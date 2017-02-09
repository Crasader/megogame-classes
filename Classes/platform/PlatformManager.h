//
//  PlatformManager.h
//  MegoGame
//
//  Created by SWT on 15/4/1.
//
//

#ifndef __MegoGame__PlatformManager__
#define __MegoGame__PlatformManager__

#include <stdio.h>

#include "IPlatform.h"
#include "cocos2d.h"

USING_NS_CC;

class PlatformManager : public cocos2d::Ref{
    
public:
    PlatformManager();
    ~PlatformManager();
    
    static void InitPlatform();
    static void DestoryPlatform();
    
    static PlatformManager* getInstance();
    
    
    static void setValueForKey(std::string, std::string);
    
    static std::string getValueForKey(std::string);
    
    static std::string getAppVersion();
    //get the mac address of device
    static std::string getMacAddress();
    
    //wiki http://zh.wikipedia.org/wiki/IOS%E8%AE%BE%E5%A4%87%E5%88%97%E8%A1%A8
    static std::string getDeviceType();
    static std::string getDeviceSystem();
    static std::string  getDeviceMemory();
    static NetworkType getNetworkType();
    static std::string getDeviceUid();
    static std::string getDeviceUidType();
    static std::string getDeviceName();
    static int getPlatformId();

	static void reportEvent(std::string event);
    static void reportNotification(std::string event);
    static void deleteAllNotification();
   
    static std::string getDeviceToken()
    {
        if (m_sharePlatform->m_plat)
        {
            return m_sharePlatform->m_plat->getDeviceToken();
        }
        return "";
    }
    
    //csb
//    static Node* createNode(std::string);
    static Node* createNode(const std::string& filename);


    //csb action
//    static cocostudio::timeline::ActionTimeline* createAction(std::string);
    
    
    //set text in pasteboard
    static void setTextInPasteboard(std::string);
    
    static void loginSuccessAndCallJS(std::vector<std::string> &arr);
    
    static void logOutAndCallJS();
    static void gameCall(const std::string action, const std::string params);
    
    static std::string getLangueIdentify();
    
    static void setLangueIdentify(std::string);
    static void sharedFaceBook(std::string shareInfo);

protected:
    static PlatformManager *m_sharePlatform;
    IPlatform* m_plat;

    std::string _langueIdentify;
    
};

#endif /* defined(__MegoGame__PlatformManager__) */
