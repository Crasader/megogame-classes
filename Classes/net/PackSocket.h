/********************************************************************
 
	Copyright (c) AM-Studio. All rights reserved.
	
	filename: 	PackSocket.h
	author:		HuangYi(notlingfeng@163.com)
	purpose:	

	history: 	2010/05/21 revision 1.0.0.0 

*********************************************************************/



#ifndef __PACK_SOCKET_HY_
#define __PACK_SOCKET_HY_


#include "FastQueue.hpp"
#include "PacketBuff.h"
#include "Socket.h"


enum SEND_RESULT
{
	SEND_RESULT_SUCCESS = 1,
	SEND_RESULT_NO_ROOM_IN_BUFFER = 2,
	SEND_RESULT_NOT_CONNECTED = 3,
	SEND_RESULT_SOCKET_ERROR = 4,
};


class PackSocket : public Socket
{
public:
	PackSocket( SOCKET hSocket, uint32 sizeRecv, uint32 sizeSend );
	~PackSocket();

	void	SendPacket( PacketBuff * pPacket );
	void	UpdateSendQueue();

protected:
	SEND_RESULT		_OutPacket( PacketBuff * pPacket );

    void			OnRead();
    virtual bool	OnQueuePacket(PacketBuff* packet) 	{ return false; };

protected:
	FastQueue< PacketBuff*, DummyLock >	m_sendQueue ;

    WORD			m_remainSize;
};



#endif			// __PACK_SOCKET_HY_
