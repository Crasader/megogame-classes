#ifndef EVENTS_EVENT_DATA_H
#define EVENTS_EVENT_DATA_H

#include "../DragonBones.h"
#include <stdint.h>
NAME_SPACE_DRAGON_BONES_BEGIN

class Armature;
class Bone;
class AnimationState;
class Frame;

class EventData
{
public:
    static const std::string Z_ORDER_UPDATED;
    static const std::string ANIMATION_FRAME_EVENT;
    static const std::string BONE_FRAME_EVENT;
    static const std::string SOUND;
    static const std::string FADE_IN;
    static const std::string FADE_OUT;
    static const std::string START;
    static const std::string COMPLETE;
    static const std::string LOOP_COMPLETE;
    static const std::string FADE_IN_COMPLETE;
    static const std::string FADE_OUT_COMPLETE;
    
    static const std::string _ERROR;
    
    enum class EventType
    {
        Z_ORDER_UPDATED,
        ANIMATION_FRAME_EVENT,
        BONE_FRAME_EVENT,
        SOUND,
        FADE_IN, FADE_OUT, START, COMPLETE, LOOP_COMPLETE, FADE_IN_COMPLETE, FADE_OUT_COMPLETE,
        _ERROR
    };
    
    static const std::string& typeToString(EventType eventType);

    static EventData* borrowObject(EventType eventType);
    static void returnObject(EventData *eventData);
    static void clearObjects();

private:
    static std::vector<EventData*> _pool;
    
public:
    std::string frameLabel;
    std::string sound;
    
    Armature *armature;
    Bone *bone;
    AnimationState *animationState;
    Frame *frame;
    unsigned int currentEventTargetId;
private:
    EventType _type;
    
public:
    EventType getType() const;
    
    const std::string& getStringType() const;
    
    const std::string& getFrameLabel(){return frameLabel;};
    
    const std::string& getSound(){return sound;};

    Frame * getFrame(){return frame;};
    
    Bone * getBone(){return bone;};
    
//    AnimationState * getAnimationState(){return animationState;};
    
    Armature * getArmature(){return armature;};
    
    // add by howe begin
public:
    const std::string &getAnimationName();
    
    uint32_t getCurrentEventTargetId()
    {
        return currentEventTargetId;
    }
    // add by howe end
public:
    
    EventData();
#ifndef SKIP_BY_JS_AUTO_BINDING

    EventData(EventType type, Armature *armatureTarget);
    virtual ~EventData();
    void clear();
    void copy(const EventData &copyData);
#endif

private:
    DRAGON_BONES_DISALLOW_COPY_AND_ASSIGN(EventData);
};
NAME_SPACE_DRAGON_BONES_END
#endif  // EVENTS_EVENT_DATA_H
