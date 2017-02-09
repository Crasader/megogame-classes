/********************************************************************
 
 Copyright (c) AM-Studio. All rights reserved.
 
 filename: 	CircularBuffer.h
 author:		HuangYi(notlingfeng@163.com)
 purpose:
 
 history: 	2010/05/21 revision 1.0.0.0
 
 *********************************************************************/


#ifndef __CIRCULAR_BUFFER_HY_
#define __CIRCULAR_BUFFER_HY_


#include "GameDefines.h"




class CircularBuffer
{
	uint8 * m_pBuffer;
	uint8 * m_pBufferEnd;
    
	uint8 * m_pRead;
	uint32	m_rSizeA;		//
	uint32	m_rSizeB;		//
    
	uint8 * m_pWrite;
	uint32	m_wSizeA;		//
	uint32	m_wSizeB;		// 
    
public:
	CircularBuffer();
	~CircularBuffer();
    
	void	InitBuffer( uint32 sz );
	void	ReleaseBuff();
    void	ResetAll();
    
	bool	IsInvalid()		{ return NULL == m_pBuffer; } ;
	bool	IsEmpty()		{ return 0 == m_rSizeA ; };
	bool	IsFull()		{ return 0 == m_wSizeA ; };
	uint32	GetTotalSize()	{ return ( m_rSizeA+m_rSizeB+m_wSizeA+m_wSizeB ); };
    
	void *	GetReadBuffer();
	uint32	GetReadSize();
	uint32	GetUsedSize();
    
	void *	GetWriteBuffer();
	uint32	GetWriteSize();
	uint32	GetFreeSize();
    
	bool	Read( void * pdest, uint32 sz );
	bool	Write( const void * psrc, uint32 sz );
    
	void	IncrementWrite( uint32 sz );
	void	IncrementRead( uint32 sz );
    
    bool	ExpandAlign( uint32 sz );
    
protected:
	//size_t	m_szTotal ;
	//bool	TestSize() { return m_szTotal == ( m_rSizeA+m_rSizeB+m_wSizeA+m_wSizeB ) ; } ;
};



#endif