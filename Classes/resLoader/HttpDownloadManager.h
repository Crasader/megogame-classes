//
//  HttpDownloadManager.h
//  RoN
//
//  Created by CoA Studio on 13-3-19.
//
//

#ifndef RoN_HttpDownloadManager_h
#define RoN_HttpDownloadManager_h

#include "cocos2d.h"
#include "RHttpRequest.h"
#include "network/HttpClient.h"
using namespace network;
USING_NS_CC;

class HttpDownloadManager : public Ref
{
public:
    HttpDownloadManager();
    virtual ~HttpDownloadManager();
    
    static HttpDownloadManager * getInstance();
    
    bool setHttpRequest(const std::string & uuid,const std::string & url,const std::string & savepath,bool isImmediate);
    
    void stopAllHttpRequest();
        
    bool isInDownLoadList(const std::string & uuid)
    {
        return _httpRequestHash.find(uuid) != _httpRequestHash.end();
    }
private:
    
    void _httpCallback(HttpClient* client, HttpResponse* response);
    
    void _callJsHandler(const std::string & uuid,bool isSuccess,int code);
private:
    std::map<std::string,RHttpRequest*> _httpRequestHash;
};

#endif
