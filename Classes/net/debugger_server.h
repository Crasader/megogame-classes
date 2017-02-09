//
//  debugger_server.h
//  HappyHero
//
//  Created by YUXIAOFEI on 14-7-30.
//
//

#ifndef __HappyHero__debugger_server__
#define __HappyHero__debugger_server__

#include <iostream>

#include <thread>
#include <vector>
#include <string>

#include "PackSocket.h"
#include "PacketBuff.h"

namespace Editor {

    /**
     *  {string}    file_name
     *  {int32}    size
     *  {raw byte}  content
     */
#define CMD_DEBUGGER_SC_SAVE_FILE   0
    /**
     *  no param
     */
#define CMD_DEBUGGER_SC_RESET       1
    
    /**
     * Server
     */
    class DebuggerServer
    {
    public:
        static DebuggerServer& GetInstance();
        
        void InitServer();
        void update(float dt_);

        void SendSaveFile(const std::string& file_name_);
        void SendReset();
    protected:
        DebuggerServer();
        
        CommonFnArgs* CreatePacket(uint32 pak_size_);
        
        static void ServerSocketThreadMain();
        static void ServerSendThreadMain();
    protected:
    };

    /**
     * Client
     */
    class DebuggerClient : public Socket
    {
    public:
        static DebuggerClient& GetInstance();
        
        void InitClient(const char* ip_);
        
        void SendHeartBeat();
        
        void update(float dt_);
    protected:
        DebuggerClient();
        
        void OnRead() override;
        
        void HandlePacket(CommonFnArgs* pak_);
        
        void HandleSaveFile(CommonFnArgs* pak_);
        void HandleReset(CommonFnArgs* pak_);
        
    protected:
        uint32			m_remainSize;
    };
}
#endif /* defined(__HappyHero__debugger_server__) */
