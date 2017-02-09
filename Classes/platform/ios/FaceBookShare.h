//
//  FaceBookShare.h
//  MegoGame
//
//  Created by Relvin on 15/11/9.
//
//

#import <Foundation/Foundation.h>
#import <FBSDKShareKit/FBSDKShareKit.h>
#import <FBSDKCoreKit/FBSDKCoreKit.h>

@interface FaceBookShare : NSObject
{

}

+ (id)sharedFaceBook;

-(void)ShareToFacebook:(NSURL *) shareURL imagePickerController:(UIImagePickerController *)picker
didFinishPickingMediaWithInfo:(NSDictionary *)info;
- (void)InviteFacebook:(NSURL *) inviteAppURL imgPathUrl:(NSURL *) imgURL;
-(void)ShareToFacebookDesc:(NSURL *) shareURL ShareDesc:(NSString *)desc
ShareTitle:(NSString *)title;

@end