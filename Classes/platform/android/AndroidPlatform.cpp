//
//  AndroidPlatform.cpp
//  MegoGame
//
//  Created by howe on 15/4/14.
//
//


#include "AndroidPlatform.h"

#include "cocos2d.h"

USING_NS_CC;

#ifdef ANDROID_COMM_VERSION
#include "platform_android.h"
#endif

//
//#include <android/log.h>
//#include "jni.h"
//#include "jni/JniHelper.h"
//#include "platform/CCPlatformMacros.h"
//USING_NS_CC;

//
//  Win32Platform.cpp
//  MegoGame
//
//  Created by howe on 15/4/14.
//
//

AndroidPlatform::~AndroidPlatform() {
    
};
std::string AndroidPlatform::getAppVersion() const
{
//    std::string ret("");
//    JniMethodInfo t;
//
//    if (JniHelper::getStaticMethodInfo(t, "com/abc", "getAppVersion", "()Ljava/lang/String;"))
//    {
//        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
//        t.env->DeleteLocalRef(t.classID);
//        ret = JniHelper::jstring2string(str);
//        t.env->DeleteLocalRef(str);
//    }
//    if (ret != "")
//    {
//        return ret;
//    }
#ifdef ANDROID_COMM_VERSION
    return PlatformGetAppVersion();
#endif

    return "";
}
//get the mac address of device
std::string AndroidPlatform::getMacAddress() const{
#ifdef ANDROID_COMM_VERSION
    return PlatformGetMacAddr();
#endif

    return "";
}

//wiki http://zh.wikipedia.org/wiki/IOS%E8%AE%BE%E5%A4%87%E5%88%97%E8%A1%A8
std::string AndroidPlatform::getDeviceType() const{
    
#ifdef ANDROID_COMM_VERSION
    return PlatformGetModel();
#endif

    return "";
}
//系统
std::string AndroidPlatform::getDeviceSystem() const{
    
    return "Android";
}
//内存
std::string  AndroidPlatform::getDeviceMemory() const{
    //    //get all memory
#ifdef ANDROID_COMM_VERSION
    return PlatformGetTotalMem();
#endif

    return "";
}
//网络
NetworkType AndroidPlatform::getNetworkType() const{
#ifdef ANDROID_COMM_VERSION
    int type = PlatformGetNetType();

    return type == 1 ? NET_WIFI : type == 2 ? NET_3G : NET_NULL;
#endif

    return NET_WIFI;
}
//UID
std::string AndroidPlatform::getDeviceUid() const{
#ifdef ANDROID_COMM_VERSION
    return PlatformGetDeviceId();
#endif

    return "";
}
//UID类型
std::string AndroidPlatform::getDeviceUidType() const{
#ifdef ANDROID_COMM_VERSION
    return PlatformGetDeviceIdType();
#endif

    return "";
}
//设备名字
std::string AndroidPlatform::getDeviceName() const{
#ifdef ANDROID_COMM_VERSION
    return PlatformGetModel();
#endif

    return "";
}

std::string AndroidPlatform::getPlatformId() const
{
#ifdef ANDROID_COMM_VERSION
    int channelId = PlatformGetAccountChannel();
    char buf[32] = {0};
    sprintf(buf, "%d", channelId);
    std::string result = buf;
    CCLOG("getPlatformId:%s", result.c_str());
    return result;
#endif

    return "1";
}


void AndroidPlatform::setTextInPasteboard(std::string text) const{
#ifdef ANDROID_COMM_VERSION
    PlatformSetClipboardText(text);
#endif
//    java 代码
//    ClipboardManager copy = (ClipboardManager) MainActivity.this.getSystemService(Context.CLIPBOARD_SERVICE);
//    copy.setText("Come On Baby");
}

std::string AndroidPlatform::getDeviceToken()
{
    return "android_device_token";
}


static char buf[512];
void AndroidPlatform::reportEvent(std::string event,float amount ,std::string currency )
{
#ifdef ANDROID_COMM_VERSION
    sprintf(buf, "Id=%s", event.c_str());
    platform::PlatformMgr::getInstance()->call("Umeng", "Event", buf);
    platform::PlatformMgr::getInstance()->call("TalkingData", "Event", buf);
#endif
}

void AndroidPlatform::addNotification(std::string id, int seconds, std::string info)
{
#ifdef ANDROID_COMM_VERSION
    cocos2d::log("AndroidPlatform::addNotification:%s,%d,%s", id.c_str(), seconds, info.c_str());
    PlatformAddNotification(id.c_str(), seconds, info.c_str());
#endif
}

void AndroidPlatform::addNotificationInWeek(std::string id, int atDay, int atHour, int atMin, std::string  info)
{
#ifdef ANDROID_COMM_VERSION
    cocos2d::log("AndroidPlatform::addNotificationInWeek:%s,%d-%d-%d,%s", id.c_str(), atDay, atHour, atMin, info.c_str());
    PlatformAddNotificationInWeek(id.c_str(), atDay, atHour, atMin, info.c_str());
#endif
}

void AndroidPlatform::deleteAllNotification()
{
#ifdef ANDROID_COMM_VERSION
    cocos2d::log("deleteAllNotification");
    PlatformDelAllNotification();
#endif
}

void AndroidPlatform::sharedFaceBook(const std::string &url,const std::string &des,const std::string &title)
{
    sharedFaceBook(url, des, title, "");
}

void AndroidPlatform::sharedFaceBook(const std::string &url,const std::string &des,const std::string &title, const std::string &imgUrl)
{
#ifdef ANDROID_COMM_VERSION
    sprintf(buf, "Title=%s|Url=%s|ImageUrl=%s|Desc=%s", title.c_str(), url.c_str(), (imgUrl.length() > 0 ? imgUrl.c_str() : ""), des.c_str());
    platform::PlatformMgr::getInstance()->call("ShareFb", buf);
#endif
}

