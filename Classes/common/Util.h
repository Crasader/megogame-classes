//
//  Util.h
//  MegoGame
//
//  Created by howe on 15/3/13.
//
//

#ifndef __MegoGame__Util__
#define __MegoGame__Util__

#include <stdio.h>
#include "string"
#include "vector"

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

#include "GameFileUtils.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocos2d::ui;

#define FORMAT_PARAM_END -1

class Util
{
public:
    
    static std::string getSavedPath()
    {
        return GameFileUtils::getClassInstance()->getSavedPath();
    }
    
    static std::vector<std::string> getAllTextureNames()
    {
        return Director::getInstance()->getTextureCache()->getAllTextureNames();
    }
    static const std::string &getRealFullpath(const std::string &filefullPath)
    {
        Util::isFileParentCreated(filefullPath);
        return filefullPath;
    }
    static std::vector<std::string> loopFiles(const std::string &dir_path);

    static void StrSplit(const std::string & src, const std::string & sep, std::vector<std::string> & vecRes);

    static bool createFile(const std::string& filefullPath,const std::string &content);
    
    static bool isFileParentCreated(const std::string &fullpath);
    
    static std::vector<std::string> findPaths(const std::string &dir_path,const std::string &partten);
    

    static std::string GetCcPositionTextureColor_noMVP_vert()
    {
        return std::string(cocos2d::ccPositionTextureColor_noMVP_vert);
    };
    
    static std::string GetCcPositionTextureColor_vert()
    {
        return std::string(cocos2d::ccPositionTextureColor_vert);
    };
    
    
    static std::string GetNodeUesrStr(cocos2d::Node* _node);
    
    
    //by sxp
    static void addLabelKey(std::string, std::string);
//    static std::string getLabelNewKey(std::string, std::string);
    static void clearLabelKey();
    
    static void closeKeyBoard(cocos2d::Node * editBox)
    {
        EditBox* dd = dynamic_cast<EditBox*>(editBox);
        if (dd)
        {
            dd->closeKeyboard();
        }
    }
};
/**
 * 
 *
 **/
class AudioEngineHelper : public experimental::AudioEngine
{
private:
    void _audioEngineFinishCallBack(int audioId,const std::string& file_path);
    static AudioEngineHelper * getInstance();
public:

    /**
     * Register a callback to be invoked when an audio instance has completed playing.
     *
     * @param audioID An audioID returned by the play2d function.
     * @param callback
     */
    static void setFinishCallback(int audioID);
    
    static bool lazyInit()
    {
        return experimental::AudioEngine::lazyInit();
    }
    
    /**
     * Release objects relating to AudioEngine.
     *
     * @warning It must be called before the application exit.
     */
    static void end()
    {
        experimental::AudioEngine::end();
    }
    
    /**
     * Play 2d sound.
     *
     * @param filePath The path of an audio file.
     * @param loop Whether audio instance loop or not.
     * @param volume Volume value (range from 0.0 to 1.0).
     * @param profile A profile for audio instance. When profile is not specified, default profile will be used.
     * @return An audio ID. It allows you to dynamically change the behavior of an audio instance on the fly.
     *
     * @see `AudioProfile`
     */
    static int play2d(const std::string& filePath, bool loop = false, float volume = 1.0f)
    {
        return experimental::AudioEngine::play2d(filePath,loop,volume);
    }
    
    static int PlayEffectT(const char* _name);
    
    float m_volume;
    
    static void SetEffectVolume(float volume);
    
    /**
     * Sets whether an audio instance loop or not.
     *
     * @param audioID An audioID returned by the play2d function.
     * @param loop Whether audio instance loop or not.
     */
    static void setLoop(int audioID, bool loop)
    {
        experimental::AudioEngine::setLoop(audioID,loop);
    }
    
    /**
     * Checks whether an audio instance is loop.
     *
     * @param audioID An audioID returned by the play2d function.
     * @return Whether or not an audio instance is loop.
     */
    static bool isLoop(int audioID)
    {
        return experimental::AudioEngine::isLoop(audioID);
    }
    
