/********************************************************************
 
	Copyright (c) AM-Studio. All rights reserved.
	
	filename: 	PacketBuff.cpp
	author:		HuangYi(notlingfeng@163.com)
	purpose:	

	history: 	2010/05/21 revision 1.0.0.0 

*********************************************************************/




#include "PacketBuff.h"
#include <vector>

PacketBuff::PacketBuff( WORD sz )
{
	m_data = new char[sz];
	ASSERTH( NULL != m_data );
	*( reinterpret_cast<WORD*>(m_data) ) = sz ;
}

PacketBuff::PacketBuff( const PacketBuff& rOther )
{
	m_data = new char[rOther.GetSize()];
	ASSERTH( NULL != m_data );

	memcpy( m_data, rOther.m_data, rOther.GetSize() );
}


PacketBuff::~PacketBuff()
{
	delete []	m_data;
	m_data = NULL ;
}


void	PacketBuff::SetOpcodeData( const void* pdata, WORD sz )
{
	ASSERTH( sz <= GetSize()-sizeof(WORD) );
	memcpy( GetOpcodeAddr(), pdata, sz );
}


void	PacketBuff::SetData( const void* pdata, WORD sz )
{
	ASSERTH( sz <= GetSize()-sizeof(WORD)*2 );
	memcpy( GetData(), pdata, sz );
}




char	CommonFnArgs::ms_buf[BUFF_SIZE];	


void		CommonFnArgs::WriteByte( uint8 val )
{
    Write<uint8>(val);
//	*reinterpret_cast<uint8*>(m_pData+m_size) = val ;
//	m_size		+= sizeof(uint8);
}

void		CommonFnArgs::WriteWord( uint32 val )
{
    Write<uint16>(val);
//	*reinterpret_cast<uint16*>(m_pData+m_size) = static_cast<uint16>(val) ;
//	m_size		+= sizeof(uint16);
}

void		CommonFnArgs::WriteDWord( uint32 val )
{
    Write<uint32>(val);
//	*reinterpret_cast<uint32*>(m_pData+m_size) = val ;
//	m_size		+= sizeof(uint32);
}

void		CommonFnArgs::WriteInt8( int val )
{
    Write<int8>(val);
//	*reinterpret_cast<int8*>(m_pData+m_size) = static_cast<int8>(val) ;
//	m_size		+= sizeof(int8);
}

void		CommonFnArgs::WriteInt16( int val )
{
    Write<int16>(val);
//	*reinterpret_cast<int16*>(m_pData+m_size) = static_cast<int16>(val) ;
//	m_size		+= sizeof(int16);
}

void		CommonFnArgs::WriteInt( int val )
{
    Write<int>(val);
//	*reinterpret_cast<int*>(m_pData+m_size) = val ;
//	m_size		+= sizeof(int);
}

void		CommonFnArgs::WriteFloat( float val )
{
    Write<float>(val);
//	*reinterpret_cast<float*>(m_pData+m_size) = val ;
//	m_size		+= sizeof(float);
}

void		CommonFnArgs::WriteDouble( double val )
{
    Write<double>(val);
//	*reinterpret_cast<double*>(m_pData+m_size) = val ;
//	m_size		+= sizeof(double);
}

void		CommonFnArgs::WriteInt64( int64 val )
{
    Write<int64>(val);
//	*reinterpret_cast<int64*>(m_pData+m_size) = val ;
//	m_size		+= sizeof(int64);
}


void		CommonFnArgs::WriteStream( const char * pBuff, int len )
{
	memcpy(m_pData+m_size, pBuff, len);
	m_size	+= len;
}

void		CommonFnArgs::WriteString( const std::string & str )
{
    int sz = static_cast<int>(str.size());
    WriteWord(sz);
    WriteStream(str.c_str(), sz);
}

void		CommonFnArgs::WriteCString( const std::string & str )
{
    int sz = static_cast<int>(str.size());
    WriteStream(str.c_str(), sz+1);				//
}

char *		CommonFnArgs::GetData()
{
	return m_pData;
}

