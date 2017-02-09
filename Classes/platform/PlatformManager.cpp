//
//  PlatformManager.cpp
//  MegoGame
//
//  Created by SWT on 15/4/1.
//
//

#include "PlatformManager.h"
#include "cocostudio/DictionaryHelper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ios/IOSPlatform.h"
#endif 

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/AndroidPlatform.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "win32/Win32Platform.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "mac/MacPlatform.h"
#endif

#include "cocostudio/CocoStudio.h"

#include "cocos2d_specifics.hpp"
#include "jsapi.h"


PlatformManager* PlatformManager::m_sharePlatform = NULL;

PlatformManager::PlatformManager(){
    
}
PlatformManager::~PlatformManager(){
    
}

void PlatformManager::InitPlatform(){
    
    if(m_sharePlatform == NULL){
        m_sharePlatform = new PlatformManager();
        
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        // create IOS Platform device
        m_sharePlatform->m_plat = new IOSPlatform();
#endif  // CC_PLATFORM_IOS
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        m_sharePlatform->m_plat = new AndroidPlatform();
#endif
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        m_sharePlatform->m_plat = new Win32Platform();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        m_sharePlatform->m_plat = new MacPlatform();
#endif
    }
    
}

PlatformManager* PlatformManager::getInstance()
{
    if(m_sharePlatform == NULL){
        PlatformManager::InitPlatform();
    }
    return m_sharePlatform;
}


void PlatformManager::DestoryPlatform(){
    delete m_sharePlatform->m_plat;
    m_sharePlatform->m_plat = NULL;
    
    delete m_sharePlatform;
    m_sharePlatform = NULL;
}

void PlatformManager::setValueForKey(std::string arg0, std::string arg1){
    cocos2d::UserDefault::getInstance()->setStringForKey(arg0.c_str(), arg1);
    cocos2d::UserDefault::getInstance()->flush();
}

std::string PlatformManager::getValueForKey(std::string arg0){
    return cocos2d::UserDefault::getInstance()->getStringForKey(arg0.c_str());

}

std::string PlatformManager::getAppVersion()
{
    return m_sharePlatform->m_plat->getAppVersion();
}
//get the mac address of device
std::string PlatformManager::getMacAddress(){
    return m_sharePlatform->m_plat->getMacAddress();
}

//wiki http://zh.wikipedia.org/wiki/IOS%E8%AE%BE%E5%A4%87%E5%88%97%E8%A1%A8
std::string PlatformManager::getDeviceType(){
    return m_sharePlatform->m_plat->getMacAddress();
}
//
std::string PlatformManager::getDeviceSystem(){
    return m_sharePlatform->m_plat->getMacAddress();
}
//
std::string  PlatformManager::getDeviceMemory(){
    return m_sharePlatform->m_plat->getDeviceMemory();
}
//
NetworkType PlatformManager::getNetworkType(){
    NetworkType type = m_sharePlatform->m_plat->getNetworkType();
    if (type == NET_NULL)
    {
        cocos2d::MessageBox("No network connecting", "Error");
    }
    return type;
}
//UID
std::string PlatformManager::getDeviceUid(){
    return m_sharePlatform->m_plat->getDeviceUid();
}
//UID
std::string PlatformManager::getDeviceUidType(){
    return m_sharePlatform->m_plat->getDeviceUidType();
}
//
std::string PlatformManager::getDeviceName(){
    return m_sharePlatform->m_plat->getDeviceName();
}
//
int PlatformManager::getPlatformId(){
    int id = std::atoi(m_sharePlatform->m_plat->getPlatformId().c_str());
    return id;
}

void PlatformManager::reportEvent(std::string jsEvent)
{
    rapidjson::Document doc;
    doc.Parse(jsEvent.c_str());

    std::string event = cocostudio::DictionaryHelper::getInstance()->getStringValue_json(doc,"Event");
    float amount = cocostudio::DictionaryHelper::getInstance()->getFloatValue_json(doc,"Amount");
    std::string currency = cocostudio::DictionaryHelper::getInstance()->getStringValue_json(doc,"Currency");
    
    m_sharePlatform->m_plat->reportEvent(event,amount,currency);
}

void PlatformManager::reportNotification(std::string jsObj)
{
    rapidjson::Document doc;
    doc.Parse(jsObj.c_str());
    int type = cocostudio::DictionaryHelper::getInstance()->getIntValue_json(doc,"Type");
    std::string key = cocostudio::DictionaryHelper::getInstance()->getStringValue_json(doc,"KeyValue");
    float second = cocostudio::DictionaryHelper::getInstance()->getFloatValue_json(doc,"Second");
    std::string notifyText = cocostudio::DictionaryHelper::getInstance()->getStringValue_json(doc,"NotifyText");
    
    if (type == 0)
    {
        m_sharePlatform->m_plat->addNotification(key, second, notifyText);
    }
    else
    {
        m_sharePlatform->m_plat->addNotificationInWeek(key, 0, 0,0,notifyText);
    }
}

