//
//  IOSPlatform.h
//  MegoGame
//
//  Created by SWT on 15/4/1.
//
//

#ifndef __MegoGame__IOSPlatform__
#define __MegoGame__IOSPlatform__

#include "IPlatform.h"

std::string getIPAddress();
class IOSPlatform : public IPlatform
{
public:
    IOSPlatform();
    
    virtual ~IOSPlatform();
    
    void init();
    
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
    

    virtual void setTextInPasteboard(std::string) const;
    
    virtual std::string getDeviceToken() override;
    
    virtual void reportEvent(std::string event,float amount = 0.0,std::string currency = "");
    
    virtual void addNotification(std::string id, int seconds, std::string info) ;
    virtual void addNotificationInWeek(std::string id, int atDay, int atHour, int atMin, std::string  info);
    virtual void deleteAllNotification();
    void sharedFaceBook(const std::string &url,const std::string &des,const std::string &title);
};


#endif /* defined(__MegoGame__IOSPlatform__) */
