#ifndef _DEFINES_H
#define _DEFINES_H



typedef   long long         int64;
//typedef long               int32;
typedef int                 int32;
typedef short               int16;
typedef signed char         int8;
typedef unsigned long long  uint64;
typedef unsigned int        uint32;
typedef unsigned short      uint16;
typedef unsigned char       uint8;

#define MACRO_PROPERTY_DEF( T, varName, funName )					\
	protected: T varName;											\
	public: virtual T Get##funName() const {return varName;}		\
	public: virtual void Set##funName( T var ) {varName = var;}

#define MACRO_PROPERTY_READONLT( T, varName, funName )				\
	protected: T varName;											\
	public: virtual T Get##funName() const {return varName;}

#define MACRO_PROPERTY_REF_DEF( T, varName, funName )				\
	protected: T varName;											\
	public: virtual T& Get##funName() {return varName;}	\
	public: virtual void Set##funName( const T& var ) { varName = var; }

#define MACRO_PROPERTY_REF_CONST_DEF( T, varName, funName )			\
	protected: T varName;											\
	public: virtual const T& Get##funName() {return varName;}		\
	public: virtual void Set##funName( const T& var ) { varName = var; }

///////// Server Macro ///////////

#define DYNAMIC_PROPERTY_DEF( T, varName, funName, enumName )		\
	public: virtual void Set##funName( T var )						\
	{																\
		varName = var;												\
		setProperty( enumName, varName );							\
	}

#define DYNAMIC_PROPERTY_OBJ_DEF( T, varName, funName, enumName )	\
	public: virtual void Set##funName( T var )						\
	{																\
		varName = var;												\
		setProperty( enumName, AnyType(varName, true) );			\
	}

#define DYNAMIC_PROPERTY_REF_DEF( T, varName, funName, enumName )	\
	public: virtual void Set##funName( const T& var )				\
	{																\
		varName = var;												\
		/*setProperty( enumName, AnyType( varName, false) );*/		\
	}

// DON'T break INSIDE
//#define FOR_EACH( elemType, elem, containerType, container )	\
//	for ( containerType::iterator __it = container.begin(); __it != container.end(); ++__it) 	\
//		for ( bool __go = true; __go; )		\
//			for ( elemType& elem = *__it; __go; __go =false )
//
//// DON'T break INSIDE
//#define FOR_EACH_CONST( elemType, elem, containerType, container )	\
//	for ( containerType::const_iterator __it = container.begin(); __it != container.end(); ++__it) 	\
//		for ( bool __go = true; __go; )		\
//			for ( const elemType& elem = *__it; __go; __go =false )

#define SAFE_DELETE( _p )		\
	do\
	{\
		if ( _p )\
		{\
			delete _p;\
			_p = NULL;\
		}\
	} while (0);

// compiler warning 4010 on win32
//#define PUSH_BACK_AND_GET( Val, T, V )	\
//	(V).push_back( T() );				\
//	T& Val = (V).back();				\

#define SCENE_GET_CTRL( TYPE, ASSIGN_TO, FROM_BASE_SCENE, CTRL_NAME )  \
    do  \
    {\
        ASSIGN_TO = dynamic_cast< TYPE >( FROM_BASE_SCENE.GetController( CTRL_NAME ) );    \
        if ( ASSIGN_TO == NULL )\
        {\
            CCLOGERROR( "%s(%d): '"#ASSIGN_TO"' not Exist", __FILE__, __LINE__ );\
        }\
    } while (0)




//#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#if defined WIN32

#define snprintf _snprintf
#define vsnprintf	_vsnprintf

#endif

#endif
