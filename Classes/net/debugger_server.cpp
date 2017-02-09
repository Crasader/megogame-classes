//
//  debugger_server.cpp
//  HappyHero
//
//  Created by YUXIAOFEI on 14-7-30.
//
//

#include "debugger_server.h"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <io.h>
#include <WS2tcpip.h>
#else
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#endif

#include "GameSession.h"

#include "AppDelegate.h"



namespace Editor {
    
#define DEBUGGER_SERVER_PORT    5096
    
#define MAX_PATH_LENGTH	256

    DebuggerServer& DebuggerServer::GetInstance()
    {
        static DebuggerServer inst;
        return inst;
    }
    
    DebuggerServer::DebuggerServer()
    {}
    
    void DebuggerServer::InitServer()
    {
        // start bg thread
        auto t = std::thread(&DebuggerServer::ServerSocketThreadMain);
        t.detach();
        
        auto send_t = std::thread(&DebuggerServer::ServerSendThreadMain);
        send_t.detach();
        
        cocos2d::Director::getInstance()->getScheduler()->scheduleUpdate(this, Scheduler::PRIORITY_SYSTEM, false);
    }

    static std::vector<CommonFnArgs*> outData;
    static std::vector<CommonFnArgs*> g_queue;
    static std::mutex g_qMutex;
    static std::mutex g_rwMutex;
    static int clientSocket = INVALID_SOCKET;

    CommonFnArgs* DebuggerServer::CreatePacket(uint32 pak_size_)
    {
        char* buf = new char[pak_size_];
        CommonFnArgs* pak = new CommonFnArgs(buf, 0);
        return pak;
    }
    
    void DebuggerServer::SendSaveFile(const std::string &file_name_)
    {
        cocos2d::Data data = cocos2d::FileUtils::getInstance()->getDataFromFile(file_name_);
        CommonFnArgs* pak = CreatePacket(data.getSize() + 100);
        pak->WriteWord(CMD_DEBUGGER_SC_SAVE_FILE);
        pak->WriteCString(file_name_);
        pak->WriteInt(data.getSize());
        pak->WriteStream((const char*)data.getBytes(), data.getSize());
        
        g_qMutex.lock();
        outData.push_back(pak);
        g_qMutex.unlock();
    }
    
    void DebuggerServer::SendReset()
    {
        CommonFnArgs* pak = CreatePacket(10);
        pak->WriteWord(CMD_DEBUGGER_SC_RESET);
        
        g_qMutex.lock();
        outData.push_back(pak);
        g_qMutex.unlock();
    }
    
    void DebuggerServer::update(float dt_)
    {
        g_qMutex.lock();
        size_t size = g_queue.size();
        g_qMutex.unlock();
        
        while (size > 0)
        {
            g_qMutex.lock();
            auto first = g_queue.begin();
            CommonFnArgs* pak = *first;
            g_queue.erase(first);
            size = g_queue.size();
            g_qMutex.unlock();

            // process command
            std::string val = pak->ReadCString();
            cocos2d::MessageBox("message", val.c_str());
            
            delete pak;
        }
    }
    

    void _clientSocketWriteAndClearString(CommonFnArgs* pak_)
    {
        if(clientSocket != INVALID_SOCKET)
        {
            /**
             *  Format
             *  {uint32} total_size
             *  {binary} content
             */
            uint32 length = pak_->GetSize() + sizeof(uint32);
            ::send(clientSocket, (const char*)&length, sizeof(uint32), 0);
            ::send(clientSocket, pak_->GetData(), pak_->GetSize(), 0);
        }
        
        delete [] pak_->GetData();
        delete pak_;
    }
    
    void processInput(CommonFnArgs* pak_) {
        std::lock_guard<std::mutex> lk(g_qMutex);
        g_queue.push_back(pak_);
    }
    
    void clearBuffers() {
        std::lock_guard<std::mutex> lk(g_rwMutex);

        while(outData.size() > 0) {
            _clientSocketWriteAndClearString(*outData.begin());
            outData.erase(outData.begin());
        }
    }

