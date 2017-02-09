//
//  platform_pp.mm
//  client
//
//  Created by YQ on 13-3-5.
//
//

#include "platform_d9.h"

#import "D9SDKMainController.h"
#import "D9DealBackGroundManager.h"
#include "PlatformManager.h"

static D9SDKMainController *s_d9SDK = NULL;


@interface D9StudioDelegate : NSObject <D9ViewDelegate>
+(D9SDKMainController*)instance;
@end

@implementation D9StudioDelegate
+(D9StudioDelegate*)instance
{
    static D9StudioDelegate *instance = nil;
    if(instance == nil) {
        instance = [[D9StudioDelegate alloc] init];
    }
    return instance;
}



//登陆成功回调
- (void)loginSuccess:(NSMutableDictionary *)result
{

    NSLog(@"Dependent App: D9StudioSDK Logged in.");
    
    NSString *userID = [result objectForKey:@"userid"];
//
    Account::shareInstance()->doLoginGame([userID UTF8String]);
//    std::vector<std::string> arr = {accountId};
//    PlatformManager::loginSuccessAndCallJS(arr);

}

//注册成功回调
-(void)registerSuccess:(NSMutableDictionary *)result
{

}

// 改密成功回调
- (void)changePassWordSuccess:(NSMutableDictionary *)result
{

}


//快速登回调
- (void)quicklyLogin:(NSString *)userId
{
    if (userId) {
        Account::shareInstance()->doLoginGame([userId UTF8String]);
//        std::vector<std::string> arr ;
//        arr.push_back(accId);
//        PlatformManager::loginSuccessAndCallJS(arr);
    }
}
// 关闭个人中心回调
- (void)d9CloseView:(D9CloseView)selfCenterView
{

}

// 切换账号回调
- (void)switchCountback{
    Account::shareInstance()->switchAccount();
}

- (void)loginIn
{
    if (![s_d9SDK isHadLogin]) {
        [s_d9SDK showLoginView];
    }
}
@end

void D9Account ::switchAccount()
{
    Account::switchAccount();
    if ([s_d9SDK isHadLogin]) {
        [s_d9SDK switchCount];
    }
}

void D9Account::init()
{
    if(s_d9SDK == NULL) {
        s_d9SDK  = [[D9SDKMainController sharedController] initWithAppid:@"100002" platformID:@"dhen" appKey:@"ef2ee2f39009f303e62d00bb34f5d254" updataLevel:D9Update_Level_Normal];
    }
    
    [s_d9SDK setDelegate:[D9StudioDelegate instance]];
}

void D9Account::login()
{
    if (![s_d9SDK isHadLogin]) {
        [s_d9SDK showLoginView];
    }
}

void D9Account::logout()
{
    if ([s_d9SDK isHadLogin]) {
        [s_d9SDK switchCount];
    }
}
void D9Account::center()
{
    if ([s_d9SDK isHadLogin]) {
        [s_d9SDK showSelfCenternavigationView:nil];
    }

}

void D9Account::buy(std::map<std::string,std::string> & mapValues)
{
    /*
     appid     应用id （由服务器分配）
     uid    萌果账号id  (登陆时候反回的uid)
     roleid     游戏内用户id （游戏角色id）
     productId      产品id  (就是在苹果注册产品的时候，使用的id)
     goodid         商品id  (游戏商品id)
     goodscount        商品数量
     goodsName         //商品名字
     currency         //货币类型
     description        //商品描述
     price      //  价格
     */
    [s_d9SDK appStorePay:@"100002"
                     uid:[NSString stringWithUTF8String:mapValues["SDK_TOKEN"].c_str()]
                  roleId:[NSString stringWithUTF8String:mapValues["G_ROLE_ID"].c_str()]
               productId:[NSString stringWithUTF8String:mapValues["B_PRODUCT_ID"].c_str()]
                 goodsId:[NSString stringWithUTF8String:mapValues["B_GOODS_ID"].c_str()]
              goodsCount:[NSString stringWithUTF8String:mapValues["B_BUY_ITEM_CNT"].c_str()]
               goodsName:[NSString stringWithUTF8String:mapValues["B_GOODS_NAME"].c_str()]
                   price:[NSString stringWithUTF8String:mapValues["B_BUY_ITEM_PRICE"].c_str()]
                currency:[NSString stringWithUTF8String:mapValues["B_CURRENCY_TYPE"].c_str()]
             description:[NSString stringWithUTF8String:mapValues["B_PAY_DESCRIPTION"].c_str()]
     ];

}

