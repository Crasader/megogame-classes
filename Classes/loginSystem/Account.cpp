//
//  Account.cpp
//  client
//
//  Created by yuxiao on 13-12-24.
//
//
#include "Account.h"
#include "../platform/PlatformManager.h"
#include "cocostudio/DictionaryHelper.h"
#include <vector>

using namespace cocostudio;

#if defined VERSION_APP
#include "platform_app_store.h"
#endif

#if defined VERSION_KY
#include "platform_ky.h"
#endif

#if defined VERSION_D9
#include "platform_d9.h"
#endif

#if defined VERSION_PP
#include "platform_pp.h"
#endif

#if defined VERSION_UC
#include "platform_uc.h"
#endif

#if defined VERSION_91
#include "platform_91.h"
#endif

#if defined VERSION_PPS
#include "platform_pps.h"
#endif

#if defined VERSION_IDS
#include "platform_ids.h"
#endif

#if defined VERSION_ITOOLS
#include "platform_itools.h"
#endif

#if defined VERSION_JJZS
#include "platform_txwy.h"
#endif

#if defined VERSION_TONGBUTUI
#include "platform_tbt.h"
#endif

#if defined VERSION_I4
#include "platform_i4.h"
#endif

#if defined VERSION_HAIMA
#include "platform_haima.h"
#endif

#if defined VERSION_XY
#include "platform_xy.h"
#endif

#if 0 //CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "AndroidAccount.h"
#include "platform_android.h"
#endif

#ifdef ANDROID_COMM_VERSION
#include "AndroidAccount.h"
#include "PlatformMgr.h"
#endif


Account *Account::shareInstance()
{
    
    static Account *account = NULL;
    
    if(account == NULL)
    {
#if defined VERSION_KY
        account = new KYAccount();
        
#elif defined VERSION_APP111 || VERSION_CHANGBA || VERSION_D9
        account = new D9Account();
        
#elif defined VERSION_PP
        account = new PPAccount();
        
#elif defined VERSION_UC
        account = new UCAccount();
        
#elif defined VERSION_91
        account = new NdComAccount();

#elif defined VERSION_PPS
        account = new PPSAccount();
        
#elif defined VERSION_IDS
        account = new IdsAccount();
        
#elif defined VERSION_ITOOLS
        account = new iToolsAccount();
        
#elif defined VERSION_JJZS
        account = new TxwyAccount();
        
#elif defined VERSION_TONGBUTUI
        account = new TBTAccount();
        
#elif defined VERSION_I4
        account = new i4Account();
        
#elif defined VERSION_HAIMA
        account = new haimaAccount();
        
#elif defined VERSION_XY
        account = new xyAccount();
        
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        #ifdef ANDROID_COMM_VERSION
            account = new AndroidAccount();
        #else
            //
            account = new Account();
        #endif
#else
        account = new Account();
#endif
        

    }
    return account;
}

void Account::buy(const std::string& jsString)
{
    rapidjson::Document doc;
    doc.Parse(jsString.c_str());
    
    std::map<std::string,std::string> jsonValues;
    jsonValues.clear();
    for (int i = 0; i < sizeof(shopKeyValue) / sizeof(shopKeyValue[0]); i++){
        std::string jsonValue = DictionaryHelper::getInstance()->getStringValue_json(doc,shopKeyValue[i].c_str());
        jsonValues[shopKeyValue[i]] = jsonValue;
    }
    
    this->buy(jsonValues);
    
}

void Account::buy(std::map<std::string,std::string> & mapValues)
{
    
}

Account::Account()
: m_sAccountId ("")
{
    
}

void Account::login(){
    this->doLoginGame("DefaultLogin");
}

void Account::doLoginGame(const std::string& accountId)
{
    if (accountId.length() > 3){
        m_sAccountId = accountId;
        std::vector<std::string> arr ;
        arr.push_back(m_sAccountId);
        PlatformManager::loginSuccessAndCallJS(arr);
    }

}

void Account::doLogoutGame()
{
    this->clearLoginUid();
    PlatformManager::logOutAndCallJS();
}

void Account::clearLoginUid()
{
    m_sAccountId = "";
}

const std::string& Account::getLoginUid() const
{
    return m_sAccountId;
}

bool Account::isLogin()
{
    if (m_sAccountId.length() > 3)
    {
        return true;
    }
    return false;
}


std::string Account::platformCall(const std::string action, const std::string params)
{
    // js call platform
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    // ios todo
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#ifdef ANDROID_COMM_VERSION
    platform::PlatformMgr::getInstance()->call(action.c_str(), params.c_str());
#endif
#endif
    
    return "";
}



std::string Account::gameCall(const std::string action, const std::string params)
{
    PlatformManager::gameCall(action,params);
    return "";
}


