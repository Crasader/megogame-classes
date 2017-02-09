//
//  RHttpRequest.h
//  MegoGame
//
//  Created by howe on 15/6/15.
//
//

#ifndef __MegoGame__RHttpRequest__
#define __MegoGame__RHttpRequest__

#include <stdio.h>
#include "cocos2d.h"
#include "network/HttpRequest.h"

USING_NS_CC;

class RHttpRequest : public cocos2d::network::HttpRequest
{
public:
    RHttpRequest()
    :_uuid(""),_savedPath(""),_fileSize(0)
    {
    
    };
    void setFileSize(int size)
    {
        _fileSize = size;
    }
    int getFileSize()
    {
        return _fileSize;
    }
    void setSavedPath(const std::string &savePath)
    {
        _savedPath = savePath;
    }
    const std::string & getSavedPath()
    {
        return _savedPath;
    }
    
    void setHttpUUID(const std::string &downloadId)
    {
        _uuid = downloadId;;
    }
    const std::string & getHttpUUID()
    {
        return _uuid;
    }
private:
    std::string _uuid;
    std::string _savedPath;
    int _fileSize;
};

#endif /* defined(__MegoGame__RHttpRequest__) */
