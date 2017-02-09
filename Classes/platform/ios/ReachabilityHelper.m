//
//  ReachabilityHelper.m
//  MegoGame
//
//  Created by howe on 15/5/4.
//
//

#import "ReachabilityHelper.h"

@interface ReachabilityHelper()

@property (retain,nonatomic) Reachability * reachability;

@end

@implementation ReachabilityHelper

-(instancetype)initHelper
{
    self = [super init];
    if (self)
    {
        [self initNet];
    }
    return self;
}

-(void)initNet
{
    self.reachability = [Reachability reachabilityWithHostname:@"www.apple.com"];
    NSLog(@"当前网络 ： %@",self.reachability.currentReachabilityString);
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(reachabilityChanged:)
                                                 name:kReachabilityChangedNotification
                                               object:nil];
}
- (void) reachabilityChanged: (NSNotification*)note
{
    NSLog(@"网络连接变化 %@",note);
    Reachability * reach = [note object];
    
    if(![reach isReachable])
    {
        UIAlertView* dialog = [[UIAlertView alloc] init];
        [dialog setDelegate:self];
        [dialog setTitle:@"warnning"];
        [dialog setMessage:@"No network connection!"];
        [dialog addButtonWithTitle:@"Exit"];
        [dialog show];
        [dialog release];
        return;
    }
    
    if (reach.isReachableViaWiFi) {
//        @"当前通过wifi连接"
    } else {
//        @"wifi未开启，不能用";
    }
    
    if (reach.isReachableViaWWAN) {
        //@"当前通过2g or 3g连接";
    } else {
        //@"2g or 3g网络未使用";
    }
}

@end
