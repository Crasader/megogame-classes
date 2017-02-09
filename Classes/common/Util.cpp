//
//  Util.cpp
//  MegoGame
//
//  Created by howe on 15/3/13.
//
//

#include "Util.h"


#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCObjectExtensionData.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    #include "../platform/win32/Win32Platform.h"
#else
    #include "OgreSearchOps.h" // unix /linux
#endif
using namespace std;


std::vector<std::string> Util::findPaths(const std::string &dir_path,const std::string &partten)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    return Win32Platform::findPaths(dir_path,partten);
#else
	std::vector<std::string> arr;
    findFiles(dir_path, partten, false, false, &arr);
	return arr;
#endif

}

std::string Util::GetNodeUesrStr(cocos2d::Node* _node){
    if (!_node)
    return "";
    Ref* t = _node->getUserObject();
    if(!t)
    return "";
    cocostudio::ObjectExtensionData* _object = static_cast<cocostudio::ObjectExtensionData*>(t);
    if(!_object)
    return "";
    return _object->getCustomProperty();
}



std::vector<std::string> fileArray;
void _loopFiles(const std::string &folderPath)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    Win32Platform::loopFiles(folderPath,fileArray);
#else
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(folderPath.c_str())) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", folderPath.c_str());
        return;
    }
    chdir(folderPath.c_str());
    while((entry = readdir(dp)) != NULL)
    {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode))
        {
            if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
            {
                continue;
            }
            _loopFiles(folderPath + "/" + entry->d_name);
        }
        else
        {
            std::string filename = entry->d_name;
            fileArray.push_back(folderPath + "/" + filename);
        }
    }
    chdir("..");
    closedir(dp);
#endif
}
std::vector<std::string> Util::loopFiles(const std::string &folderPath)
{
    fileArray.clear();
    _loopFiles(folderPath);
    return fileArray;
}

void Util::StrSplit(const std::string & src, const std::string & sep, std::vector<std::string> & vecRes)
{
    vecRes.clear();
    std::string s;
    for (std::string::const_iterator i = src.begin(); i != src.end(); i++)
    {
        if (sep.find(*i) != std::string::npos)
        {
            if (s.length()) vecRes.push_back(s);
            s = "";
        }
        else
        {
            s += *i;
        }
    }
    if (s.length()) vecRes.push_back(s);
}

bool Util::createFile(const std::string &filefullPath,const std::string &content)
{
    FILE *fp = fopen( Util::getRealFullpath(filefullPath).c_str() , "wb");
    if (fp)
    {
        fwrite(content.c_str(), 1,content.length(),fp);
        fclose(fp);
        return  true;
    }
    return false;
};

bool Util::isFileParentCreated(const std::string &fullpath)
{
    if (FileUtils::getInstance()->isDirectoryExist(fullpath))
    {return true;};
    size_t pos = fullpath.find_last_of("/");
    
    const std::string &dir_path = fullpath.substr(0, pos + 1);

    return FileUtils::getInstance()->createDirectory(dir_path);
}



//by sxp
void Util::addLabelKey(std::string key, std::string value){
    Label::addLabelKey(key, value);
}
//std::string Util::getLabelNewKey(std::string _str, std::string value){
//    return Label::getLabelNewKey(_str, value);
//}
void Util::clearLabelKey(){
    Label::clearLabelKey();
}







/***************           *************/
AudioEngineHelper * m_pInstance = nullptr;

AudioEngineHelper * AudioEngineHelper::getInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new AudioEngineHelper();
        m_pInstance->m_volume = 1.0f;
    }
    return m_pInstance;
}

void AudioEngineHelper::_audioEngineFinishCallBack(int audioId, const std::string &file_path)
{
    CCLOG("FinishCallBack ID: %d  filepath: %s",audioId,file_path.c_str());
    
}
void AudioEngineHelper::setFinishCallback(int audioID)
{
    auto helper = AudioEngineHelper::getInstance();
    // use std::bind to bind instance functions to callback;
    auto bindFuc = std::bind(&AudioEngineHelper::_audioEngineFinishCallBack, helper,std::placeholders::_1,std::placeholders::_2);
    
    cocos2d::experimental::AudioEngine::setFinishCallback(audioID, bindFuc);
};

void AudioEngineHelper::setVolumeAll(float volume)
{
    if (volume < 0.0f) {
        volume = 0.0f;
    }
    else if (volume > 1.0f){
        volume = 1.0f;
    }
    auto audioIDInfoMap = cocos2d::experimental::AudioEngine::_audioIDInfoMap;
    
    for (auto ite = audioIDInfoMap.begin();ite != audioIDInfoMap.end();ite++)
    {
        auto audioId = ite->first;
        AudioEngineHelper::setVolume(audioId, volume);
    }
}
int AudioEngineHelper::PlayEffectT(const char* _name){
    return experimental::AudioEngine::play2d(_name,false,AudioEngineHelper::getInstance()->m_volume);

}

void AudioEngineHelper::SetEffectVolume(float volume){
    AudioEngineHelper::getInstance()->m_volume = volume;
}

