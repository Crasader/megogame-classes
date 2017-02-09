//
//  Account.cpp
//  client
//
//  Created by yuxiao on 14-6-19.
//
//

#include "Account.h"

void Account::applicationWillResignActive(void *iosUIApplication)
{

}

void Account::applicationDidBecomeActive(void *iosUIApplication)
{

}

void Account::applicationDidEnterBackground(void *iosUIApplication)
{

}

void Account::applicationWillEnterForeground(void *iosUIApplication)
{

}

void Account::applicationWillTerminate(void *iosUIApplication)
{

}

void Account::applicationDidRegisterForRemoteNotificationsWithDeviceToken(void *iosNSData)
{

}

void Account::applicationDidReceiveRemoteNotification(void *iosNSDictionary)
{
    NSDictionary *userInfo = (NSDictionary *)iosNSDictionary;
    
	if ([[userInfo objectForKey:@"aps"] objectForKey:@"alert"] != NULL) {
		UIAlertView* alert = [[UIAlertView alloc] initWithTitle:@"消息"
														message:[[userInfo objectForKey:@"aps"] objectForKey:@"alert"]
													   delegate:nil
											  cancelButtonTitle:@"关闭"
											  otherButtonTitles:@"显示",nil];
		[alert show];
	}
    
    [[UIApplication sharedApplication] setApplicationIconBadgeNumber:0];
}

bool Account::applicationOpenURL(void *iosUIApplication, void *iosNSURL, void *iosNSString)
{
    
    return YES;
}

