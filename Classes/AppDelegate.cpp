#include "AppDelegate.h"

#include "SimpleAudioEngine.h"
#include "jsb_cocos2dx_auto.hpp"
#include "jsb_cocos2dx_ui_auto.hpp"
#include "jsb_cocos2dx_studio_auto.hpp"
#include "jsb_cocos2dx_builder_auto.hpp"
#include "jsb_cocos2dx_spine_auto.hpp"
#include "jsb_cocos2dx_extension_auto.hpp"
#include "jsb_cocos2dx_3d_auto.hpp"
#include "jsb_cocos2dx_3d_extension_auto.hpp"
#include "3d/jsb_cocos2dx_3d_manual.h"
#include "ui/jsb_cocos2dx_ui_manual.h"
#include "cocostudio/jsb_cocos2dx_studio_manual.h"
#include "cocosbuilder/js_bindings_ccbreader.h"
#include "spine/jsb_cocos2dx_spine_manual.h"
#include "extension/jsb_cocos2dx_extension_manual.h"
#include "localstorage/js_bindings_system_registration.h"
#include "chipmunk/js_bindings_chipmunk_registration.h"
#include "jsb_opengl_registration.h"
#include "network/XMLHTTPRequest.h"
#include "network/jsb_websocket.h"
#include "network/jsb_socketio.h"
#include "jsb_cocos2dx_physics3d_auto.hpp"
#include "physics3d/jsb_cocos2dx_physics3d_manual.h"
#include "jsb_cocos2dx_navmesh_auto.hpp"
#include "navmesh/jsb_cocos2dx_navmesh_manual.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "jsb_cocos2dx_experimental_video_auto.hpp"
#include "experimental/jsb_cocos2dx_experimental_video_manual.h"
#include "jsb_cocos2dx_experimental_webView_auto.hpp"
#include "experimental/jsb_cocos2dx_experimental_webView_manual.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/CCJavascriptJavaBridge.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "platform/ios/JavaScriptObjCBridge.h"
#endif


/** our custom headers here!!!!!  begin **/
#include "platform/PlatformManager.h"
#include "jsb/Jsb_custom.h"
#include "common/Util.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    #include "platform/win32/Win32Platform.h"
#endif

#ifdef ANDROID_COMM_VERSION
#include "platform_android.h"
#include "PlatformMgr.h"
#include "NativeModule.h"
#endif
/** our custom headers here!!!!!  end **/

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
    PlatformManager::InitPlatform();
}

AppDelegate::~AppDelegate()
{
    ScriptEngineManager::destroyInstance();
    
    cocos2d::experimental::AudioEngine::end();
    
    PlatformManager::DestoryPlatform();
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        glview = cocos2d::GLViewImpl::create("MegoGame");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        // Edit by howe
        std::string destopPath = Win32Platform::getDesktopDirectory() + "winsize.txt";
		if (FileUtils::getInstance()->isFileExist(destopPath))
		{
			auto fileData = FileUtils::getInstance()->getStringFromFile(destopPath);
			std::vector<std::string> arr;
            Util::StrSplit(fileData, "-", arr);
			int width = atoi(arr[0].c_str());
			int height = atoi(arr[1].c_str());
            if(arr.size() == 3){
                PlatformManager::getInstance()->setLangueIdentify(arr[2]);
            }
			glview = cocos2d::GLViewImpl::createWithRect("MegoGame", Rect(0, 0, width, height));
		}else
		{
			glview = cocos2d::GLViewImpl::createWithRect("MegoGame", Rect(0, 0, 960, 640));
		}
#else
        glview = cocos2d::GLViewImpl::createWithRect("MegoGame", Rect(0,0,960,640));
#endif
        director->setOpenGLView(glview);
}
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    ScriptingCore* sc = ScriptingCore::getInstance();
    sc->addRegisterCallback(register_all_cocos2dx);
    sc->addRegisterCallback(register_cocos2dx_js_core);
    sc->addRegisterCallback(jsb_register_system);
    
    // extension can be commented out to reduce the package
    sc->addRegisterCallback(register_all_cocos2dx_extension);
    sc->addRegisterCallback(register_all_cocos2dx_extension_manual);
    
    // chipmunk can be commented out to reduce the package
