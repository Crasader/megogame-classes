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

class MacPlatform : public IPlatform
{
    
    virtual ~MacPlatform();
    
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
    
};
#endif /* defined(__MegoGame__AndroidPlatform__) */
