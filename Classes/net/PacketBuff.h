
/********************************************************************
 
 Copyright (c) AM-Studio. All rights reserved.
 
 filename: 	PacketBuff.h
 author:		HuangYi(notlingfeng@163.com)
 purpose:
 
 history: 	2010/05/21 revision 1.0.0.0
 
 *********************************************************************/



#ifndef __PACKET_BUFF_HY_
#define __PACKET_BUFF_HY_


#include "GameDefines.h"
#include "cocos2d.h"
using namespace cocos2d;

typedef	uint16 WORD ;


class PacketBuff
{
public:
	explicit PacketBuff( WORD sz );						// real size = sz + sizeof(WORD)
	PacketBuff( const PacketBuff& rOther );
	virtual ~PacketBuff();
    
	WORD	GetSize()	const		{ return *(reinterpret_cast<WORD*>(m_data)) ; } ;
	WORD	GetOpcode()	const		{ return *(reinterpret_cast<WORD*>(m_data+sizeof(WORD))) ; } ;
	void	SetOpcode(WORD opcode)	{ *(reinterpret_cast<WORD*>(m_data+sizeof(WORD))) = opcode ; } ;
    
	char *	GetBuffer()				{ return m_data; } ;
	char *	GetOpcodeAddr()			{ return m_data+sizeof(WORD); } ;			//
	char *	GetData()				{ return m_data+sizeof(WORD)*2; } ;			// 
	
	void	SetOpcodeData( const void* pdata, WORD sz );
	void	SetData( const void* pdata, WORD sz );
    
	char &	operator []( int idx )	{ return m_data[idx]; };
    
protected:
	char * m_data;			//
};



class CommonFnArgs : public cocos2d::Ref
{
protected:		//
	enum CONSTANT
	{
		BUFF_SIZE = 1024*100,		//
	};
    
public:
    CommonFnArgs():
    m_pData(ms_buf),
    m_size(0)
    {
    
    } ;
    
	void		WriteByte( uint8 val );
	void		WriteWord( uint32 val );
	void		WriteDWord( uint32 val );
    void		WriteInt8( int val );
    void		WriteInt16( int val );
	void		WriteInt( int val );
	void		WriteFloat( float val );
	void		WriteDouble( double val );
	void		WriteInt64( int64 val );
	void		WriteStream( const char * pBuff, int len );
    void		WriteString( const std::string & str );
    void		WriteCString( const std::string & str );
    
	char *		GetData();
	uint32		GetSize();
    
public:
    CommonFnArgs( char * pData, int sz ) : m_pData(pData), m_size(sz)		{} ;
    
	uint8		ReadByte();
	uint32		ReadWord();
	uint32		ReadDWord();
	int			ReadInt8();
    int			ReadInt16();
    int			ReadInt();
	float		ReadFloat();
	double		ReadDouble();
	int64		ReadInt64();
    std::string	ReadString();
    std::string ReadString( int len );
    std::string	ReadCString();
    
	bool		ReadStream( char * pBuff, int len );
	char *		ReadStreamPtr( int len );
    
	bool		Enough( int len );
    
    template<typename T>
    void        Read(T& _val)
    {
        ASSERTH( Enough(sizeof(T)) );
        memcpy(&_val, m_pData, sizeof(T));
        Advance( sizeof(T) );
    }
    template<typename T>
    void        Write(const T& _val)
    {
        memcpy(m_pData+m_size, &_val, sizeof(T));
        m_size	+= sizeof(T);
    }
protected:
    void		Advance( int bytes );
    int			LeftBytes();  
    
	char *		m_pData;
	int			m_size;
    
	static char		ms_buf[BUFF_SIZE];
};



#define TYPE_READ( type, val, args )\
    type val;\
    ASSERTH(args.Enough(sizeof(type)));\
    args.ReadStream( reinterpret_cast<char*>(&val), sizeof(type) );





#endif		// __PACKET_BUFF_HY_