//
//  GameFileUtils.cpp
//  MegoGame
//
//  Created by howe on 15/7/13.
//

//  JUST for Android
//

#include "GameFileUtils.h"

#include "base/ZipUtils.h" // obb use ZipUtil parseZipData
#include "XXTeaUtil.h"

#include "../platform/PlatformManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOSUtil.h"
#endif

using namespace std;
using namespace cocos2d;

#define LOCAL_GAME_VERSION_FILE     "__gameVersion.config";

FileUtils *s_DefaultFileUtils = nullptr;
GameFileUtils * s_GameFileUtils = nullptr;

static ZipFile *s_obbZipFile = nullptr;
string s_obbFileDirectory = "";

bool hasSetFileUtils = false;

void SET_FILEUTILS_DELEGATE()
{
//    if (hasSetFileUtils)
//    {
//        GameFileUtils::getClassInstance()->dispose();
//        return;
//    }
//    hasSetFileUtils = true;
//    return;
	FileUtils::setDelegate(GameFileUtils::getClassInstance());
    GameFileUtils::getClassInstance()->purgeCachedEntries();
}



GameFileUtils * GameFileUtils::getClassInstance()
{
	if (s_GameFileUtils == nullptr)
	{
		s_GameFileUtils = new GameFileUtils();
		s_GameFileUtils->init();
        s_GameFileUtils->initRes();
	}
	return s_GameFileUtils;
}
GameFileUtils::GameFileUtils()
{

}

GameFileUtils::~GameFileUtils()
{
    if (s_obbZipFile)
    {
        delete s_obbZipFile;
        s_obbZipFile = nullptr;
    }
    s_GameFileUtils = nullptr;
}
bool GameFileUtils::init()
{
    s_DefaultFileUtils = FileUtils::getInstance(); // Save the cocos fileUtils
    FileUtils::s_sharedFileUtils = nullptr;
    
    s_obbFileDirectory = "sdcard/Android/obb/";
//    string obbFullPath = "";
//    if (s_obbZipFile)
//    {
//        delete s_obbZipFile;
//    }
//    s_obbZipFile = new ZipFile(obbFullPath.c_str());

    
    return GAME_FILEUTILS_SUPER_CLASS::init();
}

void GameFileUtils::initRes()
{
    std::string version = PlatformManager::getAppVersion();
    std::string localGameVPath = FileUtils::getInstance()->getWritablePath() + LOCAL_GAME_VERSION_FILE;
    std::string localGameVersion = FileUtils::getInstance()->getStringFromFile(localGameVPath);
    if (version != localGameVersion)
    {
        CCLOG("App is first lanuch。 localGameVersion %s , delete cache resource",localGameVersion.c_str());
        FileUtils::getInstance()->removeDirectory( this->getDownLoadSavedPath() );
    }
}

std::string GameFileUtils::getSavedPath()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return IOSUtil::getLibraryCacheDirectory();
#endif
    return FileUtils::getInstance()->getWritablePath();
}

std::string GameFileUtils::getDownLoadSavedPath()
{
    std::string savedPath = this->getSavedPath();
    return savedPath + "gameAssets/";
}

Data GameFileUtils::getFData(const std::string& filename, bool forString)
{
    return GAME_FILEUTILS_SUPER_CLASS::getDataFromFile(filename);
}

Data GameFileUtils::getOBBFileData(const std::string& filename) const
{
    Data _data;
    if (s_obbZipFile)
    {
        // 变成 相对路径
        ssize_t pSize;
        unsigned char* pData = s_obbZipFile->getFileData(filename.c_str(), &pSize);
        _data.fastSet(pData, pSize);
        XXTeaUtil::decryptBuffer(_data, XXTEA_KEY);
        XXTeaUtil::unCompressLzmaBuffer(_data);
    }
    return _data;
}
ValueMap GameFileUtils::getValueMapFromFile(const std::string& filename)
{
    const std::string &fullPath = fullPathForFilename(filename);
    Data _data = this->getDataFromFile(fullPath);
    return GAME_FILEUTILS_SUPER_CLASS::getValueMapFromData( (const char*)_data.getBytes(), (int)_data.getSize());
}
ValueMap GameFileUtils::getValueMapFromData(const char* filedata, int filesize)
{
    return GAME_FILEUTILS_SUPER_CLASS::getValueMapFromData( filedata , filesize);
}

std::string GameFileUtils::getStringFromFile(const std::string& filename)
{
    Data _data = this->getDataFromFile(filename);
    if (!_data.isNull())
    {
        auto size = _data.getSize();
        auto buffer = _data.getBytes();
        
        char* strBuffer = ( char*) malloc( size + 1);
        memset(strBuffer, 0, size+1);
        
        for (size_t i = 0; i < size; i++)
        {
            strBuffer[i] = buffer[i];
        }
        strBuffer[size] = '\0';
        
        _data.clear();
        std::string ret(strBuffer);
        free(strBuffer);
        return ret;
    }
    return "";
}
Data GameFileUtils::getDataFromFile(const std::string& filename)
{
    auto path = FileUtils::getInstance()->fullPathForFilename(filename);
    auto ite = m_csbDataMap.find(path);
    if (ite != m_csbDataMap.end())
    {
        Data _data;
        _data.copy(ite->second.getBytes(), ite->second.getSize());
        return _data;
    }
    Data _data = GAME_FILEUTILS_SUPER_CLASS::getDataFromFile(path);
    if (_data.isNull())
    {
        // custom code   read data from zipfile
//        _data = getOBBFileData(filename);
    }
    if (_data.isNull())
    {
        return _data;
    }
    XXTeaUtil::decryptBuffer(_data, XXTEA_KEY); // decry buffer
    XXTeaUtil::unCompressLzmaBuffer(_data);     // uncompress file;
    
    if ( filename.find(".csb") != std::string::npos)
    {
        m_csbDataMap[path] = _data;
    }
    
    return _data;
}

bool GameFileUtils::isAbsolutePath(const std::string& strPath) const
{
    bool ret = GAME_FILEUTILS_SUPER_CLASS::isAbsolutePath(strPath);
    
    if (!ret && !s_obbFileDirectory.empty())
    {
        if ( strPath.find(s_obbFileDirectory) == 0)
        {
            return true;
        }
    }
    return ret;
}

bool GameFileUtils::isFileExist(const std::string& filename) const
{
    bool ret = GAME_FILEUTILS_SUPER_CLASS::isFileExist(filename);
    if (!ret)
    {
        if (s_obbZipFile)
        {
            std::string strPath = filename;
            size_t pos = strPath.find(s_obbFileDirectory);
            if ( pos != std::string::npos)
            {
                strPath = strPath.substr(s_obbFileDirectory.length(),strPath.length() - pos);
            }
            if (s_obbZipFile->fileExists(strPath))
            {
                ret = true;
            }
        }
    }
    return ret;
}

unsigned char* GameFileUtils::getFileData(const std::string& filename, const char* mode, ssize_t * size)
{
    Data _data(this->getDataFromFile(filename));
    if (size)
    {
        *size = _data.getSize();
    }
    auto buffer = _data.getBytes();
    unsigned char* pbuffer = (unsigned char*)malloc(_data.getSize());
    for (size_t i = 0; i < _data.getSize(); i++)
    {
        pbuffer[i] = buffer[i];
    }
    return pbuffer;
}


void GameFileUtils::purgeCachedEntries()
{
    GAME_FILEUTILS_SUPER_CLASS::purgeCachedEntries();
    m_csbDataMap.clear();
}