//    sc->addRegisterCallback(jsb_register_chipmunk);
    // opengl can be commented out to reduce the package
    sc->addRegisterCallback(JSB_register_opengl);
    
    // builder can be commented out to reduce the package
//    sc->addRegisterCallback(register_all_cocos2dx_builder);
//    sc->addRegisterCallback(register_CCBuilderReader);
    
    // ui can be commented out to reduce the package, attension studio need ui module
    sc->addRegisterCallback(register_all_cocos2dx_ui);
    sc->addRegisterCallback(register_all_cocos2dx_ui_manual);
    
    // studio can be commented out to reduce the package,
    sc->addRegisterCallback(register_all_cocos2dx_studio);
    sc->addRegisterCallback(register_all_cocos2dx_studio_manual);
    
    // spine can be commented out to reduce the package
//    sc->addRegisterCallback(register_all_cocos2dx_spine);
//    sc->addRegisterCallback(register_all_cocos2dx_spine_manual);
    
    // XmlHttpRequest can be commented out to reduce the package
    sc->addRegisterCallback(MinXmlHttpRequest::_js_register);
    // websocket can be commented out to reduce the package
//    sc->addRegisterCallback(register_jsb_websocket);
    // sokcet io can be commented out to reduce the package
//    sc->addRegisterCallback(register_jsb_socketio);
    
    // 3d can be commented out to reduce the package
//    sc->addRegisterCallback(register_all_cocos2dx_3d);
//    sc->addRegisterCallback(register_all_cocos2dx_3d_manual);
    
    // 3d extension can be commented out to reduce the package
//    sc->addRegisterCallback(register_all_cocos2dx_3d_extension);
    
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
    // Physics 3d can be commented out to reduce the package
//    sc->addRegisterCallback(register_all_cocos2dx_physics3d);
//    sc->addRegisterCallback(register_all_cocos2dx_physics3d_manual);
#endif
    
#if CC_USE_NAVMESH
    sc->addRegisterCallback(register_all_cocos2dx_navmesh);
    sc->addRegisterCallback(register_all_cocos2dx_navmesh_manual);
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    sc->addRegisterCallback(register_all_cocos2dx_experimental_video);
    sc->addRegisterCallback(register_all_cocos2dx_experimental_video_manual);
    sc->addRegisterCallback(register_all_cocos2dx_experimental_webView);
    sc->addRegisterCallback(register_all_cocos2dx_experimental_webView_manual);
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sc->addRegisterCallback(JavascriptJavaBridge::_js_register);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    sc->addRegisterCallback(JavaScriptObjCBridge::_js_register);
#endif

    // init custom jsb code ********** add by howe
    init_custom_jsb();
    
    PlatformManager::deleteAllNotification();
    
    sc->start();    
    sc->runScript("script/jsb_boot.js");
    
    ScriptEngineProtocol *engine = ScriptingCore::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    ScriptingCore::getInstance()->runScript("main.js");

#ifdef ANDROID_COMM_VERSION    
    cocos2d::log("AppDelegate::doGameInit addModule");
    static NativeModule nativeModule;
    nativeModule.initSchedule();
    static int cnt = 0;
    if(cnt++ == 0)
    {
        platform::PlatformMgr::getInstance()->addModule(&nativeModule);
    }
    // test
    PlatformManager::getInstance()->reportEvent("{\"Event\":\"android_in\",\"Amount\":0.00,\"Currency\":\"NON\"}");
#endif
    
    Director::getInstance()->registerPlayEffectFunc(AudioEngineHelper::PlayEffectT);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    cocos2d::log("AppDelegate::applicationDidEnterBackground");    
    auto director = Director::getInstance();
    director->stopAnimation();
    director->getEventDispatcher()->dispatchCustomEvent("game_on_hide");
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();    
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    auto director = Director::getInstance();
    director->startAnimation();
    director->getEventDispatcher()->dispatchCustomEvent("game_on_show");
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
    PlatformManager::deleteAllNotification();
}