	void SleepThread(int milli_seconds_)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		Sleep(milli_seconds_);
#else
		sleep(milli_seconds_);
#endif
	}

    void DebuggerServer::ServerSendThreadMain()
    {
        while (1) {
            clearBuffers();

			SleepThread(1);
        }
    }
    
    void DebuggerServer::ServerSocketThreadMain()
    {
        // start a server, accept the connection and keep reading data from it
        struct addrinfo hints, *result = nullptr, *rp = nullptr;
        int s = 0;
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_INET;       // IPv4
        hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
        hints.ai_flags = AI_PASSIVE;     // fill in my IP for me
        
        std::stringstream portstr;
        portstr << DEBUGGER_SERVER_PORT;
        
        int err = 0;
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        WSADATA wsaData;
        err = WSAStartup(MAKEWORD(2, 2),&wsaData);
#endif
        auto cc_closesocket = [](int fd)
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
            closesocket(fd);
#else
            close(fd);
#endif
        };

        if ((err = getaddrinfo(NULL, portstr.str().c_str(), &hints, &result)) != 0) {
            CCLOGERROR("getaddrinfo error : %s\n", gai_strerror(err));
        }
        
        for (rp = result; rp != NULL; rp = rp->ai_next) {
            if ((s = socket(rp->ai_family, rp->ai_socktype, 0)) < 0) {
                continue;
            }
            int optval = 1;
            if ((setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval))) < 0) {
                cc_closesocket(s);
                CCLOGERROR("debug server : error setting socket option SO_REUSEADDR");
                return;
            }
            
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            if ((setsockopt(s, SOL_SOCKET, SO_NOSIGPIPE, &optval, sizeof(optval))) < 0) {
                close(s);
                CCLOGERROR("debug server : error setting socket option SO_NOSIGPIPE");
                return;
            }