uint32		CommonFnArgs::GetSize()
{
	return	m_size;
}




uint8		CommonFnArgs::ReadByte()
{
	ASSERTH( Enough(sizeof(uint8)) );
	uint8	val = 0; // = *reinterpret_cast<uint8*>(m_pData);
//	Advance( sizeof(uint8) );
    
    Read<uint8>(val);
    
	return val;
}

uint32		CommonFnArgs::ReadWord()
{
	ASSERTH( Enough(sizeof(uint16)) );
	uint16	val = 0; // = *reinterpret_cast<uint16*>(m_pData);
//	Advance( sizeof(uint16) );
    
    Read<uint16>(val);
    
	return val;
}

uint32		CommonFnArgs::ReadDWord()
{
	ASSERTH( Enough(sizeof(uint32)) );
	uint32	val = 0; // = *reinterpret_cast<uint32*>(m_pData);
//	Advance( sizeof(uint32) );
    
    Read<uint32>(val);
    
	return val;
}

int			CommonFnArgs::ReadInt8()
{
	ASSERTH( Enough(sizeof(int8)) );
	int8	val = 0; // 		= *reinterpret_cast<int8*>(m_pData);
//	Advance( sizeof(int8) );
    
    Read<int8>(val);
    
	return val;
}

int			CommonFnArgs::ReadInt16()
{
	ASSERTH( Enough(sizeof(int16)) );
	int16	val = 0; //		= *reinterpret_cast<int16*>(m_pData);
//	Advance( sizeof(int16) );
    
    Read<int16>(val);
    
	return val;
}

int			CommonFnArgs::ReadInt()
{
	ASSERTH( Enough(sizeof(int)) );
	int	val = 0; //		= *reinterpret_cast<int*>(m_pData);
//	Advance( sizeof(int) );
    
    Read<int>(val);
    
	return val;
}


float		CommonFnArgs::ReadFloat()
{
	ASSERTH( Enough(sizeof(float)) );
	float	val = 0; //		= *reinterpret_cast<float*>(m_pData);
//	Advance( sizeof(float) );
    
    Read<float>(val);
    
	return val;
}

double	CommonFnArgs::ReadDouble()
{
	ASSERTH( Enough(sizeof(double)) );
	double	val = 0; //		= *reinterpret_cast<double*>(m_pData);
//	Advance( sizeof(double) );
    
    Read<double>(val);
    
	return val;
}

int64	CommonFnArgs::ReadInt64()
{
	ASSERTH( Enough(sizeof(int64)) );
	int64	val = 0; //		= *reinterpret_cast<int64*>(m_pData);
//	Advance( sizeof(int64) );
    
    Read<int64>(val);
    
	return val;
}

std::string	CommonFnArgs::ReadString()	
{
    ASSERTH( Enough(sizeof(uint16)) );
    uint32 len = ReadWord();
    return std::string( ReadStreamPtr(len), len );
}

std::string CommonFnArgs::ReadString( int len )
{
    ASSERTH( Enough(len) );
    return std::string( ReadStreamPtr(len), len );
}

std::string	CommonFnArgs::ReadCString()
{    
    std::string tmp( m_pData );
    int sz = static_cast<int>(tmp.size());
    ASSERTH( Enough(sz) );
    Advance(sz+1);
    return tmp;
}

bool		CommonFnArgs::ReadStream( char * pBuff, int len )
{
	ASSERTH( Enough(len) );
    
	if (Enough(len))
	{
		memcpy(pBuff, m_pData, len);
		Advance(len);
        
		return true;
	}
	else
	{
		return false;
	}    
}

char *		CommonFnArgs::ReadStreamPtr( int len )
{
	ASSERTH( Enough(len) );
    
	char * ptemp = m_pData ;
	Advance(len);
    
	return ptemp;
}

void		CommonFnArgs::Advance( int bytes )
{
	m_pData += bytes;
	m_size	-= bytes;
}

bool		CommonFnArgs::Enough( int len )
{
	return	len <= m_size ;
}

int			CommonFnArgs::LeftBytes()
{
	return	m_size;
}



