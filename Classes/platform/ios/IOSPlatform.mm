//
//  IOSPlatform.cpp
//  MegoGame
//
//  Created by SWT on 15/4/1.
//
//

#include "IOSPlatform.h"

//#import <SystemConfiguration/SCNetworkReachability.h>
//#import <CommonCrypto/CommonDigest.h>
//#import <Foundation/Foundation.h>
//#import <QuartzCore/QuartzCore.h>
//#import <AudioToolbox/AudioToolbox.h>
//
//#include <sys/socket.h>
//#include <sys/sysctl.h>
//#include <net/if.h>
//#include <net/if_dl.h>
//#include <netinet/in.h>
//
//#import "UIDevice-Hardware.h"
//#import "SFHFKeychainUtils.h"
//#import "AppController.h"

#import <SystemConfiguration/SCNetworkReachability.h>
#import <CommonCrypto/CommonDigest.h>
#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <AudioToolbox/AudioToolbox.h>
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <netinet/in.h>
#import "UIDevice-Hardware.h"
#import "SFHFKeychainUtils.h"
#import "AppController.h"
#ifdef VERSION_D9
//#import "D9FaceBook.h"
#import "FaceBookShare.h"
#endif

#import "ReachabilityHelper.h"

#include <iostream>
#include "IOSPlatform.h"
#include "ScriptingCore.h"
#include "cocos2d.h"
#include "IOSUtil.h"
#include <mach/task_info.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

#import "AdSupport/ASIdentifierManager.h"
#import "Support.h"

std::string getIPAddress()
{
    return "";
}


IOSPlatform::IOSPlatform()
{
    init();

}
IOSPlatform::~IOSPlatform() {

};

void IOSPlatform::init()
{
    // 禁止ios 锁屏
    
    ReachabilityHelper * reachabilityHelper = [[ReachabilityHelper alloc] initHelper];
}
//virtual std::string getAppVersion();
std::string IOSPlatform::getAppVersion() const
{
    NSDictionary *appInfo = [[NSBundle mainBundle] infoDictionary];
    return [[appInfo objectForKey:@"CFBundleShortVersionString"] UTF8String];
}
//get the mac address of device
std::string IOSPlatform::getMacAddress() const{
    return [[[UIDevice currentDevice] macaddress] UTF8String];
}