    /**
     * Sets volume for an audio instance.
     *
     * @param audioID An audioID returned by the play2d function.
     * @param volume Volume value (range from 0.0 to 1.0).
     */
    static void setVolume(int audioID, float volume)
    {
        experimental::AudioEngine::setVolume(audioID,volume);
    }
    
    /**
     * Gets the volume value of an audio instance.
     *
     * @param audioID An audioID returned by the play2d function.
     * @return Volume value (range from 0.0 to 1.0).
     */
    static float getVolume(int audioID)
    {
        return experimental::AudioEngine::getVolume(audioID);
    }

    
    /**
     * change all sound volume
     *
     */
    static void setVolumeAll(float volume);
    
    /**
     * Pause an audio instance.
     *
     * @param audioID An audioID returned by the play2d function.
     */
    static void pause(int audioID)
    {
        experimental::AudioEngine::pause(audioID);
    }

    
    /** Pause all playing audio instances. */
    static void pauseAll()
    {
        experimental::AudioEngine::pauseAll();
    }
    
    /**
     * Resume an audio instance.
     *
     * @param audioID An audioID returned by the play2d function.
     */
    static void resume(int audioID)
    {
        experimental::AudioEngine::resume(audioID);

    }
    
    /** Resume all suspended audio instances. */
    static void resumeAll()
    {
        experimental::AudioEngine::resumeAll();
    }
    
    /**
     * Stop an audio instance.
     *
     * @param audioID An audioID returned by the play2d function.
     */
    static void stop(int audioID)
    {
        experimental::AudioEngine::stop(audioID);
    }
    
    /** Stop all audio instances. */
    static void stopAll()
    {
        experimental::AudioEngine::stopAll();
    }
    
    /**
     * Sets the current playback position of an audio instance.
     *
     * @param audioID An audioID returned by the play2d function.
     * @return
     */
    static bool setCurrentTime(int audioID, float time)
    {
        return experimental::AudioEngine::setCurrentTime(audioID,time);
    }
    
    /**
     * Gets the current playback position of an audio instance.
     *
     * @param audioID An audioID returned by the play2d function.
     * @return The current playback position of an audio instance.
     */
    static float getCurrentTime(int audioID)
    {
        return experimental::AudioEngine::getCurrentTime(audioID);
    }
    
    /**
     * Gets the duration of an audio instance.
     *
     * @param audioID An audioID returned by the play2d function.
     * @return The duration of an audio instance.
     */
    static float getDuration(int audioID)
    {
        return experimental::AudioEngine::getDuration(audioID);
    }
    
    /**
     * Returns the state of an audio instance.
     *
     * @param audioID An audioID returned by the play2d function.
     * @return The status of an audio instance.
     */
    static cocos2d::experimental::AudioEngine::AudioState getState(int audioID)
    {
        return experimental::AudioEngine::getState(audioID);
    }

    /**
     * Sets the maximum number of simultaneous audio instance for AudioEngine.
     *
     * @param maxInstances The maximum number of simultaneous audio instance.
     */
    static bool setMaxAudioInstance(int maxInstances)
    {
        return experimental::AudioEngine::setMaxAudioInstance(maxInstances);
    }
    
    static int getMaxAudioInstance()
    {
        return experimental::AudioEngine::getMaxAudioInstance();
    }

    
    /**
     * Uncache the audio data from internal buffer.
     * AudioEngine cache audio data on ios,mac, and win32 platform.
     *
     * @warning This can lead to stop related audio first.
     * @param filePath Audio file path.
     */
    static void uncache(const std::string& filePath)
    {
        experimental::AudioEngine::uncache(filePath);
    }
    
    /**
     * Uncache all audio data from internal buffer.
     *
     * @warning All audio will be stopped first.
     */
    static void uncacheAll()
    {
        experimental::AudioEngine::stopAll();
        experimental::AudioEngine::uncacheAll();
    }
};
#endif /* defined(__MegoGame__Util__) */
