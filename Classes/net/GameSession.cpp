/********************************************************************
 
 Copyright (c) AM-Studio. All rights reserved.
 
 filename: 	GameSession.cpp
 author:		HuangYi(notlingfeng@163.com)
 purpose:
 
 history: 	2010/05/21 revision 1.0.0.0
 
 *********************************************************************/


#include "cocos2d_specifics.hpp"
#include "GameSocket.h"
#include "GameSession.h"

#include "debugger_server.h"
using namespace cocos2d;

// c++ 回调 js函数名
static const char * s_netfuncName = "OnNetPacketHandle";

static const float s_netTickTime = 0.03;

GameSession	* GameSession::s_pGameSession = NULL;


void	GameSession::InitNet()
{
    CNetBase::Init();
	s_pGameSession = new GameSession();
}

void	GameSession::CloseNet()
{
	delete s_pGameSession;
	s_pGameSession = NULL;
    
	CNetBase::Clean();
}


bool	GameSession::ConnectNewSock( const char * pAddress, uint32 Port )
{
	if ( NULL != m_pSocket )
	{
		ReleaseGameSock();
	}
    
	m_pSocket = new GameSocket(this);
    
    m_pSocket->ConnectTo(pAddress, Port) ;
    CCLOG("connetting ip:%s port:%d",pAddress,Port);
    return true;
}

void	GameSession::ReleaseGameSock()
{
	if ( NULL != m_pSocket )
	{
		m_pSocket->Disconnect( EN_NEC_DIS_ACTIVE );
        
		delete m_pSocket;
		m_pSocket = NULL;        
	}
}

GameSession::GameSession()	:
m_pSocket(NULL),
m_scheduler(nullptr)
{
    m_scheduler = Director::getInstance()->getScheduler();
    
}

GameSession::~GameSession()
{
	while ( m_recvQueue.HasItems() )
	{
		delete m_recvQueue.Pop() ;
	}
    
	ReleaseGameSock();    
}

void		GameSession::UpdateTick(float delt)
{
	if (m_pSocket)
	{
        m_pSocket->UpdateSendQueue();
        m_pSocket->BurstSend();
        m_pSocket->BurstRecv();		
	}
    
    UpdateHandleQueue();
}

void	GameSession::UpdateConnectingTick(float delt)
{
    if (m_pSocket)
    {
        m_pSocket->CheckConnectingFinish(delt);
    }
}

void	GameSession::BeginUpdateTick()
{
    m_scheduler->schedule(CC_SCHEDULE_SELECTOR(GameSession::UpdateTick), this, s_netTickTime, false);
//    m_scheduler->scheduleSelector( schedule_selector(GameSession::UpdateTick), this, s_netTickTime, false );
}

void	GameSession::EndUpdateTick()
{
    m_scheduler->unschedule(CC_SCHEDULE_SELECTOR(GameSession::UpdateTick), this);
    
//    m_scheduler->unscheduleSelector(schedule_selector(GameSession::UpdateTick), this );
}

void	GameSession::BeginUpdateConnectingTick()
{
    m_scheduler->schedule(CC_SCHEDULE_SELECTOR(GameSession::UpdateConnectingTick), this, 0, false);

//    m_scheduler->scheduleSelector( schedule_selector(GameSession::UpdateConnectingTick), this, 0, false );
}

void	GameSession::EndUpdateConnectingTick()
{
//    m_scheduler->unscheduleSelector(schedule_selector(GameSession::UpdateConnectingTick), this );
    
    m_scheduler->unschedule(CC_SCHEDULE_SELECTOR(GameSession::UpdateConnectingTick), this);
}



void	GameSession::SendRawData(uint32 opcode, CommonFnArgs* rPack)
{
	g_pNetSession->SendData( opcode, rPack->GetData(), rPack->GetSize() );
}

void GameSession::InitDebuggerClient(const char *ip_)
{
    Editor::DebuggerClient::GetInstance().InitClient(ip_);
}

void	GameSession::SendData( uint32 opcode, const char * pData, uint32 datalen )
{    
    PacketBuff	data( (WORD)(datalen + sizeof(WORD)*2) );
    data.SetOpcode( opcode );
    if ( NULL != pData )
    {
        data.SetData( pData, datalen );
    }
    
    SendPacket(&data);
}


void	GameSession::SendPacket( PacketBuff * pPacket )
{
	if ( m_pSocket )
	{
		m_pSocket->SendPacket( pPacket );
	}
}

void	GameSession::QueuePacket(PacketBuff* packet)
{
	m_recvQueue.Push(packet);
}

bool	GameSession::IsActive()
{
    return NULL != m_pSocket && m_pSocket -> IsConnected();
}

void	GameSession::UpdateHandleQueue()
{    
	PacketBuff *packet;
    
	while ( 0 != (packet=m_recvQueue.Pop()) )
	{
        int len = packet->GetSize()-sizeof(WORD);
        OnSessionHandle( packet->GetOpcodeAddr(), len );
        
		delete	packet ;        
	}
}


