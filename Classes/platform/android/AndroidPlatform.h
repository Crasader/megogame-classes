//
//  AndroidPlatform.h
//  MegoGame
//
//  Created by howe on 15/4/14.
//
//

#ifndef __MegoGame__AndroidPlatform__
#define __MegoGame__AndroidPlatform__

#include <stdio.h>
#include "../IPlatform.h"

class AndroidPlatform : public IPlatform
{
    
    virtual ~AndroidPlatform();
    
    virtual std::string getAppVersion() const;

    //get the mac address of device
    virtual std::string getMacAddress() const;
    
    //wiki http://zh.wikipedia.org/wiki/IOS%E8%AE%BE%E5%A4%87%E5%88%97%E8%A1%A8
    virtual std::string getDeviceType() const;
    //系统
    virtual std::string getDeviceSystem() const;
    //内存
    virtual std::string  getDeviceMemory() const;
    //网络
    virtual NetworkType getNetworkType() const;
    //UID
    virtual std::string getDeviceUid() const;
    //UID类型
    virtual std::string getDeviceUidType() const;
    //设备名字
    virtual std::string getDeviceName() const;
    
    virtual std::string getPlatformId() const;
    
    virtual std::string getDeviceToken() override;

    virtual void setTextInPasteboard(std::string) const;

	void reportEvent(std::string event,float amount = 0.0,std::string currency = "");
    virtual void addNotification(std::string id, int seconds, std::string info) ;
    virtual void addNotificationInWeek(std::string id, int atDay, int atHour, int atMin, std::string  info) ;
	virtual void deleteAllNotification() ;

    virtual void sharedFaceBook(const std::string &url,const std::string &des,const std::string &title);
    virtual void sharedFaceBook(const std::string &url,const std::string &des,const std::string &title, const std::string &imgUrl);
};
#endif /* defined(__MegoGame__AndroidPlatform__) */
