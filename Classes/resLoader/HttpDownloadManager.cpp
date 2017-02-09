//
//  HttpDownloadManager.cpp
//  RoN
//
//  Created by CoA Studio on 13-3-19.
//
//

#include "HttpDownloadManager.h"
#include "cocos2d_specifics.hpp"
#include "jsapi.h"

#include <stdio.h>

#include "../common/Util.h"
HttpDownloadManager * _instance = nullptr;

int _currentHttpIndex = 0;

HttpDownloadManager::HttpDownloadManager()
{}

HttpDownloadManager::~HttpDownloadManager()
{

}

HttpDownloadManager * HttpDownloadManager::getInstance()
{
    if (!_instance)
    {
        _instance = new HttpDownloadManager();
        _instance->retain();
    }
    return _instance;
}

bool HttpDownloadManager::setHttpRequest(const std::string & uuid,const std::string & url,const std::string & savepath,bool isImmediate)
{
    if (isInDownLoadList(uuid))
    {
        return false;
    }
    auto httpRequest = new RHttpRequest();
    httpRequest->setTag(uuid.c_str());
    httpRequest->setUrl(url.c_str());
    httpRequest->setSavedPath(savepath);
//    httpRequest->setFileSize(fileSize);
    httpRequest->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    httpRequest->setResponseCallback(CC_CALLBACK_2(HttpDownloadManager::_httpCallback,this));
    if (isImmediate)
    {
        HttpClient::getInstance()->sendImmediate(httpRequest);
    }
    else
    {
        HttpClient::getInstance()->send(httpRequest);
    }
    httpRequest->release();
    
    _httpRequestHash[uuid] = httpRequest;
    return true;
}

void HttpDownloadManager::stopAllHttpRequest()
{
    _httpRequestHash.clear();
    HttpClient::getInstance()->destroyInstance();
}

void HttpDownloadManager::_httpCallback(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    do
    {
        auto request = dynamic_cast<RHttpRequest*>(response->getHttpRequest());
        CC_BREAK_IF(!request);
        
        std::string uuid(request->getTag());
        
        auto ite = _httpRequestHash.find(uuid);
        if (ite != _httpRequestHash.end())
        {
            _httpRequestHash.erase(ite);
        }
        bool isSuccess = response->isSucceed() && (response->getResponseCode() > 199 && response->getResponseCode() < 300);
        if ( isSuccess )
        {
            auto buffer = response->getResponseData();
            
            const std::string &saveFullpath = Util::getRealFullpath(request->getSavedPath());
            if ( !saveFullpath.empty() )
            {
                FILE *fp = fopen( saveFullpath.c_str() , "wb");
                if (fp)
                {
                    auto len = buffer->size();
                    unsigned char *pbuffer = new unsigned char[len];
                    memset(pbuffer, 0, len);
                    for (size_t i = 0; i < len; i++)
                    {
                        pbuffer[i] = buffer->at(i);
                    }
                    fwrite(pbuffer, sizeof(unsigned char),len,fp);
                    delete [] pbuffer;
                    fclose(fp);
                }else
                {
                    isSuccess = false;
                }
            }else
            {
                isSuccess = false;
            }

        }else
        {
            std::stringstream ss;
            ss << "ResponseCode:";
            ss << response->getResponseCode();
            ss << ", URL: ";
            ss << request->getUrl();
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
//            MessageBox(ss.str().c_str(), "http error");
#endif
            ___sendErrorLog(ss.str());
            CCLOG("http response error  httpcode %ld, errormsg: %s",response->getResponseCode(),response->getErrorBuffer());
        }
        _callJsHandler(uuid, isSuccess,(int)response->getResponseCode());
    }
    while (0);
}

void HttpDownloadManager::_callJsHandler(const std::string & uuid,bool isSuccess,int code)
{
    // tell js
    static const char _EVENT_CALL[] = "fileUpdatedHandler";
    ScriptingCore* sc = ScriptingCore::getInstance();
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject gl(cx, ScriptingCore::getInstance()->getGlobalObject());
    JS::RootedValue temp_retval(cx);
    JS_GetProperty(sc->getGlobalContext(), gl, "gameAssets", &temp_retval);
    if (temp_retval != JSVAL_VOID)
    {
        jsval valArr[3];
        valArr[0] = std_string_to_jsval(cx,uuid);
        valArr[1] = BOOLEAN_TO_JSVAL(isSuccess);
        valArr[2] = INT_TO_JSVAL(code);

        sc->executeFunctionWithOwner(temp_retval, _EVENT_CALL, JS::HandleValueArray::fromMarkedLocation(3, valArr));
    }
}