void PlatformManager::deleteAllNotification()
{
    m_sharePlatform->m_plat->deleteAllNotification();
}

//csb
//Node* PlatformManager::createNode(std::string filename){
//    Node* _node = CSLoader::createNode(filename);
//    if(!_node){
//        CCLOG("CSLoader::createNode is error!!! filename :%s",filename.c_str());
//    }
//    return _node;
//}

Node* PlatformManager::createNode(const std::string &filename){
    
    Node* _node = CSLoader::createNode(filename,nullptr);
    
    if(!_node){
        CCLOG("CSLoader::createNode is error!!! filename :%s",filename.c_str());
    }
    
    return _node;
}

//Node* PlatformManager::createNode(std::string filename){
//    Node* _node = CSLoader::createNode(filename);
//    if(!_node){
//        CCLOG("CSLoader::createNode is error!!! filename :%s",filename.c_str());
//    }
//    return _node;
//}

//cocostudio::timeline::ActionTimeline* PlatformManager::createAction(std::string filename){
//    return CSLoader::createTimeline(filename);
//}



void PlatformManager::setTextInPasteboard(std::string text){
    m_sharePlatform->m_plat->setTextInPasteboard(text);
}


void PlatformManager::loginSuccessAndCallJS(std::vector<std::string> &arr)
{
    static const char LOGIN_EVENT_CALL[] = "OnLoginCall";
    
    ScriptingCore* sc = ScriptingCore::getInstance();
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    
    JS::RootedObject gl(cx, ScriptingCore::getInstance()->getGlobalObject());
    
    JS::RootedValue temp_retval(cx);
    JS_GetProperty(sc->getGlobalContext(), gl, "syst", &temp_retval);
    if (temp_retval != JSVAL_VOID)
    {
        std::string param;
        for (auto ii : arr)
        {
            param+= ("*" + ii);
        }
        jsval dataVal = std_string_to_jsval(cx, param);
        sc->executeFunctionWithOwner(temp_retval, LOGIN_EVENT_CALL, 1,&dataVal);
    }
}


void PlatformManager::logOutAndCallJS()
{
    static const char LOGIN_EVENT_CALL[] = "OnLogoutCall";
    
    ScriptingCore* sc = ScriptingCore::getInstance();
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    
    JS::RootedObject gl(cx, ScriptingCore::getInstance()->getGlobalObject());
    
    JS::RootedValue temp_retval(cx);
    JS_GetProperty(sc->getGlobalContext(), gl, "syst", &temp_retval);
    if (temp_retval != JSVAL_VOID)
    {
        jsval dataVal = INT_TO_JSVAL(1);
        sc->executeFunctionWithOwner(temp_retval, LOGIN_EVENT_CALL, 1,&dataVal);
    }
}

void PlatformManager::gameCall(const std::string action, const std::string params)
{
    
    ScriptingCore* sc = ScriptingCore::getInstance();
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    
    JS::RootedObject gl(cx, ScriptingCore::getInstance()->getGlobalObject());
    
    JS::RootedValue temp_retval(cx);
    JS_GetProperty(sc->getGlobalContext(), gl, "syst", &temp_retval);
    if (temp_retval != JSVAL_VOID)
    {
        int iPara = atoi(params.c_str());
        jsval dataVal = INT_TO_JSVAL(iPara);
        sc->executeFunctionWithOwner(temp_retval, action.c_str(), 1,&dataVal);
    }
}

std::string PlatformManager::getLangueIdentify(){
    return m_sharePlatform->_langueIdentify;
}

void PlatformManager::setLangueIdentify(std::string str){
    m_sharePlatform->_langueIdentify = str;
}

void PlatformManager::sharedFaceBook(std::string shareInfo)
{
    rapidjson::Document doc;
    doc.Parse(shareInfo.c_str());
    std::string shareUrl = cocostudio::DictionaryHelper::getInstance()->getStringValue_json(doc,"URL");
    std::string shareDescription = cocostudio::DictionaryHelper::getInstance()->getStringValue_json(doc,"DESCRIPTION");
    std::string shareTitle = cocostudio::DictionaryHelper::getInstance()->getStringValue_json(doc,"TITLE");
    
    m_sharePlatform->m_plat->sharedFaceBook(shareUrl, shareDescription, shareTitle);

}





