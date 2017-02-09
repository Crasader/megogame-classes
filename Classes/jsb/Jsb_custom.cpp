//
//  Common.cpp
//  MegoGame
//
//  Created by howe on 15/4/3.
//
//

#include "Jsb_custom.h"
#include "jsb_game_auto.hpp"
#include "jsb_dragonbones_auto.hpp"
#include "cocos2d.h"

#include "../common/Util.h"
#include "../common/GameFileUtils.h"
#include "cocos2d_specifics.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "platform/win32/Win32Platform.h"
#endif
// add by howe
void init_custom_jsb()
{
    SET_FILEUTILS_DELEGATE();
    ScriptingCore* sc = ScriptingCore::getInstance();
    sc->addRegisterCallback(register_all_dragonbones);
    
    sc->addRegisterCallback(register_all_game);
    
    sc->addRegisterCallback(__register_custom_jsb_all);
    
}

bool CallMessageBox(JSContext *cx,uint32_t argc,jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        cocos2d::MessageBox(arg0.c_str(), arg1.c_str());
        return true;
    }
    else if (argc == 1)
    {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        cocos2d::MessageBox(arg0.c_str(), "Alert");
    }
    return false;
}
bool saveStringToFile(JSContext *cx,uint32_t argc,jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2)
    {
        std::string fullpath;
        std::string content;
        ok &= jsval_to_std_string(cx, args.get(0), &fullpath);
        ok &= jsval_to_std_string(cx, args.get(1), &content);
        
        return Util::createFile(fullpath, content);
    }
    return false;
}
bool getGlobalTouchCounts(JSContext *cx,uint32_t argc,jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        auto touches = cocos2d::Director::getInstance()->getOpenGLView()->getAllTouches();

        int ret = (int)touches.size();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "getGlobalTouchCounts: wrong number of arguments");
    return false;
}

bool getDesktopDirectory(JSContext *cx,uint32_t argc,jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string path("");
        
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        path = Win32Platform::getDesktopDirectory();
        #endif
        
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, path);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "getDesktopDirectory: wrong number of arguments");
    return false;
}

void __register_custom_jsb_all(JSContext* cx, JS::HandleObject obj)
{
    JS_DefineFunction(cx,obj ,"MessageBox",CallMessageBox,2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx,obj ,"saveStringToFile",saveStringToFile,2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx,obj ,"getGlobalTouchCounts",getGlobalTouchCounts,0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx,obj ,"getDesktopDirectory",getDesktopDirectory,0, JSPROP_ENUMERATE | JSPROP_PERMANENT);


}