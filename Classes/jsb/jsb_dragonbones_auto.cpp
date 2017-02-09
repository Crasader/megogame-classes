#include "jsb_dragonbones_auto.hpp"
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
JSClass  *jsb_dragonBones_Frame_class;
JSObject *jsb_dragonBones_Frame_prototype;

bool js_dragonbones_Frame_getaction(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Frame* cobj = (dragonBones::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_Frame_getaction : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getaction();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_Frame_getaction : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_Frame_getevent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Frame* cobj = (dragonBones::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_Frame_getevent : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getevent();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_Frame_getevent : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_Frame_getframeType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Frame* cobj = (dragonBones::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_Frame_getframeType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getframeType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_Frame_getframeType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_Frame_dispose(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Frame* cobj = (dragonBones::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_Frame_dispose : Invalid Native Object");
    if (argc == 0) {
        cobj->dispose();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_Frame_dispose : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_Frame_getduration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Frame* cobj = (dragonBones::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_Frame_getduration : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getduration();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_Frame_getduration : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_Frame_getsound(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Frame* cobj = (dragonBones::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_Frame_getsound : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getsound();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_Frame_getsound : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_Frame_geteventParameters(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Frame* cobj = (dragonBones::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_Frame_geteventParameters : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->geteventParameters();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_Frame_geteventParameters : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_Frame_getposition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Frame* cobj = (dragonBones::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_Frame_getposition : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getposition();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_Frame_getposition : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}


void js_dragonBones_Frame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Frame)", obj);
}

void js_register_dragonbones_Frame(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_Frame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_Frame_class->name = "Frame";
    jsb_dragonBones_Frame_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_Frame_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_Frame_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_Frame_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_Frame_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_Frame_class->resolve = JS_ResolveStub;
    jsb_dragonBones_Frame_class->convert = JS_ConvertStub;
    jsb_dragonBones_Frame_class->finalize = js_dragonBones_Frame_finalize;
    jsb_dragonBones_Frame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getaction", js_dragonbones_Frame_getaction, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getevent", js_dragonbones_Frame_getevent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getframeType", js_dragonbones_Frame_getframeType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("dispose", js_dragonbones_Frame_dispose, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getduration", js_dragonbones_Frame_getduration, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getsound", js_dragonbones_Frame_getsound, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("geteventParameters", js_dragonbones_Frame_geteventParameters, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getposition", js_dragonbones_Frame_getposition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_dragonBones_Frame_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_dragonBones_Frame_class,
        dummy_constructor<dragonBones::Frame>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Frame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::Frame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_Frame_class;
        p->proto = jsb_dragonBones_Frame_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_EventData_class;
JSObject *jsb_dragonBones_EventData_prototype;

bool js_dragonbones_EventData_getBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::EventData* cobj = (dragonBones::EventData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_EventData_getBone : Invalid Native Object");
    if (argc == 0) {
        dragonBones::Bone* ret = cobj->getBone();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Bone>(cx, (dragonBones::Bone*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_EventData_getBone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_EventData_getFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::EventData* cobj = (dragonBones::EventData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_EventData_getFrame : Invalid Native Object");
    if (argc == 0) {
        dragonBones::Frame* ret = cobj->getFrame();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Frame>(cx, (dragonBones::Frame*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_EventData_getFrame : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_EventData_getType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::EventData* cobj = (dragonBones::EventData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_EventData_getType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_EventData_getType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_EventData_getArmature(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::EventData* cobj = (dragonBones::EventData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_EventData_getArmature : Invalid Native Object");
    if (argc == 0) {
        dragonBones::Armature* ret = cobj->getArmature();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Armature>(cx, (dragonBones::Armature*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_EventData_getArmature : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_EventData_getCurrentEventTargetId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::EventData* cobj = (dragonBones::EventData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_EventData_getCurrentEventTargetId : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getCurrentEventTargetId();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_EventData_getCurrentEventTargetId : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_EventData_getFrameLabel(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::EventData* cobj = (dragonBones::EventData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_EventData_getFrameLabel : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getFrameLabel();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_EventData_getFrameLabel : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_EventData_getSound(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::EventData* cobj = (dragonBones::EventData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_EventData_getSound : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getSound();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_EventData_getSound : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_EventData_getStringType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::EventData* cobj = (dragonBones::EventData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_EventData_getStringType : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getStringType();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_EventData_getStringType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_EventData_getAnimationName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::EventData* cobj = (dragonBones::EventData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_EventData_getAnimationName : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getAnimationName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_EventData_getAnimationName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_EventData_typeToString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        dragonBones::EventData::EventType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_EventData_typeToString : Error processing arguments");
        const std::string& ret = dragonBones::EventData::typeToString(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_dragonbones_EventData_typeToString : wrong number of arguments");
    return false;
}

bool js_dragonbones_EventData_returnObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        dragonBones::EventData* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::EventData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_EventData_returnObject : Error processing arguments");
        dragonBones::EventData::returnObject(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_dragonbones_EventData_returnObject : wrong number of arguments");
    return false;
}

bool js_dragonbones_EventData_clearObjects(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        dragonBones::EventData::clearObjects();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_dragonbones_EventData_clearObjects : wrong number of arguments");
    return false;
}

bool js_dragonbones_EventData_borrowObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        dragonBones::EventData::EventType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_EventData_borrowObject : Error processing arguments");
        dragonBones::EventData* ret = dragonBones::EventData::borrowObject(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::EventData>(cx, (dragonBones::EventData*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_dragonbones_EventData_borrowObject : wrong number of arguments");
    return false;
}

bool js_dragonbones_EventData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::EventData* cobj = new (std::nothrow) dragonBones::EventData();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<dragonBones::EventData> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::EventData");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}



void js_dragonBones_EventData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (EventData)", obj);
}

void js_register_dragonbones_EventData(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_EventData_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_EventData_class->name = "EventData";
    jsb_dragonBones_EventData_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_EventData_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_EventData_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_EventData_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_EventData_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_EventData_class->resolve = JS_ResolveStub;
    jsb_dragonBones_EventData_class->convert = JS_ConvertStub;
    jsb_dragonBones_EventData_class->finalize = js_dragonBones_EventData_finalize;
    jsb_dragonBones_EventData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getBone", js_dragonbones_EventData_getBone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFrame", js_dragonbones_EventData_getFrame, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getType", js_dragonbones_EventData_getType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getArmature", js_dragonbones_EventData_getArmature, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentEventTargetId", js_dragonbones_EventData_getCurrentEventTargetId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFrameLabel", js_dragonbones_EventData_getFrameLabel, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSound", js_dragonbones_EventData_getSound, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStringType", js_dragonbones_EventData_getStringType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnimationName", js_dragonbones_EventData_getAnimationName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("typeToString", js_dragonbones_EventData_typeToString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("returnObject", js_dragonbones_EventData_returnObject, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clearObjects", js_dragonbones_EventData_clearObjects, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("borrowObject", js_dragonbones_EventData_borrowObject, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_dragonBones_EventData_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_dragonBones_EventData_class,
        js_dragonbones_EventData_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "EventData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::EventData> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_EventData_class;
        p->proto = jsb_dragonBones_EventData_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_DBCCArmatureNode_class;
JSObject *jsb_dragonBones_DBCCArmatureNode_prototype;

bool js_dragonbones_DBCCArmatureNode_getIsOpactityAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_getIsOpactityAnimation : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getIsOpactityAnimation();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_getIsOpactityAnimation : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_getFrameByFrameEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_getFrameByFrameEvent : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_getFrameByFrameEvent : Error processing arguments");
        dragonBones::Frame* ret = cobj->getFrameByFrameEvent(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Frame>(cx, (dragonBones::Frame*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_getFrameByFrameEvent : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_getDBADuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_getDBADuration : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_getDBADuration : Error processing arguments");
        int ret = cobj->getDBADuration(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_getDBADuration : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_setSlotDisplaySpriteFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_setSlotDisplaySpriteFrame : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        cocos2d::SpriteFrame* arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::SpriteFrame*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_setSlotDisplaySpriteFrame : Error processing arguments");
        cobj->setSlotDisplaySpriteFrame(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_setSlotDisplaySpriteFrame : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_getSlotGlobalPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_getSlotGlobalPosition : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_getSlotGlobalPosition : Error processing arguments");
        cocos2d::Vec2 ret = cobj->getSlotGlobalPosition(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_getSlotGlobalPosition : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_registerEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_registerEvent : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_registerEvent : Error processing arguments");
        cobj->registerEvent(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_registerEvent : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_setSlotDisplayTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_setSlotDisplayTexture : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_setSlotDisplayTexture : Error processing arguments");
        cobj->setSlotDisplayTexture(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_setSlotDisplayTexture : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_stopAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_stopAnimation : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        int arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_stopAnimation : Error processing arguments");
        cobj->stopAnimation(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_stopAnimation : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_setGLShaderProgram(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_setGLShaderProgram : Invalid Native Object");
    if (argc == 1) {
        cocos2d::GLProgram* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::GLProgram*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_setGLShaderProgram : Error processing arguments");
        cobj->setGLShaderProgram(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_setGLShaderProgram : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_getFrameByFrameName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_getFrameByFrameName : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_getFrameByFrameName : Error processing arguments");
        dragonBones::Frame* ret = cobj->getFrameByFrameName(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Frame>(cx, (dragonBones::Frame*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_getFrameByFrameName : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_getBlendFunc : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        jsval jsret = JSVAL_NULL;
        jsret = blendfunc_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_getBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_getCCSlotSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_getCCSlotSprite : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_getCCSlotSprite : Error processing arguments");
        cocos2d::Sprite* ret = cobj->getCCSlotSprite(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_getCCSlotSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_playAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_playAnimation : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        int arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_playAnimation : Error processing arguments");
        cobj->playAnimation(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_playAnimation : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_getInnerBoundingBox(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_getInnerBoundingBox : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Rect ret = cobj->getInnerBoundingBox();
        jsval jsret = JSVAL_NULL;
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_getInnerBoundingBox : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_getScriptID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_getScriptID : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getScriptID();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_getScriptID : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_getFrameRate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_getFrameRate : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getFrameRate();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_getFrameRate : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_setBlendFunc : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BlendFunc arg0;
        ok &= jsval_to_blendfunc(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_setBlendFunc : Error processing arguments");
        cobj->setBlendFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_setBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_playOpacityAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_playOpacityAnimation : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_playOpacityAnimation : Error processing arguments");
        cobj->playOpacityAnimation(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_playOpacityAnimation : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_pauseAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_pauseAnimation : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_pauseAnimation : Error processing arguments");
        cobj->pauseAnimation(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_pauseAnimation : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_getSlotVisible(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_getSlotVisible : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_getSlotVisible : Error processing arguments");
        bool ret = cobj->getSlotVisible(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_getSlotVisible : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_setSlotVisible(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCArmatureNode_setSlotVisible : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_setSlotVisible : Error processing arguments");
        cobj->setSlotVisible(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_setSlotVisible : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_dragonbones_DBCCArmatureNode_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        dragonBones::DBCCArmature* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::DBCCArmature*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCArmatureNode_create : Error processing arguments");
        dragonBones::DBCCArmatureNode* ret = dragonBones::DBCCArmatureNode::create(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_dragonbones_DBCCArmatureNode_create : wrong number of arguments");
    return false;
}

bool js_dragonbones_DBCCArmatureNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::DBCCArmatureNode* cobj = new (std::nothrow) dragonBones::DBCCArmatureNode();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<dragonBones::DBCCArmatureNode> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::DBCCArmatureNode");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_dragonBones_DBCCArmatureNode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (DBCCArmatureNode)", obj);
}

void js_register_dragonbones_DBCCArmatureNode(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_DBCCArmatureNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_DBCCArmatureNode_class->name = "DBCCArmatureNode";
    jsb_dragonBones_DBCCArmatureNode_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCArmatureNode_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_DBCCArmatureNode_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCArmatureNode_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_DBCCArmatureNode_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_DBCCArmatureNode_class->resolve = JS_ResolveStub;
    jsb_dragonBones_DBCCArmatureNode_class->convert = JS_ConvertStub;
    jsb_dragonBones_DBCCArmatureNode_class->finalize = js_dragonBones_DBCCArmatureNode_finalize;
    jsb_dragonBones_DBCCArmatureNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getIsOpactityAnimation", js_dragonbones_DBCCArmatureNode_getIsOpactityAnimation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFrameByFrameEvent", js_dragonbones_DBCCArmatureNode_getFrameByFrameEvent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDBADuration", js_dragonbones_DBCCArmatureNode_getDBADuration, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSlotDisplaySpriteFrame", js_dragonbones_DBCCArmatureNode_setSlotDisplaySpriteFrame, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSlotGlobalPosition", js_dragonbones_DBCCArmatureNode_getSlotGlobalPosition, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("registerEvent", js_dragonbones_DBCCArmatureNode_registerEvent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSlotDisplayTexture", js_dragonbones_DBCCArmatureNode_setSlotDisplayTexture, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopAnimation", js_dragonbones_DBCCArmatureNode_stopAnimation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setGLShaderProgram", js_dragonbones_DBCCArmatureNode_setGLShaderProgram, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFrameByFrameName", js_dragonbones_DBCCArmatureNode_getFrameByFrameName, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBlendFunc", js_dragonbones_DBCCArmatureNode_getBlendFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCCSlotSprite", js_dragonbones_DBCCArmatureNode_getCCSlotSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("playAnimation", js_dragonbones_DBCCArmatureNode_playAnimation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInnerBoundingBox", js_dragonbones_DBCCArmatureNode_getInnerBoundingBox, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getScriptID", js_dragonbones_DBCCArmatureNode_getScriptID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFrameRate", js_dragonbones_DBCCArmatureNode_getFrameRate, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBlendFunc", js_dragonbones_DBCCArmatureNode_setBlendFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("playOpacityAnimation", js_dragonbones_DBCCArmatureNode_playOpacityAnimation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pauseAnimation", js_dragonbones_DBCCArmatureNode_pauseAnimation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSlotVisible", js_dragonbones_DBCCArmatureNode_getSlotVisible, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSlotVisible", js_dragonbones_DBCCArmatureNode_setSlotVisible, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_dragonbones_DBCCArmatureNode_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_dragonBones_DBCCArmatureNode_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_dragonBones_DBCCArmatureNode_class,
        js_dragonbones_DBCCArmatureNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "DBCCArmatureNode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::DBCCArmatureNode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_DBCCArmatureNode_class;
        p->proto = jsb_dragonBones_DBCCArmatureNode_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_DBCCFactory_class;
JSObject *jsb_dragonBones_DBCCFactory_prototype;

bool js_dragonbones_DBCCFactory_removeAllDBData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCFactory_removeAllDBData : Invalid Native Object");
    if (argc == 0) {
        cobj->removeAllDBData();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCFactory_removeAllDBData : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_DBCCFactory_buildArmatureNodeWithTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCFactory_buildArmatureNodeWithTag : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCFactory_buildArmatureNodeWithTag : Error processing arguments");
        dragonBones::DBCCArmatureNode* ret = cobj->buildArmatureNodeWithTag(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCFactory_buildArmatureNodeWithTag : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCFactory_loadTextureWithPlist(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCFactory_loadTextureWithPlist : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCFactory_loadTextureWithPlist : Error processing arguments");
        bool ret = cobj->loadTextureWithPlist(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCFactory_loadTextureWithPlist : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCFactory_getTextureSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCFactory_getTextureSprite : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCFactory_getTextureSprite : Error processing arguments");
        cocos2d::Sprite* ret = cobj->getTextureSprite(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCFactory_getTextureSprite : Error processing arguments");
        cocos2d::Sprite* ret = cobj->getTextureSprite(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        const dragonBones::DisplayData* arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        do {
            if (args.get(2).isNull()) { arg2 = nullptr; break; }
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (const dragonBones::DisplayData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCFactory_getTextureSprite : Error processing arguments");
        cocos2d::Sprite* ret = cobj->getTextureSprite(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCFactory_getTextureSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCFactory_loadDragonBonesDataEasy(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCFactory_loadDragonBonesDataEasy : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCFactory_loadDragonBonesDataEasy : Error processing arguments");
        bool ret = cobj->loadDragonBonesDataEasy(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCFactory_loadDragonBonesDataEasy : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCFactory_hasDragonBones(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCFactory_hasDragonBones : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCFactory_hasDragonBones : Error processing arguments");
        bool ret = cobj->hasDragonBones(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCFactory_hasDragonBones : Error processing arguments");
        bool ret = cobj->hasDragonBones(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCFactory_hasDragonBones : Error processing arguments");
        bool ret = cobj->hasDragonBones(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCFactory_hasDragonBones : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCFactory_removeAllTextureAtlas(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCFactory_removeAllTextureAtlas : Invalid Native Object");
    if (argc == 0) {
        cobj->removeAllTextureAtlas();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCFactory_removeAllTextureAtlas : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_DBCCFactory_refreshAllTextureAtlasTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCFactory_refreshAllTextureAtlasTexture : Invalid Native Object");
    if (argc == 0) {
        cobj->refreshAllTextureAtlasTexture();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCFactory_refreshAllTextureAtlasTexture : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_dragonbones_DBCCFactory_loadTextureWithXML(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCFactory_loadTextureWithXML : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCFactory_loadTextureWithXML : Error processing arguments");
        bool ret = cobj->loadTextureWithXML(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCFactory_loadTextureWithXML : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCFactory_removeTextureData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCFactory_removeTextureData : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCFactory_removeTextureData : Error processing arguments");
        cobj->removeTextureData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCFactory_removeTextureData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCFactory_refreshTextureAtlasTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCFactory_refreshTextureAtlasTexture : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCFactory_refreshTextureAtlasTexture : Error processing arguments");
        cobj->refreshTextureAtlasTexture(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCFactory_refreshTextureAtlasTexture : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCFactory_buildArmatureNodeWithDragonBonesDataAndTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCFactory_buildArmatureNodeWithDragonBonesDataAndTexture : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCFactory_buildArmatureNodeWithDragonBonesDataAndTexture : Error processing arguments");
        dragonBones::DBCCArmatureNode* ret = cobj->buildArmatureNodeWithDragonBonesDataAndTexture(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCFactory_buildArmatureNodeWithDragonBonesDataAndTexture : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_dragonbones_DBCCFactory_removeDBData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCFactory_removeDBData : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCFactory_removeDBData : Error processing arguments");
        cobj->removeDBData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCFactory_removeDBData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCFactory_loadTextureAndBuildArmatureNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_dragonbones_DBCCFactory_loadTextureAndBuildArmatureNode : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_dragonbones_DBCCFactory_loadTextureAndBuildArmatureNode : Error processing arguments");
        dragonBones::DBCCArmatureNode* ret = cobj->loadTextureAndBuildArmatureNode(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_dragonbones_DBCCFactory_loadTextureAndBuildArmatureNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_dragonbones_DBCCFactory_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        dragonBones::DBCCFactory::destroyInstance();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_dragonbones_DBCCFactory_destroyInstance : wrong number of arguments");
    return false;
}

bool js_dragonbones_DBCCFactory_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        dragonBones::DBCCFactory* ret = dragonBones::DBCCFactory::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCFactory>(cx, (dragonBones::DBCCFactory*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_dragonbones_DBCCFactory_getInstance : wrong number of arguments");
    return false;
}

bool js_dragonbones_DBCCFactory_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::DBCCFactory* cobj = new (std::nothrow) dragonBones::DBCCFactory();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<dragonBones::DBCCFactory> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::DBCCFactory");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}



void js_dragonBones_DBCCFactory_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (DBCCFactory)", obj);
}

void js_register_dragonbones_DBCCFactory(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_DBCCFactory_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_DBCCFactory_class->name = "DBCCFactory";
    jsb_dragonBones_DBCCFactory_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCFactory_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_DBCCFactory_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCFactory_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_DBCCFactory_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_DBCCFactory_class->resolve = JS_ResolveStub;
    jsb_dragonBones_DBCCFactory_class->convert = JS_ConvertStub;
    jsb_dragonBones_DBCCFactory_class->finalize = js_dragonBones_DBCCFactory_finalize;
    jsb_dragonBones_DBCCFactory_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("removeAllDBData", js_dragonbones_DBCCFactory_removeAllDBData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("buildArmatureNodeWithTag", js_dragonbones_DBCCFactory_buildArmatureNodeWithTag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadTextureWithPlist", js_dragonbones_DBCCFactory_loadTextureWithPlist, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTextureSprite", js_dragonbones_DBCCFactory_getTextureSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadDragonBonesDataEasy", js_dragonbones_DBCCFactory_loadDragonBonesDataEasy, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("hasDragonBones", js_dragonbones_DBCCFactory_hasDragonBones, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAllTextureAtlas", js_dragonbones_DBCCFactory_removeAllTextureAtlas, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("refreshAllTextureAtlasTexture", js_dragonbones_DBCCFactory_refreshAllTextureAtlasTexture, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadTextureWithXML", js_dragonbones_DBCCFactory_loadTextureWithXML, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeTextureData", js_dragonbones_DBCCFactory_removeTextureData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("refreshTextureAtlasTexture", js_dragonbones_DBCCFactory_refreshTextureAtlasTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("buildArmatureNodeWithDragonBonesDataAndTexture", js_dragonbones_DBCCFactory_buildArmatureNodeWithDragonBonesDataAndTexture, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeDBData", js_dragonbones_DBCCFactory_removeDBData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadTextureAndBuildArmatureNode", js_dragonbones_DBCCFactory_loadTextureAndBuildArmatureNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("destroyInstance", js_dragonbones_DBCCFactory_destroyInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInstance", js_dragonbones_DBCCFactory_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_dragonBones_DBCCFactory_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_dragonBones_DBCCFactory_class,
        js_dragonbones_DBCCFactory_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "DBCCFactory", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::DBCCFactory> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_DBCCFactory_class;
        p->proto = jsb_dragonBones_DBCCFactory_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_dragonbones(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "db", &ns);

    js_register_dragonbones_DBCCArmatureNode(cx, ns);
    js_register_dragonbones_Frame(cx, ns);
    js_register_dragonbones_DBCCFactory(cx, ns);
    js_register_dragonbones_EventData(cx, ns);
}

