//
//  Win32Platform.h
//  MegoGame
//
//  Created by howe on 15/4/14.
//
//

#ifndef __MegoGame__Win32Platform__
#define __MegoGame__Win32Platform__
#include <stdio.h>
#include <string>
#include <vector>
#include "../IPlatform.h"

std::string getIPAddress();

class Win32Platform : public IPlatform
{
public:
    virtual ~Win32Platform();
    
    virtual std::string getAppVersion() const;

    //get the mac address of device
    virtual std::string getMacAddress() const;
    
    //wiki http://zh.wikipedia.org/wiki/IOS%E8%AE%BE%E5%A4%87%E5%88%97%E8%A1%A8
    virtual std::string getDeviceType() const;
    virtual std::string getDeviceSystem() const;
    virtual std::string  getDeviceMemory() const;
    virtual NetworkType getNetworkType() const;
    virtual std::string getDeviceUid() const;
    virtual std::string getDeviceUidType() const;
    virtual std::string getDeviceName() const;
    
    virtual std::string getPlatformId() const;
    
    
    virtual void setTextInPasteboard(std::string) const;
    
    // This follow api is only use for win
    static std::string getDesktopDirectory();
    
    static std::vector<std::string> findPaths(const std::string &dir_path,const std::string &partten);
    
	static void loopFiles(const std::string &folderPath, std::vector<std::string> &arr);

    
};
#endif /* defined(__MegoGame__Win32Platform__) */