void	GameSession::OnSessionHandle( char * pdata, int len )
{
    this->OnSessionHandleJS(pdata, len);
    return;
    
	JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

    CommonFnArgs args(pdata, len);    

    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
//    JSObject * gl = ScriptingCore::getInstance()->getGlobalObject();
    JS::RootedObject gl(cx, ScriptingCore::getInstance()->getGlobalObject());

    JS::RootedValue retval(cx);

//    jsval retval;
    js_proxy_t *childProxy = js_get_or_create_proxy<CommonFnArgs>(cx, &args);
    jsval dataVal = OBJECT_TO_JSVAL(childProxy->obj);

    bool hasAction;
    JS::RootedValue temp_retval(cx);    
    
    if (JS_HasProperty(cx, gl, s_netfuncName, &hasAction) && hasAction)
    {
        if(!JS_GetProperty(cx, gl, s_netfuncName, &temp_retval))
        {
            return;
        }
        if(temp_retval == JSVAL_VOID)
        {
            return;
        }
		JSAutoCompartment ac(cx, gl);
//        JS_CallFunctionName(cx, gl, s_netfuncName, 1, &dataVal, &retval);
        
        JS_CallFunctionName(cx, gl, s_netfuncName,
                            JS::HandleValueArray::fromMarkedLocation(1, &dataVal), &retval);

    }

}
void GameSession::sendCmd(uint32 opcode)
{
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    
    JS::RootedValue temp_retval(cx);
    
    bool ok = JS_GetProperty(cx, global, "netMessageManger", &temp_retval);
    if (!ok)
    {
        CCLOG("netMessageManger from netMessageManger Error");
    }
    JS::RootedObject pObj(cx);
    JS_ValueToObject(cx,temp_retval,&pObj);
    
    JS::RootedValue out(cx);
    JS_GetProperty(cx,pObj,"binDataBuffer", &out);
    GLsizei count;
    void* buffer;
    ok = JSB_get_arraybufferview_dataptr(cx, out, &count, &buffer);
    if (ok)
    {
        CommonFnArgs args((char *)buffer, count);
        this->SendRawData(opcode, &args);
    }
    else
    {
        CCLOG("无法获取 netMessageManger.binDataBuffer对象");
    }
    JSAutoCompartment ac(cx, global);

}

void GameSession::OnSessionHandleJS( char * pdata, int len )
{
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    CommonFnArgs args(pdata, len);
    
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject gl(cx, ScriptingCore::getInstance()->getGlobalObject());
    
    JS::RootedValue retval(cx);
    
    jsval valArr[2];
    valArr[0] = INT_TO_JSVAL( args.ReadWord());
    
    uint32 mm = args.GetSize();
    char* buf = new char[mm + 1];
    args.ReadStream(buf, mm);
    // js 数组
    JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0));
    for (uint32 i = 0;i < mm;i++)
    {
        JS::RootedValue arrElement(cx);
        arrElement = int32_to_jsval(cx, buf[i]);
        if (!JS_SetElement(cx, jsretArr, i, arrElement))
        {
            break;
        }
    }
    delete[] buf;
    valArr[1] = OBJECT_TO_JSVAL(jsretArr);
//    std_vector_int_to_jsval(JSContext *cx, const std::vector<int> &v)
    bool hasAction;
    JS::RootedValue temp_retval(cx);
    
    if (JS_HasProperty(cx, gl, s_netfuncName, &hasAction) && hasAction)
    {
        if(!JS_GetProperty(cx, gl, s_netfuncName, &temp_retval))
        {
            return;
        }
        if(temp_retval == JSVAL_VOID)
        {
            return;
        }
        JSAutoCompartment ac(cx, gl);
        
        JS_CallFunctionName(cx, gl, s_netfuncName,
                            JS::HandleValueArray::fromMarkedLocation(2, valArr), &retval);
        
    }
    
}

void	OnJSCallbackHandle( const char * funcname, int errorcode )
{    
	JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
//    JSObject * gl = ScriptingCore::getInstance()->getGlobalObject();
    JS::RootedObject gl(cx, ScriptingCore::getInstance()->getGlobalObject());

    JS::RootedValue retval(cx);

//    jsval retval;
    jsval dataVal = INT_TO_JSVAL(errorcode);
    bool hasAction;
    JS::RootedValue temp_retval(cx);
    
    if (JS_HasProperty(cx, gl, funcname, &hasAction) && hasAction)
    {
        if(!JS_GetProperty(cx, gl, funcname, &temp_retval))
        {
            return;
        }
        if(temp_retval == JSVAL_VOID)
        {
            return;
        }
		JSAutoCompartment ac(cx, gl);
//        JS_CallFunctionName(cx, gl, funcname, 1, &dataVal, &retval);
        JS_CallFunctionName(cx, gl, funcname,
                            JS::HandleValueArray::fromMarkedLocation(1, &dataVal), &retval);
    }
    
}

