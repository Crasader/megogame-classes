//
//  IOSUtil.h
//
//  Created by ziRoy on 12-7-9.
//

#ifndef __IOSUtil_h__
#define __IOSUtil_h__
#include <iostream>

class IOSUtil
{
public:
    
    static std::string udidType;
    
    static bool should2X();
    
    static void SinaLayer_onCancel();
    static void SinaLayer_onSignOut();
    static void SinaLayer_onSend( const char* _str );
    
    static void OpenUrl(const char* _url);
    static void OpenUrlInner(const char* _url);
    
    static bool isConnectedToNet();
    
    static const char* GetIconPath();
    
    static std::string udid();
    static std::string macString();
    static std::string idfaString();
    static std::string idfvString();
    static std::string openUDID();
    
    static float systemVersion();

    static std::string getLibraryCacheDirectory();
};

#endif
