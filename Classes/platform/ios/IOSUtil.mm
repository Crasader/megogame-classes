//
//  IOSUtil.m
//
//  Created by ziRoy on 12-7-9.
//

#import "IOSUtil.h"
#import <UIKit/UIKit.h>
#import<SystemConfiguration/SystemConfiguration.h>
#import<netdb.h>
#import <Foundation/NSBundle.h>
#import "OpenUDID.h"
#include <sys/socket.h> // Per msqr
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#include "md5.h"
#include "RootViewController.h"
#import <AdSupport/AdSupport.h>

#include "Support.h"

//@implementation IOSUtil

//@end
std::string IOSUtil::udidType("-1");
std::string IOSUtil::getLibraryCacheDirectory()
{
    std::string ss([[Support getLibraryCacheDirectory] UTF8String] );
    return ss;
}
bool IOSUtil::should2X()
{
    return [[UIScreen mainScreen] scale] == 2 || (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad);
}


void IOSUtil::SinaLayer_onCancel()
{
    //    [RootViewController sharedInstance].postImage = nil;
}

void IOSUtil::SinaLayer_onSignOut()
{
    //    [[RootViewController sharedInstance] onSignOut];
}

void IOSUtil::SinaLayer_onSend(const char *_str)
{
    //    [[RootViewController sharedInstance] onSend:_str];
}

void IOSUtil::OpenUrl(const char *_url)
{
    NSString *URL = [NSString stringWithCString:_url encoding:NSUTF8StringEncoding];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:URL]];
}

void IOSUtil::OpenUrlInner(const char* _url)
{
    //    UIViewController *rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
    //    IOSWebViewController *webViewController = [[IOSWebViewController alloc] init];
    //
    //    webViewController.requestURLString = [NSString stringWithUTF8String:_url];
    //
    //    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:webViewController];
    //    [rootViewController presentModalViewController:nav animated:YES];
    //
    //    [webViewController release];
    //    [nav release];
}

bool IOSUtil::isConnectedToNet()
{
    struct sockaddr_in zeroAddress;
    bzero(&zeroAddress, sizeof(zeroAddress));
    zeroAddress.sin_len = sizeof(zeroAddress);
    zeroAddress.sin_family = AF_INET;
    
    SCNetworkReachabilityRef defaultRouteReachability = SCNetworkReachabilityCreateWithAddress(NULL, (struct sockaddr *)&zeroAddress);
    SCNetworkReachabilityFlags flags;
    
    BOOL didRetrieveFlags = SCNetworkReachabilityGetFlags(defaultRouteReachability, &flags);
    CFRelease(defaultRouteReachability);
    
    if (!didRetrieveFlags) {
        printf("Error. Count not recover network reachability flags\n");
        return NO;
    }
    
    BOOL isReachable = flags & kSCNetworkFlagsReachable;
    BOOL needsConnection = flags & kSCNetworkFlagsConnectionRequired;
    return (isReachable && !needsConnection) ? true : false;
}

const char* IOSUtil::GetIconPath()
{
    static char buf[256] = {0};
    
    NSDictionary* info = [[NSBundle mainBundle] infoDictionary];
    if (info) {
        NSArray* icon_array = [info objectForKey:@"CFBundleIconFiles"];
        if (icon_array) {
            NSString* path = icon_array[0];
            if (path) {
                strcpy(buf, [path cStringUsingEncoding:NSUTF8StringEncoding]);
            }
        }
    }
    
    return buf;
    
}

std::string IOSUtil::udid()
{
    std::string ret;
    do {
        ret = MD5(macString()).toString();
        if(ret != "0f607264fc6318a92b9e13c65db7cd3c") {
            IOSUtil::udidType = "100";
            break;
        }
        ret = openUDID();
        if(ret != "0f607264fc6318a92b9e13c65db7cd3c") {
            IOSUtil::udidType = "101";
            break;
        }
        ret = idfaString();
        if(!ret.empty()) {
            IOSUtil::udidType = "102";
            break;
        }
        ret = idfvString();
        if(!ret.empty()) {
            IOSUtil::udidType = "103";
            break;
        }
    }while(0);
    
    return ret;
}

std::string IOSUtil::macString()
{
    int                 mib[6];
    size_t              len;
    char                *buf;
    unsigned char       *ptr;
    struct if_msghdr    *ifm;
    struct sockaddr_dl  *sdl;
    char outstring[50];
    
    mib[0] = CTL_NET;
    mib[1] = AF_ROUTE;
    mib[2] = 0;
    mib[3] = AF_LINK;
    mib[4] = NET_RT_IFLIST;
    
    if ((mib[5] = if_nametoindex("en0")) == 0) {
        printf("Error: if_nametoindex error\n");
        return NULL;
    }
    
    if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
        printf("Error: sysctl, take 1\n");
        return NULL;
    }
    
    if ((buf = (char*)malloc(len)) == NULL) {
        printf("Could not allocate memory. error!\n");
        return NULL;
    }
    
    if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
        printf("Error: sysctl, take 2");
        free(buf);
        return NULL;
    }
    
    ifm = (struct if_msghdr *)buf;
    sdl = (struct sockaddr_dl *)(ifm + 1);
    ptr = (unsigned char *)LLADDR(sdl);
    snprintf(outstring, sizeof(outstring), "%02X:%02X:%02X:%02X:%02X:%02X", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5));
    free(buf);
    
    return std::string(outstring);
}

std::string IOSUtil::idfaString()
{
    if([[ASIdentifierManager sharedManager] isAdvertisingTrackingEnabled]) {
        NSString *idfa = [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
        if(idfa) {
            return std::string([idfa UTF8String]);
        }
    }
    return std::string();
}

std::string IOSUtil::idfvString()
{
    if([[UIDevice currentDevice] respondsToSelector:@selector(identifierForVendor)]) {
        NSString *idfv = [[UIDevice currentDevice].identifierForVendor UUIDString];
        if(idfv) {
            return std::string([idfv UTF8String]);
        }
    }
    return std::string();
}

std::string IOSUtil::openUDID()
{
    NSString *openUDID = [OpenUDID value];
    if(openUDID) {
        return std::string([openUDID UTF8String]);
    }
    return std::string();
}


float IOSUtil::systemVersion()
{
    return [[UIDevice currentDevice].systemVersion floatValue];
}



