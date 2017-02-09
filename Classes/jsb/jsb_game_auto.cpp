#include "jsb_game_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "js_cpp_export.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && initializing.toBoolean();
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JS::RootedObject proto(cx, typeClass->proto.get());
        JS::RootedObject parent(cx, typeClass->parentProto.get());
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
        
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_GameSession_class;
JSObject *jsb_GameSession_prototype;

bool js_game_GameSession_QueuePacket(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameSession* cobj = (GameSession *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_GameSession_QueuePacket : Invalid Native Object");
    if (argc == 1) {
        PacketBuff* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (PacketBuff*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_GameSession_QueuePacket : Error processing arguments");
        cobj->QueuePacket(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_GameSession_QueuePacket : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_GameSession_EndUpdateConnectingTick(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameSession* cobj = (GameSession *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_GameSession_EndUpdateConnectingTick : Invalid Native Object");
    if (argc == 0) {
        cobj->EndUpdateConnectingTick();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_GameSession_EndUpdateConnectingTick : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_GameSession_BeginUpdateConnectingTick(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameSession* cobj = (GameSession *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_GameSession_BeginUpdateConnectingTick : Invalid Native Object");
    if (argc == 0) {
        cobj->BeginUpdateConnectingTick();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_GameSession_BeginUpdateConnectingTick : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_GameSession_SendData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameSession* cobj = (GameSession *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_GameSession_SendData : Invalid Native Object");
    if (argc == 3) {
        unsigned int arg0;
        const char* arg1;
        unsigned int arg2;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_game_GameSession_SendData : Error processing arguments");
        cobj->SendData(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_GameSession_SendData : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_game_GameSession_sendCmd(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameSession* cobj = (GameSession *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_GameSession_sendCmd : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_GameSession_sendCmd : Error processing arguments");
        cobj->sendCmd(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_GameSession_sendCmd : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_GameSession_ReleaseGameSock(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameSession* cobj = (GameSession *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_GameSession_ReleaseGameSock : Invalid Native Object");
    if (argc == 0) {
        cobj->ReleaseGameSock();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_GameSession_ReleaseGameSock : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_GameSession_EndUpdateTick(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameSession* cobj = (GameSession *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_GameSession_EndUpdateTick : Invalid Native Object");
    if (argc == 0) {
        cobj->EndUpdateTick();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_GameSession_EndUpdateTick : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_GameSession_ConnectNewSock(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameSession* cobj = (GameSession *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_GameSession_ConnectNewSock : Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        unsigned int arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_game_GameSession_ConnectNewSock : Error processing arguments");
        bool ret = cobj->ConnectNewSock(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_GameSession_ConnectNewSock : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_game_GameSession_BeginUpdateTick(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameSession* cobj = (GameSession *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_GameSession_BeginUpdateTick : Invalid Native Object");
    if (argc == 0) {
        cobj->BeginUpdateTick();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_GameSession_BeginUpdateTick : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_GameSession_IsActive(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameSession* cobj = (GameSession *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_GameSession_IsActive : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->IsActive();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_GameSession_IsActive : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_GameSession_InitNet(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        GameSession::InitNet();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_GameSession_InitNet : wrong number of arguments");
    return false;
}

bool js_game_GameSession_Instance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        GameSession* ret = GameSession::Instance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<GameSession>(cx, (GameSession*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_GameSession_Instance : wrong number of arguments");
    return false;
}

bool js_game_GameSession_SendRawData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        unsigned int arg0;
        CommonFnArgs* arg1;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (CommonFnArgs*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_GameSession_SendRawData : Error processing arguments");
        GameSession::SendRawData(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_GameSession_SendRawData : wrong number of arguments");
    return false;
}

bool js_game_GameSession_InitDebuggerClient(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_game_GameSession_InitDebuggerClient : Error processing arguments");
        GameSession::InitDebuggerClient(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_GameSession_InitDebuggerClient : wrong number of arguments");
    return false;
}

bool js_game_GameSession_CloseNet(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        GameSession::CloseNet();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_GameSession_CloseNet : wrong number of arguments");
    return false;
}

bool js_game_GameSession_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    GameSession* cobj = new (std::nothrow) GameSession();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<GameSession> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "GameSession");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}



void js_GameSession_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GameSession)", obj);
}

void js_register_game_GameSession(JSContext *cx, JS::HandleObject global) {
    jsb_GameSession_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameSession_class->name = "GameSession";
    jsb_GameSession_class->addProperty = JS_PropertyStub;
    jsb_GameSession_class->delProperty = JS_DeletePropertyStub;
    jsb_GameSession_class->getProperty = JS_PropertyStub;
    jsb_GameSession_class->setProperty = JS_StrictPropertyStub;
    jsb_GameSession_class->enumerate = JS_EnumerateStub;
    jsb_GameSession_class->resolve = JS_ResolveStub;
    jsb_GameSession_class->convert = JS_ConvertStub;
    jsb_GameSession_class->finalize = js_GameSession_finalize;
    jsb_GameSession_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("QueuePacket", js_game_GameSession_QueuePacket, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("EndUpdateConnectingTick", js_game_GameSession_EndUpdateConnectingTick, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("BeginUpdateConnectingTick", js_game_GameSession_BeginUpdateConnectingTick, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendData", js_game_GameSession_SendData, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("sendCmd", js_game_GameSession_sendCmd, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ReleaseGameSock", js_game_GameSession_ReleaseGameSock, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("EndUpdateTick", js_game_GameSession_EndUpdateTick, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ConnectNewSock", js_game_GameSession_ConnectNewSock, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("BeginUpdateTick", js_game_GameSession_BeginUpdateTick, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("IsActive", js_game_GameSession_IsActive, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("InitNet", js_game_GameSession_InitNet, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Instance", js_game_GameSession_Instance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendRawData", js_game_GameSession_SendRawData, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("InitDebuggerClient", js_game_GameSession_InitDebuggerClient, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("CloseNet", js_game_GameSession_CloseNet, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_GameSession_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_GameSession_class,
        js_game_GameSession_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "GameSession", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<GameSession> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_GameSession_class;
        p->proto = jsb_GameSession_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_Util_class;
JSObject *jsb_Util_prototype;

bool js_game_Util_GetCcPositionTextureColor_noMVP_vert(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = Util::GetCcPositionTextureColor_noMVP_vert();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_Util_GetCcPositionTextureColor_noMVP_vert : wrong number of arguments");
    return false;
}

bool js_game_Util_getSavedPath(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = Util::getSavedPath();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_Util_getSavedPath : wrong number of arguments");
    return false;
}

bool js_game_Util_createFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_game_Util_createFile : Error processing arguments");
        bool ret = Util::createFile(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_Util_createFile : wrong number of arguments");
    return false;
}

bool js_game_Util_isFileParentCreated(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_Util_isFileParentCreated : Error processing arguments");
        bool ret = Util::isFileParentCreated(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_Util_isFileParentCreated : wrong number of arguments");
    return false;
}

bool js_game_Util_closeKeyBoard(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_Util_closeKeyBoard : Error processing arguments");
        Util::closeKeyBoard(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_Util_closeKeyBoard : wrong number of arguments");
    return false;
}

bool js_game_Util_loopFiles(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_Util_loopFiles : Error processing arguments");
        std::vector<std::string> ret = Util::loopFiles(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = std_vector_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_Util_loopFiles : wrong number of arguments");
    return false;
}

bool js_game_Util_GetCcPositionTextureColor_vert(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = Util::GetCcPositionTextureColor_vert();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_Util_GetCcPositionTextureColor_vert : wrong number of arguments");
    return false;
}

bool js_game_Util_getAllTextureNames(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::vector<std::string> ret = Util::getAllTextureNames();
        jsval jsret = JSVAL_NULL;
        jsret = std_vector_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_Util_getAllTextureNames : wrong number of arguments");
    return false;
}

bool js_game_Util_getRealFullpath(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_Util_getRealFullpath : Error processing arguments");
        const std::string& ret = Util::getRealFullpath(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_Util_getRealFullpath : wrong number of arguments");
    return false;
}

bool js_game_Util_findPaths(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_game_Util_findPaths : Error processing arguments");
        std::vector<std::string> ret = Util::findPaths(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = std_vector_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_Util_findPaths : wrong number of arguments");
    return false;
}

bool js_game_Util_StrSplit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        std::vector<std::string> arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_vector_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_game_Util_StrSplit : Error processing arguments");
        Util::StrSplit(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_Util_StrSplit : wrong number of arguments");
    return false;
}

bool js_game_Util_GetNodeUesrStr(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_Util_GetNodeUesrStr : Error processing arguments");
        std::string ret = Util::GetNodeUesrStr(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_Util_GetNodeUesrStr : wrong number of arguments");
    return false;
}

bool js_game_Util_clearLabelKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        Util::clearLabelKey();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_Util_clearLabelKey : wrong number of arguments");
    return false;
}

bool js_game_Util_addLabelKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_game_Util_addLabelKey : Error processing arguments");
        Util::addLabelKey(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_Util_addLabelKey : wrong number of arguments");
    return false;
}



void js_Util_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Util)", obj);
}

void js_register_game_Util(JSContext *cx, JS::HandleObject global) {
    jsb_Util_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_Util_class->name = "Util";
    jsb_Util_class->addProperty = JS_PropertyStub;
    jsb_Util_class->delProperty = JS_DeletePropertyStub;
    jsb_Util_class->getProperty = JS_PropertyStub;
    jsb_Util_class->setProperty = JS_StrictPropertyStub;
    jsb_Util_class->enumerate = JS_EnumerateStub;
    jsb_Util_class->resolve = JS_ResolveStub;
    jsb_Util_class->convert = JS_ConvertStub;
    jsb_Util_class->finalize = js_Util_finalize;
    jsb_Util_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("GetCcPositionTextureColor_noMVP_vert", js_game_Util_GetCcPositionTextureColor_noMVP_vert, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSavedPath", js_game_Util_getSavedPath, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createFile", js_game_Util_createFile, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isFileParentCreated", js_game_Util_isFileParentCreated, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("closeKeyBoard", js_game_Util_closeKeyBoard, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loopFiles", js_game_Util_loopFiles, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("GetCcPositionTextureColor_vert", js_game_Util_GetCcPositionTextureColor_vert, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAllTextureNames", js_game_Util_getAllTextureNames, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRealFullpath", js_game_Util_getRealFullpath, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("findPaths", js_game_Util_findPaths, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("StrSplit", js_game_Util_StrSplit, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("GetNodeUesrStr", js_game_Util_GetNodeUesrStr, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clearLabelKey", js_game_Util_clearLabelKey, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addLabelKey", js_game_Util_addLabelKey, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_Util_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_Util_class,
        dummy_constructor<Util>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Util", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<Util> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_Util_class;
        p->proto = jsb_Util_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_AudioEngineHelper_class;
JSObject *jsb_AudioEngineHelper_prototype;

bool js_game_AudioEngineHelper_lazyInit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        bool ret = AudioEngineHelper::lazyInit();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_lazyInit : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_setCurrentTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        double arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_setCurrentTime : Error processing arguments");
        bool ret = AudioEngineHelper::setCurrentTime(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_setCurrentTime : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_getVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_getVolume : Error processing arguments");
        double ret = AudioEngineHelper::getVolume(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_getVolume : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_uncache(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_uncache : Error processing arguments");
        AudioEngineHelper::uncache(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_uncache : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_resumeAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        AudioEngineHelper::resumeAll();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_resumeAll : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_stopAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        AudioEngineHelper::stopAll();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_stopAll : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_pause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_pause : Error processing arguments");
        AudioEngineHelper::pause(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_pause : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_end(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        AudioEngineHelper::end();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_end : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_getMaxAudioInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        int ret = AudioEngineHelper::getMaxAudioInstance();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_getMaxAudioInstance : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_getCurrentTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_getCurrentTime : Error processing arguments");
        double ret = AudioEngineHelper::getCurrentTime(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_getCurrentTime : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_setVolumeAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_setVolumeAll : Error processing arguments");
        AudioEngineHelper::setVolumeAll(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_setVolumeAll : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_PlayEffectT(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_PlayEffectT : Error processing arguments");
        int ret = AudioEngineHelper::PlayEffectT(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_PlayEffectT : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_setMaxAudioInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_setMaxAudioInstance : Error processing arguments");
        bool ret = AudioEngineHelper::setMaxAudioInstance(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_setMaxAudioInstance : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_isLoop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_isLoop : Error processing arguments");
        bool ret = AudioEngineHelper::isLoop(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_isLoop : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_pauseAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        AudioEngineHelper::pauseAll();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_pauseAll : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_uncacheAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        AudioEngineHelper::uncacheAll();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_uncacheAll : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_setVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        double arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_setVolume : Error processing arguments");
        AudioEngineHelper::setVolume(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_setVolume : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_play2d(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_play2d : Error processing arguments");
        int ret = AudioEngineHelper::play2d(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_play2d : Error processing arguments");
        int ret = AudioEngineHelper::play2d(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        bool arg1;
        double arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_play2d : Error processing arguments");
        int ret = AudioEngineHelper::play2d(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_play2d : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_getState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_getState : Error processing arguments");
        int ret = (int)AudioEngineHelper::getState(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_getState : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_resume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_resume : Error processing arguments");
        AudioEngineHelper::resume(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_resume : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_stop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_stop : Error processing arguments");
        AudioEngineHelper::stop(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_stop : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_getDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_getDuration : Error processing arguments");
        double ret = AudioEngineHelper::getDuration(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_getDuration : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_setLoop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        bool arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_setLoop : Error processing arguments");
        AudioEngineHelper::setLoop(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_setLoop : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_SetEffectVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_SetEffectVolume : Error processing arguments");
        AudioEngineHelper::SetEffectVolume(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_SetEffectVolume : wrong number of arguments");
    return false;
}

bool js_game_AudioEngineHelper_setFinishCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_AudioEngineHelper_setFinishCallback : Error processing arguments");
        AudioEngineHelper::setFinishCallback(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_AudioEngineHelper_setFinishCallback : wrong number of arguments");
    return false;
}



void js_AudioEngineHelper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (AudioEngineHelper)", obj);
}

void js_register_game_AudioEngineHelper(JSContext *cx, JS::HandleObject global) {
    jsb_AudioEngineHelper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_AudioEngineHelper_class->name = "AudioEngineHelper";
    jsb_AudioEngineHelper_class->addProperty = JS_PropertyStub;
    jsb_AudioEngineHelper_class->delProperty = JS_DeletePropertyStub;
    jsb_AudioEngineHelper_class->getProperty = JS_PropertyStub;
    jsb_AudioEngineHelper_class->setProperty = JS_StrictPropertyStub;
    jsb_AudioEngineHelper_class->enumerate = JS_EnumerateStub;
    jsb_AudioEngineHelper_class->resolve = JS_ResolveStub;
    jsb_AudioEngineHelper_class->convert = JS_ConvertStub;
    jsb_AudioEngineHelper_class->finalize = js_AudioEngineHelper_finalize;
    jsb_AudioEngineHelper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("lazyInit", js_game_AudioEngineHelper_lazyInit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCurrentTime", js_game_AudioEngineHelper_setCurrentTime, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVolume", js_game_AudioEngineHelper_getVolume, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("uncache", js_game_AudioEngineHelper_uncache, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resumeAll", js_game_AudioEngineHelper_resumeAll, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopAll", js_game_AudioEngineHelper_stopAll, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pause", js_game_AudioEngineHelper_pause, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("end", js_game_AudioEngineHelper_end, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxAudioInstance", js_game_AudioEngineHelper_getMaxAudioInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentTime", js_game_AudioEngineHelper_getCurrentTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVolumeAll", js_game_AudioEngineHelper_setVolumeAll, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("PlayEffectT", js_game_AudioEngineHelper_PlayEffectT, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxAudioInstance", js_game_AudioEngineHelper_setMaxAudioInstance, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLoop", js_game_AudioEngineHelper_isLoop, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pauseAll", js_game_AudioEngineHelper_pauseAll, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("uncacheAll", js_game_AudioEngineHelper_uncacheAll, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVolume", js_game_AudioEngineHelper_setVolume, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("play2d", js_game_AudioEngineHelper_play2d, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getState", js_game_AudioEngineHelper_getState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resume", js_game_AudioEngineHelper_resume, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stop", js_game_AudioEngineHelper_stop, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDuration", js_game_AudioEngineHelper_getDuration, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLoop", js_game_AudioEngineHelper_setLoop, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SetEffectVolume", js_game_AudioEngineHelper_SetEffectVolume, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFinishCallback", js_game_AudioEngineHelper_setFinishCallback, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_AudioEngineHelper_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_AudioEngineHelper_class,
        dummy_constructor<AudioEngineHelper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "AudioEngineHelper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<AudioEngineHelper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_AudioEngineHelper_class;
        p->proto = jsb_AudioEngineHelper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_SafeSprite_class;
JSObject *jsb_SafeSprite_prototype;

bool js_game_SafeSprite_getScriptID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SafeSprite* cobj = (SafeSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_SafeSprite_getScriptID : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getScriptID();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_SafeSprite_getScriptID : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_SafeSprite_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        SafeSprite* ret = SafeSprite::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<SafeSprite>(cx, (SafeSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_SafeSprite_create : wrong number of arguments");
    return false;
}

bool js_game_SafeSprite_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    SafeSprite* cobj = new (std::nothrow) SafeSprite();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<SafeSprite> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "SafeSprite");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Sprite_prototype;

void js_SafeSprite_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SafeSprite)", obj);
}

void js_register_game_SafeSprite(JSContext *cx, JS::HandleObject global) {
    jsb_SafeSprite_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_SafeSprite_class->name = "SafeSprite";
    jsb_SafeSprite_class->addProperty = JS_PropertyStub;
    jsb_SafeSprite_class->delProperty = JS_DeletePropertyStub;
    jsb_SafeSprite_class->getProperty = JS_PropertyStub;
    jsb_SafeSprite_class->setProperty = JS_StrictPropertyStub;
    jsb_SafeSprite_class->enumerate = JS_EnumerateStub;
    jsb_SafeSprite_class->resolve = JS_ResolveStub;
    jsb_SafeSprite_class->convert = JS_ConvertStub;
    jsb_SafeSprite_class->finalize = js_SafeSprite_finalize;
    jsb_SafeSprite_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getScriptID", js_game_SafeSprite_getScriptID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_game_SafeSprite_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_SafeSprite_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Sprite_prototype),
        jsb_SafeSprite_class,
        js_game_SafeSprite_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "SafeSprite", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<SafeSprite> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_SafeSprite_class;
        p->proto = jsb_SafeSprite_prototype;
        p->parentProto = jsb_cocos2d_Sprite_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_ReSprite_class;
JSObject *jsb_ReSprite_prototype;

bool js_game_ReSprite_isReSpriteFlipX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ReSprite* cobj = (ReSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ReSprite_isReSpriteFlipX : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isReSpriteFlipX();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_ReSprite_isReSpriteFlipX : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_ReSprite_setReSpriteFlipX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ReSprite* cobj = (ReSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ReSprite_setReSpriteFlipX : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_game_ReSprite_setReSpriteFlipX : Error processing arguments");
        cobj->setReSpriteFlipX(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_ReSprite_setReSpriteFlipX : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_ReSprite_initWithFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ReSprite* cobj = (ReSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ReSprite_initWithFile : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ReSprite_initWithFile : Error processing arguments");
        bool ret = cobj->initWithFile(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_ReSprite_initWithFile : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_ReSprite_pointInSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ReSprite* cobj = (ReSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ReSprite_pointInSprite : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ReSprite_pointInSprite : Error processing arguments");
        bool ret = cobj->pointInSprite(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_ReSprite_pointInSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_ReSprite_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ReSprite_create : Error processing arguments");
        ReSprite* ret = ReSprite::create(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<ReSprite>(cx, (ReSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_ReSprite_create : wrong number of arguments");
    return false;
}

bool js_game_ReSprite_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    ReSprite* cobj = new (std::nothrow) ReSprite();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<ReSprite> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "ReSprite");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Sprite_prototype;

void js_ReSprite_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ReSprite)", obj);
}

void js_register_game_ReSprite(JSContext *cx, JS::HandleObject global) {
    jsb_ReSprite_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_ReSprite_class->name = "ReSprite";
    jsb_ReSprite_class->addProperty = JS_PropertyStub;
    jsb_ReSprite_class->delProperty = JS_DeletePropertyStub;
    jsb_ReSprite_class->getProperty = JS_PropertyStub;
    jsb_ReSprite_class->setProperty = JS_StrictPropertyStub;
    jsb_ReSprite_class->enumerate = JS_EnumerateStub;
    jsb_ReSprite_class->resolve = JS_ResolveStub;
    jsb_ReSprite_class->convert = JS_ConvertStub;
    jsb_ReSprite_class->finalize = js_ReSprite_finalize;
    jsb_ReSprite_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("isReSpriteFlipX", js_game_ReSprite_isReSpriteFlipX, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setReSpriteFlipX", js_game_ReSprite_setReSpriteFlipX, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithFile", js_game_ReSprite_initWithFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pointInSprite", js_game_ReSprite_pointInSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_game_ReSprite_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_ReSprite_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Sprite_prototype),
        jsb_ReSprite_class,
        js_game_ReSprite_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ReSprite", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<ReSprite> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_ReSprite_class;
        p->proto = jsb_ReSprite_prototype;
        p->parentProto = jsb_cocos2d_Sprite_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_PlatformManager_class;
JSObject *jsb_PlatformManager_prototype;

bool js_game_PlatformManager_reportNotification(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_PlatformManager_reportNotification : Error processing arguments");
        PlatformManager::reportNotification(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_reportNotification : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_getNetworkType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        int ret = (int)PlatformManager::getNetworkType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_getNetworkType : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_createNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_PlatformManager_createNode : Error processing arguments");
        cocos2d::Node* ret = PlatformManager::createNode(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_createNode : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_getDeviceType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = PlatformManager::getDeviceType();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_getDeviceType : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_getDeviceToken(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = PlatformManager::getDeviceToken();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_getDeviceToken : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_getMacAddress(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = PlatformManager::getMacAddress();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_getMacAddress : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        PlatformManager* ret = PlatformManager::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<PlatformManager>(cx, (PlatformManager*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_getInstance : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_getDeviceName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = PlatformManager::getDeviceName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_getDeviceName : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_setLangueIdentify(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_PlatformManager_setLangueIdentify : Error processing arguments");
        PlatformManager::setLangueIdentify(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_setLangueIdentify : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_setTextInPasteboard(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_PlatformManager_setTextInPasteboard : Error processing arguments");
        PlatformManager::setTextInPasteboard(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_setTextInPasteboard : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_getDeviceSystem(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = PlatformManager::getDeviceSystem();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_getDeviceSystem : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_logOutAndCallJS(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        PlatformManager::logOutAndCallJS();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_logOutAndCallJS : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_DestoryPlatform(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        PlatformManager::DestoryPlatform();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_DestoryPlatform : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_gameCall(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_game_PlatformManager_gameCall : Error processing arguments");
        PlatformManager::gameCall(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_gameCall : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_getPlatformId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        int ret = PlatformManager::getPlatformId();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_getPlatformId : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_getDeviceUid(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = PlatformManager::getDeviceUid();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_getDeviceUid : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_getValueForKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_PlatformManager_getValueForKey : Error processing arguments");
        std::string ret = PlatformManager::getValueForKey(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_getValueForKey : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_InitPlatform(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        PlatformManager::InitPlatform();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_InitPlatform : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_getLangueIdentify(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = PlatformManager::getLangueIdentify();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_getLangueIdentify : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_getDeviceUidType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = PlatformManager::getDeviceUidType();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_getDeviceUidType : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_sharedFaceBook(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_PlatformManager_sharedFaceBook : Error processing arguments");
        PlatformManager::sharedFaceBook(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_sharedFaceBook : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_getDeviceMemory(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = PlatformManager::getDeviceMemory();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_getDeviceMemory : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_getAppVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = PlatformManager::getAppVersion();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_getAppVersion : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_loginSuccessAndCallJS(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::vector<std::string> arg0;
        ok &= jsval_to_std_vector_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_PlatformManager_loginSuccessAndCallJS : Error processing arguments");
        PlatformManager::loginSuccessAndCallJS(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_loginSuccessAndCallJS : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_deleteAllNotification(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        PlatformManager::deleteAllNotification();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_deleteAllNotification : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_reportEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_PlatformManager_reportEvent : Error processing arguments");
        PlatformManager::reportEvent(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_reportEvent : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_setValueForKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_game_PlatformManager_setValueForKey : Error processing arguments");
        PlatformManager::setValueForKey(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_game_PlatformManager_setValueForKey : wrong number of arguments");
    return false;
}

bool js_game_PlatformManager_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    PlatformManager* cobj = new (std::nothrow) PlatformManager();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<PlatformManager> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "PlatformManager");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}



void js_PlatformManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PlatformManager)", obj);
}

void js_register_game_PlatformManager(JSContext *cx, JS::HandleObject global) {
    jsb_PlatformManager_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_PlatformManager_class->name = "PlatformManager";
    jsb_PlatformManager_class->addProperty = JS_PropertyStub;
    jsb_PlatformManager_class->delProperty = JS_DeletePropertyStub;
    jsb_PlatformManager_class->getProperty = JS_PropertyStub;
    jsb_PlatformManager_class->setProperty = JS_StrictPropertyStub;
    jsb_PlatformManager_class->enumerate = JS_EnumerateStub;
    jsb_PlatformManager_class->resolve = JS_ResolveStub;
    jsb_PlatformManager_class->convert = JS_ConvertStub;
    jsb_PlatformManager_class->finalize = js_PlatformManager_finalize;
    jsb_PlatformManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("reportNotification", js_game_PlatformManager_reportNotification, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNetworkType", js_game_PlatformManager_getNetworkType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createNode", js_game_PlatformManager_createNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDeviceType", js_game_PlatformManager_getDeviceType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDeviceToken", js_game_PlatformManager_getDeviceToken, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMacAddress", js_game_PlatformManager_getMacAddress, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInstance", js_game_PlatformManager_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDeviceName", js_game_PlatformManager_getDeviceName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLangueIdentify", js_game_PlatformManager_setLangueIdentify, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTextInPasteboard", js_game_PlatformManager_setTextInPasteboard, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDeviceSystem", js_game_PlatformManager_getDeviceSystem, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("logOutAndCallJS", js_game_PlatformManager_logOutAndCallJS, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("DestoryPlatform", js_game_PlatformManager_DestoryPlatform, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("gameCall", js_game_PlatformManager_gameCall, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPlatformId", js_game_PlatformManager_getPlatformId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDeviceUid", js_game_PlatformManager_getDeviceUid, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getValueForKey", js_game_PlatformManager_getValueForKey, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("InitPlatform", js_game_PlatformManager_InitPlatform, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLangueIdentify", js_game_PlatformManager_getLangueIdentify, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDeviceUidType", js_game_PlatformManager_getDeviceUidType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("sharedFaceBook", js_game_PlatformManager_sharedFaceBook, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDeviceMemory", js_game_PlatformManager_getDeviceMemory, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAppVersion", js_game_PlatformManager_getAppVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loginSuccessAndCallJS", js_game_PlatformManager_loginSuccessAndCallJS, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("deleteAllNotification", js_game_PlatformManager_deleteAllNotification, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("reportEvent", js_game_PlatformManager_reportEvent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setValueForKey", js_game_PlatformManager_setValueForKey, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_PlatformManager_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_PlatformManager_class,
        js_game_PlatformManager_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "PlatformManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<PlatformManager> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_PlatformManager_class;
        p->proto = jsb_PlatformManager_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_HttpDownloadManager_class;
JSObject *jsb_HttpDownloadManager_prototype;

bool js_game_HttpDownloadManager_isInDownLoadList(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    HttpDownloadManager* cobj = (HttpDownloadManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_HttpDownloadManager_isInDownLoadList : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_HttpDownloadManager_isInDownLoadList : Error processing arguments");
        bool ret = cobj->isInDownLoadList(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_HttpDownloadManager_isInDownLoadList : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_HttpDownloadManager_setHttpRequest(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    HttpDownloadManager* cobj = (HttpDownloadManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_HttpDownloadManager_setHttpRequest : Invalid Native Object");
    if (argc == 4) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        bool arg3;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        arg3 = JS::ToBoolean(args.get(3));
        JSB_PRECONDITION2(ok, cx, false, "js_game_HttpDownloadManager_setHttpRequest : Error processing arguments");
        bool ret = cobj->setHttpRequest(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_HttpDownloadManager_setHttpRequest : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_game_HttpDownloadManager_stopAllHttpRequest(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    HttpDownloadManager* cobj = (HttpDownloadManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_HttpDownloadManager_stopAllHttpRequest : Invalid Native Object");
    if (argc == 0) {
        cobj->stopAllHttpRequest();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_HttpDownloadManager_stopAllHttpRequest : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_HttpDownloadManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        HttpDownloadManager* ret = HttpDownloadManager::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<HttpDownloadManager>(cx, (HttpDownloadManager*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_HttpDownloadManager_getInstance : wrong number of arguments");
    return false;
}

bool js_game_HttpDownloadManager_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    HttpDownloadManager* cobj = new (std::nothrow) HttpDownloadManager();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<HttpDownloadManager> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "HttpDownloadManager");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}



void js_HttpDownloadManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HttpDownloadManager)", obj);
}

void js_register_game_HttpDownloadManager(JSContext *cx, JS::HandleObject global) {
    jsb_HttpDownloadManager_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_HttpDownloadManager_class->name = "HttpDownloadManager";
    jsb_HttpDownloadManager_class->addProperty = JS_PropertyStub;
    jsb_HttpDownloadManager_class->delProperty = JS_DeletePropertyStub;
    jsb_HttpDownloadManager_class->getProperty = JS_PropertyStub;
    jsb_HttpDownloadManager_class->setProperty = JS_StrictPropertyStub;
    jsb_HttpDownloadManager_class->enumerate = JS_EnumerateStub;
    jsb_HttpDownloadManager_class->resolve = JS_ResolveStub;
    jsb_HttpDownloadManager_class->convert = JS_ConvertStub;
    jsb_HttpDownloadManager_class->finalize = js_HttpDownloadManager_finalize;
    jsb_HttpDownloadManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("isInDownLoadList", js_game_HttpDownloadManager_isInDownLoadList, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setHttpRequest", js_game_HttpDownloadManager_setHttpRequest, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopAllHttpRequest", js_game_HttpDownloadManager_stopAllHttpRequest, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getInstance", js_game_HttpDownloadManager_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_HttpDownloadManager_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_HttpDownloadManager_class,
        js_game_HttpDownloadManager_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "HttpDownloadManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<HttpDownloadManager> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_HttpDownloadManager_class;
        p->proto = jsb_HttpDownloadManager_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_CURLHelper_class;
JSObject *jsb_CURLHelper_prototype;

bool js_game_CURLHelper_getLocalFileSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_CURLHelper_getLocalFileSize : Error processing arguments");
        long ret = CURLHelper::getLocalFileSize(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = long_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_CURLHelper_getLocalFileSize : wrong number of arguments");
    return false;
}

bool js_game_CURLHelper_getHttpString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_CURLHelper_getHttpString : Error processing arguments");
        std::string ret = CURLHelper::getHttpString(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_CURLHelper_getHttpString : wrong number of arguments");
    return false;
}

bool js_game_CURLHelper_downloadFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_game_CURLHelper_downloadFile : Error processing arguments");
        int ret = CURLHelper::downloadFile(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_CURLHelper_downloadFile : wrong number of arguments");
    return false;
}

bool js_game_CURLHelper_getDownloadFileSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_CURLHelper_getDownloadFileSize : Error processing arguments");
        long ret = CURLHelper::getDownloadFileSize(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = long_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_CURLHelper_getDownloadFileSize : wrong number of arguments");
    return false;
}

bool js_game_CURLHelper_getHttpHeader(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_CURLHelper_getHttpHeader : Error processing arguments");
        std::string ret = CURLHelper::getHttpHeader(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_CURLHelper_getHttpHeader : wrong number of arguments");
    return false;
}



void js_CURLHelper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CURLHelper)", obj);
}

void js_register_game_CURLHelper(JSContext *cx, JS::HandleObject global) {
    jsb_CURLHelper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_CURLHelper_class->name = "CURLHelper";
    jsb_CURLHelper_class->addProperty = JS_PropertyStub;
    jsb_CURLHelper_class->delProperty = JS_DeletePropertyStub;
    jsb_CURLHelper_class->getProperty = JS_PropertyStub;
    jsb_CURLHelper_class->setProperty = JS_StrictPropertyStub;
    jsb_CURLHelper_class->enumerate = JS_EnumerateStub;
    jsb_CURLHelper_class->resolve = JS_ResolveStub;
    jsb_CURLHelper_class->convert = JS_ConvertStub;
    jsb_CURLHelper_class->finalize = js_CURLHelper_finalize;
    jsb_CURLHelper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getLocalFileSize", js_game_CURLHelper_getLocalFileSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getHttpString", js_game_CURLHelper_getHttpString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("downloadFile", js_game_CURLHelper_downloadFile, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDownloadFileSize", js_game_CURLHelper_getDownloadFileSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getHttpHeader", js_game_CURLHelper_getHttpHeader, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_CURLHelper_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_CURLHelper_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "CURLHelper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<CURLHelper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_CURLHelper_class;
        p->proto = jsb_CURLHelper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_ProgressAction_class;
JSObject *jsb_ProgressAction_prototype;

bool js_game_ProgressAction_initWithDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProgressAction* cobj = (ProgressAction *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ProgressAction_initWithDuration : Invalid Native Object");
    if (argc == 4) {
        double arg0;
        double arg1;
        double arg2;
        std::function<void (cocos2d::Ref *, float)> arg3;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        do {
		    if(JS_TypeOfValue(cx, args.get(3)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(3)));
		        auto lambda = [=](cocos2d::Ref* larg0, float larg1) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[2];
		            do {
		            if (larg0) {
		                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)larg0);
		                largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
		            } else {
		                largv[0] = JSVAL_NULL;
		            }
		        } while (0);
		            largv[1] = DOUBLE_TO_JSVAL(larg1);
		            JS::RootedValue rval(cx);
		            bool ok = func->invoke(2, &largv[0], &rval);
		            if (!ok && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg3 = lambda;
		    }
		    else
		    {
		        arg3 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_game_ProgressAction_initWithDuration : Error processing arguments");
        bool ret = cobj->initWithDuration(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_ProgressAction_initWithDuration : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_game_ProgressAction_setProgressActionCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProgressAction* cobj = (ProgressAction *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ProgressAction_setProgressActionCallback : Invalid Native Object");
    if (argc == 1) {
        std::function<void (cocos2d::Ref *, float)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=](cocos2d::Ref* larg0, float larg1) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[2];
		            do {
		            if (larg0) {
		                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)larg0);
		                largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
		            } else {
		                largv[0] = JSVAL_NULL;
		            }
		        } while (0);
		            largv[1] = DOUBLE_TO_JSVAL(larg1);
		            JS::RootedValue rval(cx);
		            bool ok = func->invoke(2, &largv[0], &rval);
		            if (!ok && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg0 = lambda;
		    }
		    else
		    {
		        arg0 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_game_ProgressAction_setProgressActionCallback : Error processing arguments");
        cobj->setProgressActionCallback(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_ProgressAction_setProgressActionCallback : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_ProgressAction_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 3) {
            double arg0;
            ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
            if (!ok) { ok = true; break; }
            double arg1;
            ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
            if (!ok) { ok = true; break; }
            double arg2;
            ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
            if (!ok) { ok = true; break; }
            ProgressAction* ret = ProgressAction::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<ProgressAction>(cx, (ProgressAction*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 4) {
            double arg0;
            ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
            if (!ok) { ok = true; break; }
            double arg1;
            ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
            if (!ok) { ok = true; break; }
            double arg2;
            ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
            if (!ok) { ok = true; break; }
            std::function<void (cocos2d::Ref *, float)> arg3;
            do {
			    if(JS_TypeOfValue(cx, args.get(3)) == JSTYPE_FUNCTION)
			    {
			        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(3)));
			        auto lambda = [=](cocos2d::Ref* larg0, float larg1) -> void {
			            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
			            jsval largv[2];
			            do {
			            if (larg0) {
			                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)larg0);
			                largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
			            } else {
			                largv[0] = JSVAL_NULL;
			            }
			        } while (0);
			            largv[1] = DOUBLE_TO_JSVAL(larg1);
			            JS::RootedValue rval(cx);
			            bool ok = func->invoke(2, &largv[0], &rval);
			            if (!ok && JS_IsExceptionPending(cx)) {
			                JS_ReportPendingException(cx);
			            }
			        };
			        arg3 = lambda;
			    }
			    else
			    {
			        arg3 = nullptr;
			    }
			} while(0)
			;
            if (!ok) { ok = true; break; }
            ProgressAction* ret = ProgressAction::create(arg0, arg1, arg2, arg3);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<ProgressAction>(cx, (ProgressAction*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_game_ProgressAction_create : wrong number of arguments");
    return false;
}
bool js_game_ProgressAction_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    ProgressAction* cobj = new (std::nothrow) ProgressAction();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<ProgressAction> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "ProgressAction");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ActionInterval_prototype;

void js_ProgressAction_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProgressAction)", obj);
}

void js_register_game_ProgressAction(JSContext *cx, JS::HandleObject global) {
    jsb_ProgressAction_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_ProgressAction_class->name = "ProgressAction";
    jsb_ProgressAction_class->addProperty = JS_PropertyStub;
    jsb_ProgressAction_class->delProperty = JS_DeletePropertyStub;
    jsb_ProgressAction_class->getProperty = JS_PropertyStub;
    jsb_ProgressAction_class->setProperty = JS_StrictPropertyStub;
    jsb_ProgressAction_class->enumerate = JS_EnumerateStub;
    jsb_ProgressAction_class->resolve = JS_ResolveStub;
    jsb_ProgressAction_class->convert = JS_ConvertStub;
    jsb_ProgressAction_class->finalize = js_ProgressAction_finalize;
    jsb_ProgressAction_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("initWithDuration", js_game_ProgressAction_initWithDuration, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setProgressActionCallback", js_game_ProgressAction_setProgressActionCallback, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_game_ProgressAction_create, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_ProgressAction_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ActionInterval_prototype),
        jsb_ProgressAction_class,
        js_game_ProgressAction_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ProgressAction", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<ProgressAction> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_ProgressAction_class;
        p->proto = jsb_ProgressAction_prototype;
        p->parentProto = jsb_cocos2d_ActionInterval_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_Account_class;
JSObject *jsb_Account_prototype;

bool js_game_Account_getLoginUid(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Account* cobj = (Account *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_Account_getLoginUid : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getLoginUid();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_Account_getLoginUid : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_Account_buy(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Account* cobj = (Account *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_Account_buy : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_Account_buy : Error processing arguments");
        cobj->buy(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_Account_buy : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_Account_center(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Account* cobj = (Account *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_Account_center : Invalid Native Object");
    if (argc == 0) {
        cobj->center();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_Account_center : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_Account_doLoginGame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Account* cobj = (Account *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_Account_doLoginGame : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_Account_doLoginGame : Error processing arguments");
        cobj->doLoginGame(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_Account_doLoginGame : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_Account_switchAccount(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Account* cobj = (Account *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_Account_switchAccount : Invalid Native Object");
    if (argc == 0) {
        cobj->switchAccount();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_Account_switchAccount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_Account_isLogin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Account* cobj = (Account *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_Account_isLogin : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isLogin();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_Account_isLogin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_Account_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Account* cobj = (Account *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_Account_init : Invalid Native Object");
    if (argc == 0) {
        cobj->init();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_Account_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_Account_logout(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Account* cobj = (Account *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_Account_logout : Invalid Native Object");
    if (argc == 0) {
        cobj->logout();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_Account_logout : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_Account_clearLoginUid(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Account* cobj = (Account *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_Account_clearLoginUid : Invalid Native Object");
    if (argc == 0) {
        cobj->clearLoginUid();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_Account_clearLoginUid : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_Account_exit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Account* cobj = (Account *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_Account_exit : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->exit();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_Account_exit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_Account_login(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Account* cobj = (Account *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_Account_login : Invalid Native Object");
    if (argc == 0) {
        cobj->login();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_Account_login : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_Account_doLogoutGame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Account* cobj = (Account *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_Account_doLogoutGame : Invalid Native Object");
    if (argc == 0) {
        cobj->doLogoutGame();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_Account_doLogoutGame : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_Account_gameCall(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Account* cobj = (Account *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_Account_gameCall : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_game_Account_gameCall : Error processing arguments");
        std::string ret = cobj->gameCall(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_Account_gameCall : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_game_Account_platformCall(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Account* cobj = (Account *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_Account_platformCall : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_game_Account_platformCall : Error processing arguments");
        std::string ret = cobj->platformCall(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_Account_platformCall : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_game_Account_shareInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        Account* ret = Account::shareInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<Account>(cx, (Account*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_Account_shareInstance : wrong number of arguments");
    return false;
}

bool js_game_Account_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    Account* cobj = new (std::nothrow) Account();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<Account> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "Account");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}



void js_Account_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Account)", obj);
}

void js_register_game_Account(JSContext *cx, JS::HandleObject global) {
    jsb_Account_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_Account_class->name = "Account";
    jsb_Account_class->addProperty = JS_PropertyStub;
    jsb_Account_class->delProperty = JS_DeletePropertyStub;
    jsb_Account_class->getProperty = JS_PropertyStub;
    jsb_Account_class->setProperty = JS_StrictPropertyStub;
    jsb_Account_class->enumerate = JS_EnumerateStub;
    jsb_Account_class->resolve = JS_ResolveStub;
    jsb_Account_class->convert = JS_ConvertStub;
    jsb_Account_class->finalize = js_Account_finalize;
    jsb_Account_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getLoginUid", js_game_Account_getLoginUid, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("buy", js_game_Account_buy, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("center", js_game_Account_center, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("doLoginGame", js_game_Account_doLoginGame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("switchAccount", js_game_Account_switchAccount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLogin", js_game_Account_isLogin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_game_Account_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("logout", js_game_Account_logout, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clearLoginUid", js_game_Account_clearLoginUid, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("exit", js_game_Account_exit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("login", js_game_Account_login, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("doLogoutGame", js_game_Account_doLogoutGame, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("gameCall", js_game_Account_gameCall, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("platformCall", js_game_Account_platformCall, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("shareInstance", js_game_Account_shareInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_Account_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_Account_class,
        js_game_Account_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Account", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<Account> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_Account_class;
        p->proto = jsb_Account_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_game(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "cj", &ns);

    js_register_game_CURLHelper(cx, ns);
    js_register_game_PlatformManager(cx, ns);
    js_register_game_ReSprite(cx, ns);
    js_register_game_HttpDownloadManager(cx, ns);
    js_register_game_Account(cx, ns);
    js_register_game_Util(cx, ns);
    js_register_game_AudioEngineHelper(cx, ns);
    js_register_game_SafeSprite(cx, ns);
    js_register_game_GameSession(cx, ns);
    js_register_game_ProgressAction(cx, ns);
}

