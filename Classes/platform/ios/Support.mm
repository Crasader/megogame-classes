//
//  Support.m
//  MegoGame
//
//  Created by Relvin on 15/6/23.
//
//
/**
 * defined CHARTBOOST for chartboostSDK
 * defined VERSION_D9 for D9SDK
 * defined GOCPATRACKER for GocpaTrackerSDK
 * defined APPSFLYER for AppsFlyerTrackerSDK
 * defined ADWORDS for adwordsSDK
 **/

#include "Support.h"
#include "cocos2d.h"
#import <AdSupport/AdSupport.h>

#if defined ADWORDS
#import "ACTReporter.h"
#endif
#if defined GOCPATRACKER
#import "GocpaTracker.h"
#endif
#if defined VERSION_D9
#import "D9SDKMainController.h"
#endif

#include "Account.h"

#if defined CHARTBOOST
@interface Support () <ChartboostDelegate>
@end
#endif

@implementation Support


static Support * _sharedSupportInstance = nil;

+ (void)initialize
{
    if (self == [Support class] && _sharedSupportInstance == nil)
    {
        _sharedSupportInstance = [ [self alloc] init];
        [_sharedSupportInstance initSupport];
    }
}
+ (id)shareSupport
{
    [Support initialize];
    return _sharedSupportInstance;
}

- (void) initSupport
{
    // init Support  ********** add by howe
    
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions{
    [Support removeAllNoticefication];
    Account::shareInstance()->init();

#if defined VERSION_D9
    [[D9SDKMainController sharedController] application:application didFinishLaunchingWithOptions:launchOptions];
#endif
    
#if defined APPSFLYER
    [AppsFlyerTracker sharedTracker].appleAppID = @"1022264513"; // The Apple app ID. Example 34567899
    [AppsFlyerTracker sharedTracker].appsFlyerDevKey = @"csnNQkJx8WJYKcKjHJMARC";
#endif
#if defined ADWORDS
    [ACTConversionReporter reportWithConversionID:@"941459643" label:@"_2ymCPyk1V4Qu5H2wAM" value:@"0.00" isRepeatable:NO];
#endif
    
#if defined CHARTBOOST
    [Chartboost startWithAppId:@"55b0a81fc909a64304216306"
                  appSignature:@"4ef32c764454dc8ac9a9048df4a94c7d6451d581"
                      delegate:self];
    
    [Chartboost cacheRewardedVideo:CBLocationMainMenu];
    [Chartboost cacheMoreApps:CBLocationHomeScreen];
    
#endif
    
    return YES;
}

- (void)applicationDidBecomeActive:(UIApplication *)application{
    
#if defined VERSION_D9
    [[D9SDKMainController sharedController] applicationDidBecomeActive:application];
#endif
    
#if defined CHARTBOOST
    [Chartboost showInterstitial:CBLocationHomeScreen];
#endif
    
#if defined APPSFLYER
    [[AppsFlyerTracker sharedTracker] trackAppLaunch]; //***** THIS LINE IS MANDATORY *****
    [AppsFlyerTracker sharedTracker].delegate = self; //Delegate methods below
#endif
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
#if defined VERSION_D9
    [[D9SDKMainController sharedController] application:application openURL:url sourceApplication:sourceApplication annotation:annotation];
    return YES;
#else
    return NO;
#endif
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    [Support removeAllNoticefication];
}

- (void) openGameUpdateAlert:(NSString *)newVersion isForceUpdate:(BOOL)force AndUrl:(NSString *)url withUpdateLog:(NSString *)text
{
    self.app_url = [NSString stringWithString:url];
    
    UIAlertView*alert = [[UIAlertView alloc]initWithTitle:@"Update"
                                                  message:text
                                                 delegate:self
                                        cancelButtonTitle:@"Cancel"
                                        otherButtonTitles:@"Update",nil];
    [alert show];
    [alert release];
    if (force)
    {
        [alert setTag:1];
    }
    else
    {
        [alert setTag:2];
    }
}

- (void) alertView:(UIAlertView *)alert clickedButtonAtIndex:(NSInteger)buttonIndex
{
    switch (alert.tag)
    {
        case 1://检查更新的alert, 强制
        {
            if (buttonIndex == 0)
            {
                exit(0);
            } else
            {
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:self.app_url]];
            }
            break;
        }
        case 2://检查更新的alert，非强制
        {
            if (buttonIndex == 1)
            {
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:self.app_url]];
            }
            break;
        }
        default:
            break;
    }
}

- (BOOL)shouldDisplayInterstitial:(NSString *)location {
    NSLog(@"about to display interstitial at location %@", location);
    
    // For example:
    // if the user has left the main menu and is currently playing your game, return NO;
    
    // Otherwise return YES to display the interstitial
    return YES;
}

