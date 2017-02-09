//
//  Win32Platform.cpp
//  MegoGame
//
//  Created by howe on 15/4/14.
//
//

#include "Win32Platform.h"
#include "cocos2d.h"

#include <io.h>
#include <ShlObj.h>

using namespace std;


char * wch2chr(LPCTSTR lpString)
{
    UINT len = wcslen(lpString) * 2;
    char *buf = (char *)malloc(len);
    UINT i = wcstombs(buf, lpString, len);
    return buf;
}
wstring getComputerName()
{
    DWORD size=0;
    wstring wstr;
    GetComputerName(NULL,&size);  //µ√µΩµÁƒ‘√˚≥∆≥§∂»
    wchar_t *name=new wchar_t[size];
    if(GetComputerName(name,&size))
    {
        wstr=name;
    }
    delete [] name;
    return wstr;
}
wstring getUserName()
{
    DWORD size=0;
    wstring wstr;
    GetUserName(NULL,&size);
    wchar_t *name=new wchar_t[size];
    if(GetUserName(name,&size))
    {
        wstr=name;
    }
    delete [] name;
    return wstr;
}
std::string WStringToString(const std::wstring &wstr)
  {
      std::string str(wstr.length(), ' ');
      std::copy(wstr.begin(), wstr.end(), str.begin());
      return str; 
}
std::string getIPAddress()
{
    return "";
}

Win32Platform::~Win32Platform() {
    
};

std::string Win32Platform::getAppVersion() const
{
    return "1.2.0";
}
//get the mac address of device
std::string Win32Platform::getMacAddress() const{
    return "0.0.0.0";
}

//wiki http://zh.wikipedia.org/wiki/IOS%E8%AE%BE%E5%A4%87%E5%88%97%E8%A1%A8
std::string Win32Platform::getDeviceType() const{

    return "pc";
}
std::string Win32Platform::getDeviceSystem() const{

    return "windows";
}

std::string  Win32Platform::getDeviceMemory() const{
    //    //get all memory
    return "1024";
}

NetworkType Win32Platform::getNetworkType() const{

    return NET_WIFI;
}

//UID
std::string Win32Platform::getDeviceUid() const{
	auto computerName = WStringToString(getComputerName());
	CCLOG("computerName: %s",computerName.c_str());
	return computerName;
}
//UID
std::string Win32Platform::getDeviceUidType() const{

    auto userName = WStringToString(getUserName());
	CCLOG("userName: %s",userName.c_str());
	return userName;
}
//
std::string Win32Platform::getDeviceName() const{
    return "windows";
}

std::string Win32Platform::getPlatformId() const
{
    return "1";
}

void Win32Platform::setTextInPasteboard(std::string text) const
{
	//open
	OpenClipboard(NULL);

	//clear
	EmptyClipboard();
	const char * tp_char = text.c_str();

	int lenght = text.length() +1;

	//
	HGLOBAL hgl = GlobalAlloc(GMEM_MOVEABLE, lenght);
	//lock 
	LPWSTR lpstrcpy = (LPWSTR) GlobalLock(hgl);

	memcpy(lpstrcpy, tp_char,  lenght);

	GlobalUnlock(hgl);
	//set board type is text
	SetClipboardData(CF_TEXT, lpstrcpy);
	
	//close
	CloseClipboard();
}




std::string Win32Platform::getDesktopDirectory()
{
    TCHAR path[255];
    SHGetSpecialFolderPath(0, path, CSIDL_DESKTOPDIRECTORY, 0);
    std::string destopPath(wch2chr(path));
    destopPath.append("/");
    return destopPath;
}

std::vector<std::string> Win32Platform::findPaths(const std::string &dir_path,const std::string &partten)
{
    std::vector<std::string> arr;
    _finddata_t FileInfo;
    std::string strfind = dir_path + "\\" + partten;
    long Handle = _findfirst(strfind.c_str(), &FileInfo);
    
    if (Handle != -1L)
    {
        do{
            if (FileInfo.attrib & _A_SUBDIR)
            {
            }
            else
            {
                std::string filename = (dir_path + "\\" + FileInfo.name);
                arr.push_back(FileInfo.name);
            }
        }while (_findnext(Handle, &FileInfo) == 0);
        _findclose(Handle);
    }
    return arr;
}


void Win32Platform::loopFiles(const std::string &folderPath,std::vector<std::string> &fileArray)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    _finddata_t FileInfo;
    std::string strfind = folderPath + "/*";
    long Handle = _findfirst(strfind.c_str(), &FileInfo);
    if (Handle == -1L)
    {
        std::string errorlog = "Canot open dir!" + folderPath;
        cocos2d::MessageBox(errorlog.c_str(), "Error");
        return;
    }
    do{
        if (FileInfo.attrib & _A_SUBDIR)
        {
            if( (strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0))
            {
                std::string newPath = folderPath + "/" + FileInfo.name;
                Win32Platform::loopFiles(newPath,fileArray);
            }
        }
        else
        {
            std::string filename = (folderPath + "/" + FileInfo.name);
            fileArray.push_back(filename);
        }
    }while (_findnext(Handle, &FileInfo) == 0);
    _findclose(Handle);
#endif
}