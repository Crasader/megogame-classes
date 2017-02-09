//
//  Support.h
//  MegoGame
//
//  Created by Relvin on 15/6/23.
//
//

#ifndef MegoGame_Support_h
#define MegoGame_Support_h

#import <Foundation/Foundation.h>
#if defined CHARTBOOST
#import <Chartboost/Chartboost.h>
#endif
#if defined APPSFLYER
#import "AppsFlyerTracker.h"
#endif
#include "cocos2d.h"

USING_NS_CC;

@interface Support : NSObject <UIAlertViewDelegate
#if defined CHARTBOOST
,ChartboostDelegate
#endif
#if defined APPSFLYER
,AppsFlyerTrackerDelegate
#endif
>

@property (nonatomic,copy) NSString *app_url;

+(id)shareSupport; // single instance  ****This method shouldnot call in JS！！！

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;

- (void) openGameUpdateAlert:(NSString *)newVersion isForceUpdate:(BOOL)force AndUrl:(NSString *)url withUpdateLog:(NSString *)text;

- (void)applicationDidBecomeActive:(UIApplication *)application;
- (void)applicationWillEnterForeground:(UIApplication *)application ;

+ (void)ReportEvent:(NSString*)event amount:(float)amount currency:(NSString*)currency;


+ (void)addNotificationSupportToSystem;
+ (void)addLocalNotification:(NSString *)key forText:(NSString *)text withTime:(NSNumber *) deltaTime;
+ (void)removeNotificationByKey:(NSString *) key;
+ (void)removeAllNoticefication;

+ (NSString*) getLibraryCacheDirectory;

+ (void) checkGameUpdateVersion:(NSString *)newVersion isForceUpdate:(BOOL)force AndUrl:(NSString *)url withUpdateLog:(NSString *)text;

@end

#endif
