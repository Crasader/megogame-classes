/********************************************************************
 
 Copyright (c) AM-Studio. All rights reserved.
 
 filename: 	GameSession.h
 author:		HuangYi(notlingfeng@163.com)
 purpose:
 
 history: 	2010/05/21 revision 1.0.0.0
 
 *********************************************************************/



#ifndef __GAME_SESSION_HY_
#define __GAME_SESSION_HY_

#include "cocos2d.h"
#include "GameDefines.h"
#include "FastQueue.hpp"

class GameSession;
class CommonFnArgs;
class PacketBuff;
class GameSocket;
class GameSession : public cocos2d::Ref
{    
public:
	static void		InitNet();
	static void		CloseNet();
    static void		SendRawData(uint32 opcode, CommonFnArgs* rPack);
    
    static void     InitDebuggerClient(const char* ip_);
    
	static  GameSession *Instance()
	{
		ASSERTH(NULL!=s_pGameSession);
		return s_pGameSession;
	};
	static	GameSession	* s_pGameSession;    
    
	bool	ConnectNewSock( const char * pAddress, uint32 Port );
	void	ReleaseGameSock();
    
public:
	GameSession();
	~GameSession();
    
	void	SendData( uint32 opcode, const char * pData, uint32 len );
	void	QueuePacket(PacketBuff* packet);
    
	bool	IsActive();
    
    void	BeginUpdateTick();
    void	EndUpdateTick();
    void	BeginUpdateConnectingTick();
    void	EndUpdateConnectingTick();

    void sendCmd(uint32 opcode);
    
protected:
    void	UpdateTick(float delt);
    void	UpdateConnectingTick(float delt);		
    
	void	SendPacket( PacketBuff * pPacket );
	void	UpdateHandleQueue();        
    
    void	OnSessionHandle( char * pdata, int len );
    void	OnSessionHandleJS( char * pdata, int len );

protected:
	FastQueue<PacketBuff*, DummyLock> m_recvQueue;
	GameSocket	*	m_pSocket ;
    cocos2d::Scheduler * m_scheduler;
    
};


void	OnJSCallbackHandle( const char * funcname, int errorcode );



#define g_pNetSession	GameSession::Instance()


#endif		// __GAME_SESSION_HY_