#pragma mark Report Event
+ (void)ReportEvent:(NSString *)event amount:(float)amount currency:(NSString *)currency {

#if defined GOCPATRACKER
    GocpaTracker *tracker = [[GocpaTracker alloc]initWithAppId:@"ed91c7eecc4a40a38e2b8a6d479414e2" advertiserId:@"552" referral:false];
#endif
    
    NSString* ifa = [[[NSClassFromString(@"ASIdentifierManager") sharedManager] advertisingIdentifier] UUIDString];
    if (ifa) {
        ifa = [[ifa stringByReplacingOccurrencesOfString:@"-" withString:@""] lowercaseString];
        NSLog(@"IFA: %@",ifa);
#if defined GOCPATRACKER
        [tracker SetIDFA:ifa];
#endif
    }
    else {
        NSLog(@"IFA: No IFA returned from device");
    }
    
    if (amount > 0.0001){
#if defined GOCPATRACKER
        [tracker ReportEvent:event amount:amount currency:currency];
#endif
#if defined APPSFLYER
        [AppsFlyerTracker sharedTracker].currencyCode = currency;
        [[AppsFlyerTracker sharedTracker] trackEvent:event withValues: @{AFEventParamCurrency:currency,
                                                                                   AFEventParamRevenue:[NSString stringWithFormat:@"%f",amount]}];
#endif
    }
    else{
#if defined GOCPATRACKER
        [tracker ReportEvent:event];
#endif
#if defined APPSFLYER
        [[AppsFlyerTracker sharedTracker] trackEvent:event withValue:nil];
#endif
    }
    
    
    
}


#pragma mark AppsFlyerTrackerDelegate methods
- (void) onConversionDataReceived:(NSDictionary*) installData{
    id status = [installData objectForKey:@"af_status"];
    if([status isEqualToString:@"Non-organic"]) {
        id sourceID = [installData objectForKey:@"media_source"];
        id campaign = [installData objectForKey:@"campaign"];
        NSLog(@"This is a none organic install.");
        NSLog(@"Media source: %@",sourceID);
        NSLog(@"Campaign: %@",campaign);
    } else if([status isEqualToString:@"Organic"]) {
        NSLog(@"This is an organic install.");
    }
}

- (void) onConversionDataRequestFailure:(NSError *)error{
    NSLog(@"Failed to get data from AppsFlyer's server: %@",[error localizedDescription]);
}


static int m_nBadgeNumber = 0;

+ (NSString*) getLibraryCacheDirectory
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    
    NSString * path = [NSString stringWithFormat:@"%@/",documentsDirectory];
    return path;
}

+ (void) checkGameUpdateVersion:(NSString *)newVersion isForceUpdate:(BOOL)force AndUrl:(NSString *)url withUpdateLog:(NSString *)text
{
    [[Support shareSupport] openGameUpdateAlert:newVersion isForceUpdate:force AndUrl:url withUpdateLog:text];
}

+ (void)addNotificationSupportToSystem
{
    
#if __clang_major__ >= 6
    
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0)
    {
        if ([[UIApplication sharedApplication] isRegisteredForRemoteNotifications])
        {
            return;
        }
        
        [[UIApplication sharedApplication] registerUserNotificationSettings:[UIUserNotificationSettings
                                                                             settingsForTypes:UIUserNotificationTypeAlert
                                                                             categories:nil]];
        
        
        [[UIApplication sharedApplication] registerForRemoteNotifications];
    }
    else
#endif
    {
        
        [[UIApplication sharedApplication] registerForRemoteNotificationTypes:UIRemoteNotificationTypeAlert];
    }
}

+ (void)addLocalNotification:(NSString *)key forText:(NSString *)text withTime:(NSNumber *) deltaTime
{
//
    UILocalNotification *note;
    
    NSDate* fireDate = NULL;
    
    fireDate = [NSDate dateWithTimeIntervalSinceNow:[deltaTime doubleValue]];
    if (fireDate != NULL) {
        
        note = [[UILocalNotification alloc] init];
        note.timeZone = [NSTimeZone systemTimeZone];
        note.alertBody = text;
        note.fireDate = fireDate;
        
        NSDictionary *info = [NSDictionary dictionaryWithObject:key forKey:key];
        note.userInfo = info;
        note.applicationIconBadgeNumber =  ++m_nBadgeNumber;
//        this->m_nBadgeNumber ++;
        [[UIApplication sharedApplication] scheduleLocalNotification:note];
        [note release];
    }
}

+ (void)removeAllNoticefication
{
    m_nBadgeNumber = 0;
    [[UIApplication sharedApplication] cancelAllLocalNotifications];
}

+ (void)removeNotificationByKey:(NSString *) key
{
    UIApplication *app = [UIApplication sharedApplication];
    NSArray *localArray = [app scheduledLocalNotifications];
    UILocalNotification *localNotification = nil;
//    NSString *nsKey = [NSString stringWithCString:key encoding:NSUTF8StringEncoding];
    if (localArray) {
        for (UILocalNotification *noti in localArray) {
            NSDictionary *dict = noti.userInfo;
            if (dict) {
                
                NSString *inKey = [dict objectForKey:key];
                if ([inKey isEqualToString:key]) {
                    if (localNotification){
                        [localNotification release];
                        localNotification = nil;
                    }
                    localNotification = [noti retain];
                    break;
                }
            }
        }
        if (localNotification) {
            
            //不推送 取消推送
            [app cancelLocalNotification:localNotification];
            
            [localNotification release];
            
        }
    }
}





@end