#endif //(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            
            struct timeval tv;
            
            tv.tv_sec = 1;  /* 1 Secs Timeout */
            tv.tv_usec = 0;  // Not init'ing this can cause strange errors
            
            setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
            
            if ((::bind(s, rp->ai_addr, rp->ai_addrlen)) == 0) {
                break;
            }
            cc_closesocket(s);
            s = -1;
        }
        if (s < 0 || rp == NULL) {
            CCLOGERROR("debug server : error creating/binding socket");
            return;
        }
        
        freeaddrinfo(result);
        
        listen(s, 1);
        
        while (true) {
            clientSocket = accept(s, NULL, NULL);
            
            if (clientSocket < 0)
            {
                CCLOGERROR("debug server : error on accept");
                return;
            }
            else
            {
                // alert
                cocos2d::MessageBox("alert", "client connected");
                
                // process any input, send any output
                clearBuffers();
                
                int buf_size = 1024 * 1024 * 4;
                char* buf = new char[buf_size];
                buf[0] = 0;
                int readBytes = 0;

                while ((readBytes = ::recv(clientSocket, buf, buf_size, 0)) > 0)
                {
                    // no other thread is using this
                    CommonFnArgs* pak = new CommonFnArgs(buf, readBytes);
                    processInput(pak);

                    // process any input, send any output
                    clearBuffers();
                } // while(read)
                
                delete[] buf;
                cc_closesocket(clientSocket);
                clientSocket = INVALID_SOCKET;
            }
        } // while(true)
    }
    
    /**
     * Client
     */
    DebuggerClient& DebuggerClient::GetInstance()
    {
        static DebuggerClient inst;
        return inst;
    }
    
    DebuggerClient::DebuggerClient()
    : Socket(INVALID_SOCKET, 1024 * 1024, 1024 * 1024)
    , m_remainSize(0)
    {
        
    }
    
    void DebuggerClient::InitClient(const char* ip_)
    {
        ConnectTo(ip_, DEBUGGER_SERVER_PORT);
        
        while (!IsConnected()) {
            SleepThread(1);
            CheckConnectingFinish(0);
        }

        cocos2d::Director::getInstance()->getScheduler()->scheduleUpdate(this, Scheduler::PRIORITY_SYSTEM, false);
    }
    
    void DebuggerClient::update(float dt_)
    {
        BurstSend();
        BurstRecv();
    }
    
    void DebuggerClient::SendHeartBeat()
    {
        if(!IsConnected()) return;
        
        CommonFnArgs pak;
        pak.WriteCString("heart beat");
        SendData(pak.GetData(), pak.GetSize());
    }
    
    void DebuggerClient::HandleReset(CommonFnArgs *pak_)
    {
        // add writable path to search path
        auto pathes = cocos2d::CCFileUtils::getInstance()->getSearchPaths();
        std::string write_path = cocos2d::CCFileUtils::getInstance()->getWritablePath();
        bool add = true;
        for (auto itor = pathes.begin(); itor != pathes.end(); ++itor) {
            if (write_path == *itor) {
                add = false;
                break;
            }
        }
        if(add)
        {
            pathes.insert(pathes.begin(), write_path);
            cocos2d::CCFileUtils::getInstance()->setSearchPaths(pathes);
        }
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("reset_game_script");
//        AppDelegate *delegate = dynamic_cast<AppDelegate*>( Application::getInstance());
//        g_app_delegate->ResetScriptEngine();
    }
    
    bool CreateDirOfFile( const char* path )
    {
        char dir[MAX_PATH_LENGTH];
        size_t len = strlen( path );
        memcpy( dir, path, len );
        
        bool valid = false;
        
        for ( int i = len - 1; i >= 0; i-- )
        {
            if ( dir[i] == '/' || dir[i] == '\\' )
            {
                dir[i] 	= '\0';
                valid 	= true;
                break;
            }
        }
        
        if ( !valid )
        {
            char bufferError[128] = {0};
            snprintf(bufferError , 128 ,"Create Direction Error [%s]", path );
            return false;
        }
        
//        if ( Platform::DirExist( dir ) == -1 )
//        {
//            if ( !CreateDirOfFile( dir ) ) return false;
//            Platform::DirCreate( dir );
//        }
        
        return true;
    }

    void DebuggerClient::HandleSaveFile(CommonFnArgs *pak_)
    {
        std::string file_path = pak_->ReadCString();
        int size = pak_->ReadInt();
        
        char* buf = new char[size];
        pak_->ReadStream(buf, size);
     
        std::string final_path = cocos2d::FileUtils::getInstance()->getWritablePath() + file_path;
        CreateDirOfFile(final_path.c_str());
        
        FILE* fp = fopen(final_path.c_str(), "wb");
        fwrite(buf, size, 1, fp);
        fclose(fp);
        
        delete[] buf;
    }
    
    void DebuggerClient::OnRead()
    {
        while (1)
        {
            // check for a complete packet
            if ( 0 == m_remainSize )
            {
                if ( m_recvBuffer.GetUsedSize() < sizeof(uint32) )
                {
                    return;
                }
                
                m_recvBuffer.Read( &m_remainSize, sizeof(uint32) );
            }
            
            uint32 content_size = m_remainSize - sizeof(uint32);
            if ( m_recvBuffer.GetUsedSize() < content_size )
            {
                return;
            }
            
            // read a packet
            char* buf = new char[content_size];
            CommonFnArgs* pak = new CommonFnArgs(buf, content_size) ;
            m_recvBuffer.Read( pak->GetData(), pak->GetSize() );
            m_remainSize = 0;
            
            HandlePacket(pak);
        }
    }
    
    void DebuggerClient::HandlePacket(CommonFnArgs* pak_)
    {
        uint32 cmd = pak_->ReadWord();
        if(cmd == CMD_DEBUGGER_SC_RESET)
        {
            HandleReset(pak_);
        }
        else if(cmd == CMD_DEBUGGER_SC_SAVE_FILE)
        {
            HandleSaveFile(pak_);
        }
    }
}