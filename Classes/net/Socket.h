/********************************************************************
 
 Copyright (c) AM-Studio. All rights reserved.
 
 filename: 	Socket.h
 author:		HuangYi(notlingfeng@163.com)
 purpose:
 
 history: 	2010/05/21 revision 1.0.0.0
 
 *********************************************************************/


#ifndef __SOCKET_HY_
#define __SOCKET_HY_



#include "CircularBuffer.h"
#include "NetBase.h"

typedef enum
{
    ENET_STATE_INVALID,
    ENET_STATE_DISCONNECT,
    ENET_STATE_CONNECTING,
    ENET_STATE_CONNECTED
} eConnectState;


typedef enum
{
    EN_NEC_SUCC         = 0,
    EN_NEC_DIS_TIMEOUT	= 1,
    EN_NEC_DIS_UNABLE	= 2,
    EN_NEC_DIS_SYSERR	= 3,
    EN_NEC_DIS_NONET	= 4,
    
    
    EN_NEC_DIS_ACTIVE	= 10,
    EN_NEC_DIS_BREAK	= 11,
    EN_NEC_DIS_SERVER	= 12,
}eNetErrorCode;


class Socket : public CNetBase
{
public:
    Socket( SOCKET hSocket, uint32 sizeRecv, uint32 sizeSend );
    virtual ~Socket();
    
    void 	ConnectTo(const char* ip, uint16 port);
    void	Disconnect( eNetErrorCode ercode );
    
    void	BurstSend();
    void	BurstRecv();
    
    bool	SendData(const char * pBytes, uint32 Size);
    
    bool		IsNamed( SOCKET hs )	{ return hs == m_sock; } ;
    bool		IsConnected()			{ return m_netSatte == ENET_STATE_CONNECTED; };
    void		CheckConnectingFinish( float dt );
    
protected:
    bool 		IsTryAgain();
    
    virtual void OnRead()		{} ;
    virtual void OnConnect()	{} ;
    virtual void OnDisconnect( eNetErrorCode ercode ) {} ;
    virtual void OnConnecting() {} ;	//
    
 
    void	ActuallySend();
    void	ActuallyRecv();
    bool	BurstWriteBuff(const char * pBytes, uint32 Size);		// 
    
protected:
    CircularBuffer	m_sendBuffer;
    CircularBuffer	m_recvBuffer;
    
    eConnectState	m_netSatte;
    float			m_fTickConnectElapsed;
    
};


#endif		// __SOCKET_HY_