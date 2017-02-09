#ifndef _NETBASE_H_
#define _NETBASE_H_


#include "cocos2d.h"
USING_NS_CC;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#include <winsock.h>
	typedef int				socklen_t;
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <arpa/inet.h>
	typedef int				SOCKET;

	//#pragma region define win32 const variable in linux
	#define INVALID_SOCKET	-1
	#define SOCKET_ERROR	-1
	//#pragma endregion
#endif

#include <errno.h>


class CNetBase
{
public:
	CNetBase(SOCKET sock = INVALID_SOCKET);
	~CNetBase();

	// Create socket object for snd/recv data socket(AF_INET, SOCK_STREAM, 0);
	bool Create(int af = AF_INET, int type = SOCK_STREAM, int protocol = 0);

	// Connect socket
	int Connect(const char* ip, unsigned short port);

	//region server
	// Bind socket
	bool Bind(unsigned short port);

	// Listen socket
	bool Listen(int backlog = 5);

	// Accept socket
	bool Accept(CNetBase& s, char* fromip = NULL);
	//endregion
	
	// Send socket
	int Send(const char* buf, int len, int flags = 0);

	// Recv socket
	int Recv(char* buf, int len, int flags = 0);
	
	// Close socket
	int Close();

	// Get errno
	int GetError();
	
	//#pragma region just for win32
	// Init winsock DLL 
	static int Init();	
	// Clean winsock DLL
	static int Clean();
	//#pragma endregion

    int GetSockfd() 	{ return m_sock; };
    
	// Domain parse
	static bool DnsParse(const char* domain, char* ip);

	CNetBase& operator = (SOCKET s);

	operator SOCKET ();

protected:
	SOCKET m_sock;

};

#endif