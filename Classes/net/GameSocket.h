/********************************************************************
 
	Copyright (c) AM-Studio. All rights reserved.
	
	filename: 	GameSocket.h
	author:		HuangYi(notlingfeng@163.com)
	purpose:	

	history: 	2010/05/21 revision 1.0.0.0 

*********************************************************************/



#ifndef __GAME_SOCKET_HY_
#define __GAME_SOCKET_HY_


#include "PackSocket.h"


class GameSession ;

class GameSocket : public PackSocket
{
public:
	enum
	{
		RECV_BUFF_SIZE = 1024 << 4,		// 16 K
		SEND_BUFF_SIZE = 1024 << 4,
	};

public:
	explicit GameSocket( GameSession* pSession, SOCKET hSocket = INVALID_SOCKET, uint32 sizeRecv = RECV_BUFF_SIZE, uint32 sizeSend = SEND_BUFF_SIZE );
	~GameSocket();

protected:
	bool	OnQueuePacket( PacketBuff* packet );
	void	OnConnect();
	void	OnDisconnect( eNetErrorCode ercode );
    void 	OnConnecting();

protected:
	GameSession *	m_pSession;
};


#endif		// __GAME_SOCKET_HY_