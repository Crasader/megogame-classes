//
//  CURLHelper.cpp
//  MegoGame
//
//  Created by howe on 15/6/15.
//
//

#include "CURLHelper.h"
#include "../common/Util.h"
#include <curl/curl.h>
#include <curl/easy.h>
using namespace std;


static size_t getCharCode(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    string *content = (string*)userdata;
    content->append((char*)ptr, size * nmemb);
    return (size * nmemb);
}

/* */

size_t wirtefunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
    FILE *fp = (FILE*)stream;
    size_t written = fwrite(ptr, size, nmemb, fp);
    return written;
}
int CURLHelper::downloadFile(const string &path,const string &url)
{
    FILE *localFile = fopen(Util::getRealFullpath(path).c_str(), "wb+");
    
    CURL *curlhandle = curl_easy_init();
    curl_easy_setopt(curlhandle, CURLOPT_URL, url.c_str());
    
    curl_easy_setopt(curlhandle, CURLOPT_WRITEDATA, localFile);
    curl_easy_setopt(curlhandle, CURLOPT_WRITEFUNCTION, wirtefunc);
    curl_easy_setopt(curlhandle, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curlhandle, CURLOPT_NOSIGNAL, 1L);
    
    CURLcode res = curl_easy_perform(curlhandle);
    fclose(localFile);
    curl_easy_cleanup(curlhandle);
    
    if (res == CURLE_OK)
    {
        return 0;
    }
    CCLOG("can not get file content,curl error code is %d", res);
    return res;
}


/**
 *  @param url
 *  @return
 */
string CURLHelper::getHttpString(const string &url)
{
    std::string str = "";
    CURL *handle = curl_easy_init();
    if (! handle)
    {
        CCLOG("can not init curl");
        return str;
    }
    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, getCharCode);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &str);
    curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1L);
    
    //    curl_easy_setopt( handle, CURLOPT_TIMEOUT, 3 );
    CURLcode res = curl_easy_perform(handle);
    if (res != CURLE_OK)
    {
        str="";
        CCLOG("can not get file content,curl error code is %d", res);
    }
    curl_easy_cleanup(handle);
    return str;
}
string CURLHelper::getHttpHeader(const string & url)
{
    std::string str = "";
    CURL *handle = curl_easy_init();
    if (! handle)
    {
        CCLOG("can not init curl");
        return str;
    }
    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
    
    curl_easy_setopt(handle, CURLOPT_HEADER, 1L);
    curl_easy_setopt(handle, CURLOPT_NOBODY, 1L);
    
    curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION,getCharCode);
    curl_easy_setopt(handle, CURLOPT_HEADERDATA,&str);
    curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1L);
    
    CURLcode res = curl_easy_perform(handle);
    if (res != CURLE_OK)
    {
        CCLOG("can not get header, curl error code is %d", res);
    }
    curl_easy_cleanup(handle);
    return str;
}

/**
 *  @param url
 *  @return
 */
long CURLHelper::getDownloadFileSize(const string &url)
{
    double downloadFileLenth = 0;
    CURL *handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_HEADER, 0L);
    curl_easy_setopt(handle, CURLOPT_NOBODY, 1L);
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1L);
    
    CURLcode res = curl_easy_perform(handle);
    
    if (res == CURLE_OK)
    {
        curl_easy_getinfo(handle, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &downloadFileLenth);
    }
    else
    {
        downloadFileLenth = 0;
        CCLOG("can not get file content,curl error code is %d", res);
    }
    
    curl_easy_cleanup(handle);
    return downloadFileLenth;
}
/**
 *  获取本地文件大小
 *  @param localpath
 *  @return
 */
long CURLHelper::getLocalFileSize(const string &localpath)
{
    return 0;
//    curl_off_t local_file_len = 0;
//    struct stat file_info;
//    if(stat(localpath, &file_info) == 0)
//    {
//        local_file_len =  file_info.st_size;
//    }
//    return local_file_len;
}


