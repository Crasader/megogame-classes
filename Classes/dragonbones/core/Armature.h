﻿#ifndef CORE_ARMATURE_H
#define CORE_ARMATURE_H

#include "../DragonBones.h"
#include "../objects/ArmatureData.h"
#include "../animation/IAnimatable.h"
#include "../animation/Animation.h"
#include "../events/IEventDispatcher.h"
#include "Slot.h"
#include "../geoms/Rectangle.h"
#include <functional>
NAME_SPACE_DRAGON_BONES_BEGIN

typedef std::function<void(EventData* eventData)> DBEventCallListener;

class Object;
class Bone;
class Slot;
class DBAnimation;
class AnimationState;

class Armature : public IAnimatable
{
    friend class Object;
    friend class Bone;
    friend class Slot;
    
    friend class DBAnimation;
    friend class AnimationState;
    // add by howe begin
public:
    void setEventCallBack(const DBEventCallListener&listener)
    {
        _listener = listener;
    }
protected:
    virtual void _sendAllEventImmediately();
    
protected:
    DBEventCallListener _listener;
    // add by howe end
    
public:
    static IEventDispatcher *soundEventDispatcher;
    
private:
    static bool sortBone(const std::pair<int, Bone*> &a, const std::pair<int, Bone*> &b);
    
public:
    std::string name;
    
    void *userData;
    
protected:
    bool _needUpdate;
    bool _slotsZOrderChanged;
    bool _delayDispose;
    bool _lockDispose;
    bool _isInheritAnimation;
    
    std::vector<Bone*> _boneList;
    std::vector<Slot*> _slotList;
    std::vector<EventData*> _eventDataList;
    
    ArmatureData *_armatureData;
    DBAnimation *_animation;
    IEventDispatcher *_eventDispatcher;
    void *_display;
    
public:
    virtual Rectangle getBoundingBox() = 0;
    
    virtual const std::vector<Bone*>& getBones() const;
    virtual const std::vector<Slot*>& getSlots() const;
    
    virtual const ArmatureData* getArmatureData() const;
    virtual DBAnimation* getAnimation() const;
    virtual void* getDisplay() const;
    virtual IEventDispatcher* getEventDispatcher() const;
    
public:
    Armature(ArmatureData *armatureData, DBAnimation *animation, IEventDispatcher *eventDispatcher, void *display);
    virtual ~Armature();
    virtual void dispose();
    
public:
    virtual bool isInheritAnimation() const { return _isInheritAnimation; };
    virtual void setInheritAnimation(bool b) { _isInheritAnimation = b; };
    virtual Bone* getBone(const std::string &boneName) const;
    virtual Bone* getBoneByDisplay(const void *display) const;
    virtual void addBone(Bone *bone);
    virtual void addBone(Bone *bone, const std::string &parentBoneName);
    virtual void removeBone(Bone *bone);
    virtual Bone* removeBone(const std::string &boneName);
    
    virtual Slot* getSlot(const std::string &slotName) const;
    virtual Slot* getSlotByDisplay(const void *display) const;
    virtual void addSlot(Slot *slot, const std::string &parentBoneName);
    virtual void removeSlot(Slot *slot);
    virtual Slot* removeSlot(const std::string &slotName);
    virtual void replaceSlot(const std::string &boneName, const std::string &oldSlotName, Slot* newSlot);
    virtual void sortSlotsByZOrder();
    
    virtual void invalidUpdate();
    virtual void invalidUpdate(const std::string &boneName);
    
    virtual void advanceTime(float passedTime) override;
    
protected:
    virtual void addObject(Object *object);
    virtual void removeObject(Object *object);
    
    virtual void sortBones();
    static bool sortSlot(const Slot *a, const Slot *b);
    
    virtual void arriveAtFrame(Frame *frame, AnimationState *animationState, bool isCross);
private:
    DRAGON_BONES_DISALLOW_COPY_AND_ASSIGN(Armature);
};
NAME_SPACE_DRAGON_BONES_END
#endif  // CORE_ARMATURE_H
