//
//  CURLHelper.h
//  MegoGame
//
//  Created by howe on 15/6/15.
//
//

#ifndef __MegoGame__CURLHelper__
#define __MegoGame__CURLHelper__

#include <stdio.h>
#include "cocos2d.h"


class CURLHelper
{
public:
    CURLHelper();
    ~CURLHelper();
    
    static std::string getHttpString(const std::string &url);
    
    static long getDownloadFileSize(const std::string &url);
    
    static long getLocalFileSize(const std::string &localpath);
    
    static std::string getHttpHeader(const std::string & url);
    
    static int downloadFile(const std::string &path,const std::string &url);
    
};

#endif /* defined(__MegoGame__CURLHelper__) */
