/********************************************************************
 
 Copyright (c) AM-Studio. All rights reserved.
 
 filename: 	GameSocket.cpp
 author:		HuangYi(notlingfeng@163.com)
 purpose:
 
 history: 	2010/05/21 revision 1.0.0.0
 
 *********************************************************************/


#include "GameSession.h"
#include "GameSocket.h"


static const char * s_netConnectFuncName = "OnNetConnectCallback";
static const char * s_netDisconnectFuncName = "OnNetDisconnectCallback";



GameSocket::GameSocket( GameSession* pSession, SOCKET hSocket, uint32 sizeRecv, uint32 sizeSend ) : PackSocket( hSocket, sizeRecv, sizeSend ), m_pSession(pSession)
{
    
}

GameSocket::~GameSocket()
{
    
}

bool GameSocket::OnQueuePacket( PacketBuff* packet )
{   
    if ( NULL != m_pSession )
    {
        m_pSession->QueuePacket( packet );
        return true;
    }
    else
    {
        return false ;
    }
}


void GameSocket::OnConnect()
{
	m_pSession->EndUpdateConnectingTick();
    m_pSession->BeginUpdateTick();
    OnJSCallbackHandle( s_netConnectFuncName, EN_NEC_SUCC );
}

void GameSocket::OnDisconnect( eNetErrorCode ercode )
{
    m_pSession->EndUpdateConnectingTick();
    m_pSession->EndUpdateTick();
    
    if(ercode >= 10)
    {
        OnJSCallbackHandle( s_netDisconnectFuncName, ercode );
    }
    else
    {
       OnJSCallbackHandle( s_netConnectFuncName, ercode );
    }
}

void GameSocket::OnConnecting()
{
    m_pSession->BeginUpdateConnectingTick();
}






