/********************************************************************
 
 Copyright (c) AM-Studio. All rights reserved.
 
 filename: 	Socket.cpp
 author:		HuangYi(notlingfeng@163.com)
 purpose:
 
 history: 	2010/05/21 revision 1.0.0.0
 
 *********************************************************************/




#include "Socket.h"


Socket::Socket( SOCKET hSocket, uint32 sizeRecv, uint32 sizeSend ) :CNetBase(hSocket), m_netSatte(ENET_STATE_INVALID), m_fTickConnectElapsed(0)
{
	if( INVALID_SOCKET == m_sock )
	{
		if( ! Create() )
        {
         	return;
        }
	}
    
	m_sendBuffer.InitBuffer( sizeSend );
	m_recvBuffer.InitBuffer( sizeRecv );
}

Socket::~Socket()
{
	Disconnect( EN_NEC_DIS_ACTIVE );
	Close();
    
	m_sendBuffer.ReleaseBuff();
	m_recvBuffer.ReleaseBuff();
}

void 	Socket::ConnectTo(const char* ip, uint16 port)
{    
    int ret = Connect(ip, port);
    
    if ( ret == 1 )
    {
        m_netSatte = ENET_STATE_CONNECTED;
        OnConnect();
    }
    else if( ret == 0 )
    {
        m_netSatte = ENET_STATE_CONNECTING;
        m_fTickConnectElapsed = 0;
        OnConnecting();
    }
    else
    {
        Disconnect( EN_NEC_DIS_NONET );
    }
}

void	Socket::Disconnect( eNetErrorCode ercode )
{
	if( m_netSatte != ENET_STATE_DISCONNECT )
	{
        shutdown(m_sock, 2);
        
		m_netSatte = ENET_STATE_DISCONNECT ;
        m_sendBuffer.ResetAll();
        m_recvBuffer.ResetAll();

		OnDisconnect( ercode );
	}
}

void	Socket::CheckConnectingFinish( float dt )
{
    // check tick connect time
	const float tick_connect_time_out = 15;

	if (m_fTickConnectElapsed >= tick_connect_time_out)
	{
		Disconnect( EN_NEC_DIS_TIMEOUT );
	}
	m_fTickConnectElapsed += dt;
    
	/* Do whatever we want while the connect is taking place */
	int errorcode, ret;
	socklen_t len;
	fd_set wset;
	struct timeval tval;
	int sockfd = GetSockfd();
	FD_ZERO(&wset);
	FD_SET(sockfd, &wset);
	tval.tv_sec = 0;
	tval.tv_usec = 30*1000;
    
	if ( select(sockfd+1, NULL, &wset, NULL, &tval ) == 0 )
    {
        return;
	}
	
	if (FD_ISSET(sockfd, &wset))
    {
        len = sizeof(errorcode);
        ret = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, (char *)&errorcode, &len);
        if (ret < 0 || errorcode)
        {
			Disconnect( EN_NEC_DIS_UNABLE );
        }
		else 	//ok
		{
			m_netSatte = ENET_STATE_CONNECTED;
			OnConnect();
		}
    }
    else
    {
        CCLOG("select error: sockfd not set");  
		Disconnect( EN_NEC_DIS_SYSERR );
    }
}


void	Socket::ActuallySend()
{
	if ( !IsConnected() )
	{
		return ;
	}
    
	if ( ! m_sendBuffer.IsEmpty() )
	{
        int retLen = Send( (char*)m_sendBuffer.GetReadBuffer(), m_sendBuffer.GetReadSize() );

        if ( retLen>0 && retLen<=m_sendBuffer.GetReadSize() )
        {
            m_sendBuffer.IncrementRead(retLen);
            ActuallySend();
        }
        else
        {
            YLJ_ERROR("NetBase send error %d", GetError());
            Disconnect( EN_NEC_DIS_BREAK );
        }
	}
}

void	Socket::ActuallyRecv()
{
	if ( !IsConnected() )
	{
		return ;
	}
    
    if ( m_recvBuffer.IsFull() )
    {
        YLJ_LOG("Net recvbuffer is full for size : %d", m_recvBuffer.GetTotalSize());
        if( ! m_recvBuffer.ExpandAlign(1) )
        {
            return;
        }
    }
    
    int retLen;    
    retLen = Recv( (char*)m_recvBuffer.GetWriteBuffer(), m_recvBuffer.GetWriteSize() );
        
    if ( retLen > 0 )
    {
        m_recvBuffer.IncrementWrite(retLen);
        OnRead();
    }
    else if( retLen == 0 || !IsTryAgain() )
    {
        Disconnect( EN_NEC_DIS_SERVER );
    }
}


bool	Socket::SendData(const char * pBytes, uint32 Size)
{
	bool rv;
    
	rv = BurstWriteBuff(pBytes, Size);
	if(rv)
    {
        BurstSend();
    }
		  
	return rv;
}

bool	Socket::BurstWriteBuff(const char * pBytes, uint32 Size)
{
    // check exist enough buff
    if ( Size > m_sendBuffer.GetFreeSize() )
    {
        YLJ_LOG("Net sendbuffer not enough for size : %d", Size);
        m_sendBuffer.ExpandAlign(Size);
    }
    
	return	m_sendBuffer.Write( pBytes, Size );
}

void	Socket::BurstSend()
{
	//if ( AttempSendOptLock() )
	{
		ActuallySend();
	}
}

void	Socket::BurstRecv()
{
    ActuallyRecv();
}

bool 	Socket::IsTryAgain()
{
	// thread safe???
#if	CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	return GetError() == WSATRY_AGAIN|| GetError() == WSAEWOULDBLOCK;
#else
	return EAGAIN == GetError() || EWOULDBLOCK == GetError();
#endif
}



