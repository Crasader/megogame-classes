//
//  AndroidPlatform.cpp
//  MegoGame
//
//  Created by howe on 15/4/14.
//
//

#include "MacPlatform.h"
#include <objc/runtime.h>
//#import <AppKit/AppKit.h>
#import <AppKit/AppKit.h>
//
//  Win32Platform.cpp
//  MegoGame
//
//  Created by howe on 15/4/14.
//
//

std::string GetHardwareUUID()
{
    NSString *ret = nil;
    io_service_t platformExpert ;
    platformExpert = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching("IOPlatformExpertDevice")) ;
    
    if (platformExpert) {
        CFTypeRef serialNumberAsCFString ;
        serialNumberAsCFString = IORegistryEntryCreateCFProperty(platformExpert, CFSTR("IOPlatformUUID"), kCFAllocatorDefault, 0) ;
        if (serialNumberAsCFString) {
            ret = [(NSString *)(CFStringRef)serialNumberAsCFString copy];
            CFRelease(serialNumberAsCFString); serialNumberAsCFString = NULL;
        }
        IOObjectRelease(platformExpert); platformExpert = 0;
    }
    if (!ret)
    {
        return "";
    }
    return [ret UTF8String];
}

MacPlatform::~MacPlatform() {
    
};
std::string MacPlatform::getAppVersion() const
{
    NSDictionary *appInfo = [[NSBundle mainBundle] infoDictionary];
    return [[appInfo objectForKey:@"CFBundleShortVersionString"] UTF8String];
}
//get the mac address of device
std::string MacPlatform::getMacAddress() const{
    return "";
}

//wiki http://zh.wikipedia.org/wiki/IOS%E8%AE%BE%E5%A4%87%E5%88%97%E8%A1%A8
std::string MacPlatform::getDeviceType() const{
    
    return "";
}
//系统
std::string MacPlatform::getDeviceSystem() const{
    
    return "mac osx";
}
//内存
std::string  MacPlatform::getDeviceMemory() const{
    //    //get all memory
    
    return "";
}
//网络
NetworkType MacPlatform::getNetworkType() const{
    
    return NET_WIFI;
}
//UID
std::string MacPlatform::getDeviceUid() const{
    
    return GetHardwareUUID();
}
//UID类型
std::string MacPlatform::getDeviceUidType() const{
    return "";
}
//设备名字
std::string MacPlatform::getDeviceName() const{
    return "MAC";
}

std::string MacPlatform::getPlatformId() const
{
    return "1";
}

void MacPlatform::setTextInPasteboard(std::string text) const
{
    
    UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];
    [pasteboard setString:[NSString stringWithCString:text.c_str() encoding:[NSString defaultCStringEncoding]]];
}
