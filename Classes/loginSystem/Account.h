//
//  Account.h
//  client
//
//  Created by yuxiao on 13-12-24.
//
//

#ifndef __client__Account__
#define __client__Account__

#include <iostream>
#include "cocos2d.h"
#include <map>
//#include "Defines.h"

const std::string shopKeyValue[] =
{
    "SDK_TOKEN",
    "G_ROLE_ID",
    "G_ROLE_LEVEL",
    "G_ROLE_NAME",
    "G_SERVER_ID",
    "G_SERVER_NAME",
    "G_ROLE_VIP_LV",
    "G_ROLE_DIAMOND",
    "B_CURRENCY_TYPE",
    "B_PRODUCT_ID",
    "B_GOODS_ID",
    "B_GOODS_NAME",
    "B_BUY_ITEM_PRICE",
    "B_BUY_ITEM_CNT",
    "B_BUY_ITEM_DES",
    "B_BUY_ITEM_ID",
    "G_PLATFORM_ID",
    "G_ROLE_GUILD_NAME",
    "G_ROLE_GUILD_ID",
    "B_PAY_DESCRIPTION"
};


class Account
{

public:
    static Account *shareInstance();
    Account();

    virtual void init() {};

    virtual void login();
    virtual void logout() { this->doLogoutGame();};
    virtual void center() {};
    virtual void switchAccount() {this->doLogoutGame();};
	/*
		false: platform don't need this event. native can exit app now
		true: platform will handle exit. do not exit app now.
	*/
	virtual bool exit(){return false;}
    
    void buy(const std::string& jsString);
    
    
    
    bool isLogin();
    void doLoginGame(const std::string& accountId);
    void doLogoutGame();
    void clearLoginUid();
    const std::string& getLoginUid() const;
    
    

	std::string platformCall(const std::string action, const std::string params);
	std::string gameCall(const std::string action, const std::string params);
    
private:
    virtual void buy(std::map<std::string,std::string> & mapValues);
    
protected:
    
private:
    std::string m_sAccountId;
    
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
protected:
    virtual void applicationWillResignActive(void *iosUIApplication);
    virtual void applicationDidBecomeActive(void *iosUIApplication);
    virtual void applicationDidEnterBackground(void *iosUIApplication);
    virtual void applicationWillEnterForeground(void *iosUIApplication);
    virtual void applicationWillTerminate(void *iosUIApplication);
    virtual void applicationDidRegisterForRemoteNotificationsWithDeviceToken(void *iosNSData);
    virtual void applicationDidReceiveRemoteNotification(void *iosNSDictionary);
    virtual bool applicationOpenURL(void *iosUIApplication, void *iosNSURL, void *iosNSString);
#endif
    
};

#endif /* defined(__client__AccountBase__) */
