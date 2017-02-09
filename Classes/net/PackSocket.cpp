/********************************************************************
 
	Copyright (c) AM-Studio. All rights reserved.
	
	filename: 	PackSocket.cpp
	author:		HuangYi(notlingfeng@163.com)
	purpose:
 
	history: 	2010/05/21 revision 1.0.0.0
 
 *********************************************************************/


#include "PackSocket.h"


PackSocket::PackSocket( SOCKET hSocket, uint32 sizeRecv, uint32 sizeSend ) : Socket( hSocket, sizeRecv, sizeSend ), m_remainSize(0)
{
    
}

PackSocket::~PackSocket()
{
    while ( m_sendQueue.HasItems() )
    {
        delete m_sendQueue.Pop();
    }
}

void PackSocket::SendPacket( PacketBuff * pPacket )
{
    if ( NULL == pPacket )
    {
        return ;
    }
    
    if ( pPacket->GetSize() > m_sendBuffer.GetTotalSize() )
    {
        YLJ_ERROR( "WARNING: Tried to send a packet of %u bytes (which is too large) to a socket. Opcode: (0x%03X)\n", pPacket->GetSize(), pPacket->GetOpcode() );
        if ( ! m_sendBuffer.ExpandAlign( pPacket->GetSize() ) )
        {
            return ;
        }
    }
    
    if ( _OutPacket(pPacket) == SEND_RESULT_NO_ROOM_IN_BUFFER )
    {
        m_sendQueue.Push( new PacketBuff(*pPacket) );
    }
}

void PackSocket::UpdateSendQueue()
{
    if(!m_sendQueue.HasItems())
    {
        return;
    }
    
    PacketBuff * pck;
    while((pck = m_sendQueue.Front()) != 0)
    {
        switch( _OutPacket(pck) )
        {
            case SEND_RESULT_SUCCESS:
            {
                delete pck;
                m_sendQueue.Pop_front();
            }
                break;
                
            case SEND_RESULT_NO_ROOM_IN_BUFFER:
            {
                return;
            }
                break;
                
            default:
            {
                /* kill everything in the buffer */
                while( (pck = m_sendQueue.Pop()) != 0 )
                {
                    delete pck;
                }
                return;
            }
                break;
        }
    }
}


SEND_RESULT	PackSocket::_OutPacket( PacketBuff * pPacket )
{
    if ( !IsConnected() )
    {
        return	SEND_RESULT_NOT_CONNECTED ;
    }
    
    if ( SendData( pPacket->GetBuffer(), pPacket->GetSize() ) )
    {
        return	SEND_RESULT_SUCCESS ;
    }
    else
    {
        return	SEND_RESULT_NO_ROOM_IN_BUFFER ;
    }
}

void PackSocket::OnRead()
{
    while (1)
    {
        if ( 0 == m_remainSize )
        {
            if ( m_recvBuffer.GetUsedSize() < 2 )
            {
                return;
            }
            
            m_recvBuffer.Read( &m_remainSize, 2 );
        }
        
        if ( m_recvBuffer.GetUsedSize() < (uint32)(m_remainSize-2) )
        {
            return;
        }
        
        PacketBuff * packet = new PacketBuff(m_remainSize) ;
        m_recvBuffer.Read( packet->GetOpcodeAddr(), m_remainSize-2 );
        m_remainSize = 0;
        
        if ( ! OnQueuePacket(packet) )
        {
            delete packet;
        }
    }
}

