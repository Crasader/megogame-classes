//
//  IPlatform.h
//  MegoGame
//
//  Created by SWT on 15/4/1.
//
//

#ifndef MegoGame_IPlatform_h
#define MegoGame_IPlatform_h

#include <iostream>

typedef enum
{
    NET_NULL = 0,
    NET_WIFI =1,
    NET_3G=2,
    NET_2G=3,
} NetworkType;

class IPlatform {
    
public:
    virtual ~IPlatform() {};
    
    virtual std::string getAppVersion() const = 0;

    //get the mac address of device
    virtual std::string getMacAddress() const = 0;
    
    //wiki http://zh.wikipedia.org/wiki/IOS%E8%AE%BE%E5%A4%87%E5%88%97%E8%A1%A8
    virtual std::string getDeviceType() const = 0;
    //system
    virtual std::string getDeviceSystem() const = 0;
    //memory
    virtual std::string  getDeviceMemory() const = 0;
    //net
    virtual NetworkType getNetworkType() const = 0;
    //UID
    virtual std::string getDeviceUid() const = 0;
    //UID
    virtual std::string getDeviceUidType() const= 0;
    // device name
    virtual std::string getDeviceName() const= 0;
    // channel
    virtual std::string getPlatformId() const= 0;

    virtual void reportEvent(std::string event,float amount = 0.0,std::string currency = ""){}
    
    virtual void addNotification(std::string id, int seconds, std::string info) {};
    virtual void addNotificationInWeek(std::string id, int atDay, int atHour, int atMin, std::string  info) {};
    virtual void deleteAllNotification() {};
    virtual std::string getDeviceToken()
    {
        return "device_token";
    }
    //set text in pasteboard
    virtual void setTextInPasteboard(std::string) const = 0;
    virtual void sharedFaceBook(const std::string &url,const std::string &des,const std::string &title) = 0;
};


#endif
