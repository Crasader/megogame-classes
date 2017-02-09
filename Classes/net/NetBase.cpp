
#include "NetBase.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma comment(lib, "wsock32")
#endif


CNetBase::CNetBase(SOCKET sock)
{
	m_sock = sock;
}

CNetBase::~CNetBase()
{
}

int CNetBase::Init()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	/*
     http://msdn.microsoft.com/zh-cn/vstudio/ms741563(en-us,VS.85).aspx
     
     typedef struct WSAData {
     WORD wVersion;								//winsock version
     WORD wHighVersion;							//The highest version of the Windows Sockets specification that the Ws2_32.dll can support
     char szDescription[WSADESCRIPTION_LEN+1];
     char szSystemStatus[WSASYSSTATUS_LEN+1];
     unsigned short iMaxSockets;
     unsigned short iMaxUdpDg;
     char FAR * lpVendorInfo;
     }WSADATA, *LPWSADATA;
     */
	WSADATA wsaData;
	//#define MAKEWORD(a,b) ((WORD) (((BYTE) (a)) | ((WORD) ((BYTE) (b))) << 8))
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if ( ret )
	{
		CCLOG("Initilize winsock error !");
		return -1;
	}
#endif
	
	return 0;
}
//this is just for windows
int CNetBase::Clean()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    return (WSACleanup());
#endif
    return 0;
}

CNetBase& CNetBase::operator = (SOCKET s)
{
	m_sock = s;
	return (*this);
}

CNetBase::operator SOCKET ()
{
	return m_sock;
}
//create a socket object win/lin is the same
// af:
bool CNetBase::Create(int af, int type, int protocol)
{
	m_sock = socket(af, type, protocol);
	if ( m_sock == INVALID_SOCKET )
	{
        CCLOG( "invalid socket %d, error: %d", m_sock, GetError() );
		return false;
	}
    
	return true;
}

int CNetBase::Connect(const char* ip, unsigned short port)
{
    //
    char hostaddr[32];
    bool ishost = DnsParse( ip, hostaddr );
    if (ishost)
    {
        ip = hostaddr;
    }    
    
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = inet_addr(ip);
	svraddr.sin_port = htons(port);
    
    int ret;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	unsigned long ul = 1;
	ret = ioctlsocket(m_sock, FIONBIO, (unsigned long*)&ul);
	if (ret == SOCKET_ERROR)
	{
		return -1;
	}
#else
	if(fcntl(m_sock, F_SETFL, O_NONBLOCK) == -1)
	{
		return -1;
	}
#endif
    
	ret = connect(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if ( ret == SOCKET_ERROR )
	{
        int errorcode = GetError();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		if (errorcode != WSAEWOULDBLOCK && errorcode != WSAEINPROGRESS)
        {
            return -1;
        }			
#else
		if (errorcode != EWOULDBLOCK && errorcode != EINPROGRESS)
        {
            return -1;
        }			
#endif
	}
    else if( ret == 0 )
    {
        return 1;
    }
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    // set flag SO_NOSIGPIPE, so SIGPIPE won't be raised when write fails
    // @yuxiaofei
	int opt =  1;
    if(setsockopt(m_sock, SOL_SOCKET, SO_NOSIGPIPE, (char*)&opt, sizeof(opt) ) != 0)
    {
        return -1;
    }
#endif
    
	return 0;
}

bool CNetBase::Bind(unsigned short port)
{
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = INADDR_ANY;
	svraddr.sin_port = htons(port);
    
	int opt =  1;
    // set flag SO_NOSIGPIPE, so SIGPIPE won't be raised when write fails
    int s_flag = SO_REUSEADDR;
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    s_flag = SO_REUSEADDR | SO_NOSIGPIPE;
#endif
	if ( setsockopt(m_sock, SOL_SOCKET, s_flag, (char*)&opt, sizeof(opt)) < 0 )
		return false;
    
	int ret = bind(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if ( ret == SOCKET_ERROR )
	{
		return false;
	}
	return true;
}
//for server
bool CNetBase::Listen(int backlog)
{
	int ret = listen(m_sock, backlog);
	if ( ret == SOCKET_ERROR )
	{
		return false;
	}
	return true;
}

bool CNetBase::Accept(CNetBase& s, char* fromip)
{
	struct sockaddr_in cliaddr;
	socklen_t addrlen = sizeof(cliaddr);
	SOCKET sock = accept(m_sock, (struct sockaddr*)&cliaddr, &addrlen);
	if ( sock == SOCKET_ERROR )
	{
		return false;
	}
    
	s = sock;
	if ( fromip != NULL )
		sprintf(fromip, "%s", inet_ntoa(cliaddr.sin_addr));
    
	return true;
}

int CNetBase::Send(const char* buf, int len, int flags)
{
	int bytes;
	int count = 0;
    
	while ( count < len )
	{
        
		bytes = send(m_sock, buf + count, len - count, flags);
		if ( bytes == -1 || bytes == 0 )
			return -1;
		count += bytes;
	}
    
	return count;
}

int CNetBase::Recv(char* buf, int len, int flags)
{
	return (recv(m_sock, buf, len, flags));
}

int CNetBase::Close()
{
#ifdef WIN32
	return (closesocket(m_sock));
#else
	return (close(m_sock));
#endif
}

int CNetBase::GetError()
{
#ifdef WIN32
	return (WSAGetLastError());
#else
	return (errno);
#endif
}

bool CNetBase::DnsParse(const char* domain, char* ip)
{
	struct hostent* p;
	if ( (p = gethostbyname(domain)) == NULL )
		return false;
    
	sprintf(ip,
            "%u.%u.%u.%u",
            (unsigned char)p->h_addr_list[0][0],
            (unsigned char)p->h_addr_list[0][1],
            (unsigned char)p->h_addr_list[0][2], 
            (unsigned char)p->h_addr_list[0][3]);
	
	return true;
}