//wiki http://zh.wikipedia.org/wiki/IOS%E8%AE%BE%E5%A4%87%E5%88%97%E8%A1%A8
std::string IOSPlatform::getDeviceType() const{
    size_t size;
    
    sysctlbyname("hw.machine", NULL, &size, NULL, 0);
    
    char *machine = (char*)malloc(size);
    
    sysctlbyname("hw.machine", machine, &size, NULL, 0);
    
    NSString *platform = [NSString stringWithCString:machine encoding:NSUTF8StringEncoding];
    
    free(machine);
    return std::string([platform UTF8String]);
}
//系统
std::string IOSPlatform::getDeviceSystem() const{
    UIDevice *dev = [UIDevice currentDevice];
    NSString *deviceSystemVersion = dev.systemVersion;
    NSString *systemName =dev.systemName;
    NSString *system =[systemName stringByAppendingFormat:@" %@",deviceSystemVersion];
    return std::string([system UTF8String]);
}
//内存
std::string  IOSPlatform::getDeviceMemory() const{
//    //get all memory
    long mem = NSRealMemoryAvailable()/1024/1024; // MB
    char str[32] = {0};
    sprintf(str, "%lu",mem);
    return str;
//    std::string totalMemory=([[NSString stringWithFormat:@"%luMB",(NSRealMemoryAvailable()/1024/1024)] UTF8String]);
//    
//    //get current memory
//    vm_statistics_data_t vmStats;
//    mach_msg_type_number_t infoCount = HOST_VM_INFO_COUNT;
//    kern_return_t kernReturn = host_statistics(mach_host_self(),
//                                               HOST_VM_INFO,
//                                               (host_info_t)&vmStats,
//                                               &infoCount);
//    
//    if (kernReturn != KERN_SUCCESS) {
//        return 0;
//    }
//    
//    int currentAvaliable = (int) ((vm_page_size *vmStats.free_count) / 1024.0) / 1024.0;
//    std::string memoryString([[NSString stringWithFormat:@"%dMB",currentAvaliable] UTF8String]);
//    std::string info = memoryString +"/"+totalMemory;
//    return info;
}
//网络
NetworkType IOSPlatform::getNetworkType() const{
    struct sockaddr_in zeroAddress;
    bzero(&zeroAddress, sizeof(zeroAddress));
    zeroAddress.sin_len = sizeof(zeroAddress);
    zeroAddress.sin_family = AF_INET;
    
    // Recover reachability flags
    SCNetworkReachabilityRef defaultRouteReachability = SCNetworkReachabilityCreateWithAddress(NULL, (struct sockaddr *)&zeroAddress);
    SCNetworkReachabilityFlags flags;
    
    BOOL didRetrieveFlags = SCNetworkReachabilityGetFlags(defaultRouteReachability, &flags);
    CFRelease(defaultRouteReachability);
    
    if (!didRetrieveFlags)
    {
        NSLog(@"Error. Could not recover network reachability flags");
        return NET_NULL;
    }
    
    BOOL isReachable = flags & kSCNetworkFlagsReachable;
    BOOL needsConnection = flags & kSCNetworkFlagsConnectionRequired;
    
    if ((isReachable && !needsConnection) == NO)
    {
        return NET_NULL;
    }
    NetworkType retVal = NET_NULL;
    if ((flags & kSCNetworkReachabilityFlagsConnectionRequired) == 0)
    {
        // if target host is reachable and no connection is required
        // then we'll assume (for now) that your on Wi-Fi
        retVal = NET_WIFI;
    }
    if (
        ((flags & kSCNetworkReachabilityFlagsConnectionOnDemand ) != 0) ||
        (flags & kSCNetworkReachabilityFlagsConnectionOnTraffic) != 0
        )
    {
        // ... and the connection is on-demand (or on-traffic) if the
        // calling application is using the CFSocketStream or higher APIs
        if ((flags & kSCNetworkReachabilityFlagsInterventionRequired) == 0)
        {
            // ... and no [user] intervention is needed
            retVal = NET_WIFI;
        }
    }
    if ((flags & kSCNetworkReachabilityFlagsIsWWAN) == kSCNetworkReachabilityFlagsIsWWAN)
    {
        if((flags & kSCNetworkReachabilityFlagsReachable) == kSCNetworkReachabilityFlagsReachable) {
            if ((flags & kSCNetworkReachabilityFlagsTransientConnection) == kSCNetworkReachabilityFlagsTransientConnection) {
                retVal = NET_3G;
                if((flags & kSCNetworkReachabilityFlagsConnectionRequired) == kSCNetworkReachabilityFlagsConnectionRequired) {
                    retVal = NET_2G;
                }
            }
        }
    }
    return retVal;
}
//UID
std::string IOSPlatform::getDeviceUid() const{
    return IOSUtil::udid();
}
//UID类型
std::string IOSPlatform::getDeviceUidType() const{
    return IOSUtil::udidType;
}
//设备名字
std::string IOSPlatform::getDeviceName() const{
    return [[UIDevice currentDevice].model UTF8String];
}

std::string IOSPlatform::getPlatformId() const{
    
//    int platformId = 0;
    std::string abalyid = "1";
#ifdef VERSION_D9
    abalyid = "994";
#else
    
#endif
    
    
    
    return abalyid;
}



void IOSPlatform::setTextInPasteboard(std::string text) const
{
    UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];
    [pasteboard setString:[NSString stringWithCString:text.c_str() encoding:[NSString defaultCStringEncoding]]];
}

std::string IOSPlatform::getDeviceToken()
{
    NSString *adId = [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
    return std::string( [adId UTF8String] );
}

void IOSPlatform::reportEvent(std::string event,float amount ,std::string currency )
{
    [Support ReportEvent:[NSString stringWithUTF8String:event.c_str()] amount:amount currency:[NSString stringWithUTF8String:currency.c_str()]];
}

void IOSPlatform::addNotification(std::string key, int seconds, std::string info)
{
    [Support addLocalNotification:[NSString stringWithUTF8String:key.c_str()] forText:[NSString stringWithUTF8String:info.c_str()] withTime: [NSNumber numberWithInt:seconds]];
};
void IOSPlatform::addNotificationInWeek(std::string id, int atDay, int atHour, int atMin, std::string  info)
{
    
};

void IOSPlatform::deleteAllNotification()
{
    [Support removeAllNoticefication];
}

void IOSPlatform::sharedFaceBook(const std::string &url,const std::string &des,const std::string &title)
{
#ifdef VERSION_D9
    [[FaceBookShare sharedFaceBook]ShareToFacebookDesc:[NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]] ShareDesc:[NSString stringWithUTF8String:des.c_str()] ShareTitle:[NSString stringWithUTF8String:title.c_str()]];
#endif
}

