//
//  FaceBookShare.m
//  MegoGame
//
//  Created by Relvin on 15/11/9.
//
//

#import "FaceBookShare.h"
#import <FBSDKCoreKit/FBSDKCoreKit.h>
#import <FBSDKLoginKit/FBSDKLoginKit.h>
#import <FBSDKShareKit/FBSDKShareKit.h>
#import "D9SDKMainController.h"
#include "PlatformManager.h";


@interface FaceBookShare () <FBSDKSharingDelegate,FBSDKAppInviteDialogDelegate>
@end

static NSInteger slot = 0;
@implementation FaceBookShare

+ (id)sharedFaceBook
{
    static dispatch_once_t pred = 0;
    __strong static id sharedFaceBook = nil;
    dispatch_once(&pred, ^{
        sharedFaceBook = [[self alloc] init]; // or some other init method
    });
    return sharedFaceBook;
}

-(void )ShareToFacebookDesc:(NSURL *) shareURL ShareDesc:(NSString *)desc
                                   ShareTitle:(NSString *)title
{
    FBSDKShareLinkContent *content = [[FBSDKShareLinkContent alloc]init];
    content.contentURL = shareURL;
    content.contentTitle = title;
    content.contentDescription = desc;
    
//    FBSDKShareDialog *shareDialog = [[FBSDKShareDialog alloc] init];
//    shareDialog.shareContent = content;//
    [FBSDKShareDialog showFromViewController:[D9SDKMainController sharedController] withContent: content delegate: self];
//    [FBSDKShareAPI shareWithContent: content delegate: self];
}

- (void)sharer:(id<FBSDKSharing>)sharer didCompleteWithResults:(NSDictionary *)results
{
    std::string result = "0";
    if ([results count] > 0)
    {
        result = "1";
    }
    PlatformManager::gameCall("shareCompletedCallback",result);
    NSLog(@"completed share:%@", results);
}

- (void)sharer:(id<FBSDKSharing>)sharer didFailWithError:(NSError *)error
{
    NSLog(@"sharing error:%@", error);
    NSString *message = error.userInfo[FBSDKErrorLocalizedDescriptionKey] ?:
    @"There was a problem sharing, please try again later.";
    NSString *title = error.userInfo[FBSDKErrorLocalizedTitleKey] ?: @"Oops!";
    
    [[[UIAlertView alloc] initWithTitle:title message:message delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil] show];
}

- (void)sharerDidCancel:(id<FBSDKSharing>)sharer
{
    NSLog(@"share cancelled");
}

-(void)appInviteDialog:(FBSDKAppInviteDialog *)appInviteDialog didCompleteWithResults:(NSDictionary *)results
{
    
}

- (void)appInviteDialog:(FBSDKAppInviteDialog *)appInviteDialog didFailWithError:(NSError *)error
{
    
}

@end

