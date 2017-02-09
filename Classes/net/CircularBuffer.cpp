/********************************************************************
 
 Copyright (c) AM-Studio. All rights reserved.
 
 filename: 	CircularBuffer.cpp
 author:		HuangYi(notlingfeng@163.com)
 purpose:
 
 history: 	2010/05/21 revision 1.0.0.0
 
 *********************************************************************/



#include "CircularBuffer.h"


static const uint32		BUFFER_MIN_LEN = 1024;
static const uint32		BUFFER_MAX_LEN = 1024 << 13;		// 8 M


CircularBuffer::CircularBuffer()
{
	m_pBuffer = m_pBufferEnd = m_pRead = m_pWrite = NULL ;
	m_rSizeA = m_rSizeB = m_wSizeA = m_wSizeB = 0;
	//m_szTotal = 0;
}

CircularBuffer::~CircularBuffer()
{
	if ( NULL != m_pBuffer )
	{
		ReleaseBuff();
	}
}

void	CircularBuffer::InitBuffer( uint32 sz )
{
	ASSERTH( NULL == m_pBuffer );
	m_pBuffer = new	uint8[sz];
	ASSERTH( NULL != m_pBuffer );
	//m_szTotal = sz;
    
	m_pBufferEnd = m_pBuffer + sz;
	ResetAll();
}

void	CircularBuffer::ReleaseBuff()
{
	delete [] m_pBuffer;
	m_pBuffer = NULL;
}

void	CircularBuffer::ResetAll()
{
    m_pRead = m_pWrite = m_pBuffer ;
	m_wSizeA = m_pBufferEnd -  m_pBuffer;
	m_rSizeA = m_rSizeB = m_wSizeB = 0;
}

void *	CircularBuffer::GetReadBuffer()
{
	return m_pRead;
}

uint32	CircularBuffer::GetReadSize()
{
	return m_rSizeA ;
}

uint32	CircularBuffer::GetUsedSize()
{
	return m_rSizeA + m_rSizeB ;
}

void *	CircularBuffer::GetWriteBuffer()
{
	return m_pWrite;
}

uint32	CircularBuffer::GetWriteSize()
{
	return m_wSizeA ;
}

uint32	CircularBuffer::GetFreeSize()
{
	return m_wSizeA + m_wSizeB ;
}

bool	CircularBuffer::Read( void * pdest, uint32 sz )
{
	if ( IsInvalid() || sz > GetUsedSize() )
	{
		return false;
	}
    
	if ( sz <= m_rSizeA )
	{
		memcpy( pdest, m_pRead, sz );
	}
	else
	{
		memcpy( pdest, m_pRead, m_rSizeA );
		memcpy( (uint8*)pdest+m_rSizeA, m_pBuffer, sz-m_rSizeA );
	}
    
	IncrementRead( sz );
    
	return true;
}

bool	CircularBuffer::Write( const void * psrc, uint32 sz )
{
	if ( IsInvalid() || sz > GetFreeSize() )
	{
		return false;
	}
    
	if ( sz <= m_wSizeA )
	{
		memcpy( m_pWrite, psrc, sz );
	}
	else
	{
		memcpy( m_pWrite, psrc, m_wSizeA );
		memcpy( m_pBuffer, (uint8*)psrc+m_wSizeA, sz-m_wSizeA );
	}
    
	IncrementWrite( sz );
    
	return true;
}


void	CircularBuffer::IncrementWrite( uint32 sz )
{
	ASSERTH( sz <= GetFreeSize() );
    
	if ( m_pWrite < m_pRead )
	{
		m_pWrite += sz ;
		m_wSizeA -= sz ;
		m_rSizeB += sz ;
	}
	else
	{
		m_pWrite += sz;
        
		size_t offset = 0 ;
		if ( m_pWrite >= m_pBufferEnd )
		{
			offset = m_pWrite - m_pBufferEnd ;
			m_pWrite = m_pBuffer + offset ;
            
			m_wSizeA = m_wSizeB - offset ;
			m_wSizeB = 0 ;
		}
		else
		{
			m_wSizeA -= sz ;
		}
        
		m_rSizeA += (sz - offset) ;
		m_rSizeB += offset ;
	}
}

void	CircularBuffer::IncrementRead( uint32 sz )
{
	ASSERTH( sz <= GetUsedSize() );
    
	if ( m_pRead < m_pWrite )
	{
		m_pRead  += sz ;
		m_rSizeA -= sz ;
		m_wSizeB += sz ;
	}
	else
	{
		m_pRead += sz ;
        
		size_t offset = 0 ;
		if ( m_pRead >= m_pBufferEnd )
		{
			offset = m_pRead - m_pBufferEnd ;
			m_pRead = m_pBuffer + offset ;
            
			m_rSizeA = m_rSizeB - offset ;
			m_rSizeB = 0 ;
		}
		else
		{
			m_rSizeA -= sz ;
		}
        
		m_wSizeA += (sz - offset) ;
		m_wSizeB += offset ;
	}
}

bool	CircularBuffer::ExpandAlign( uint32 sz )
{
    uint32 len = GetTotalSize();
    uint32 need = len + sz;
    
    if ( len < BUFFER_MIN_LEN )
    {
        len = BUFFER_MIN_LEN;
    }
    
    while ( len < need )
    {
        len <<= 1;
    }
    
    if ( len > BUFFER_MAX_LEN )
    {
        YLJ_ERROR("CircularBuffer Error for too large size : %d", len);
        return false;
    }
    
    YLJ_LOG("CircularBuffer warning : Expand for new size : %d", len);
    
	uint8 * ptemp = new	uint8[len];
	ASSERTH( NULL != ptemp );

    memcpy( ptemp, m_pRead, m_rSizeA );
    memcpy( ptemp+m_rSizeA, m_pBuffer, m_rSizeB );
    
    delete [] m_pBuffer;
    
    m_pRead = m_pBuffer = ptemp;
    m_rSizeA += m_rSizeB;
    m_rSizeB = 	0;
    
    m_pWrite = m_pRead + m_rSizeA;
    m_wSizeA = len - m_rSizeA;
    m_wSizeB = 0;
    
	m_pBufferEnd = m_pBuffer + len;
    
    return true;
}


