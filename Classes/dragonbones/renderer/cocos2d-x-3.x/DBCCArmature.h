#ifndef DBCC_ARMATURE_H
#define DBCC_ARMATURE_H


#include "dbccMacro.h"
#include "../../DragonBonesHeaders.h"
#include "DBCCSlot.h"
#include "cocos2d.h"

#if (DRAGON_BONES_ENABLE_LUA == 1)
#include "CCLuaValue.h"
#endif // DRAGON_BONES_ENABLE_LUA

NAME_SPACE_DRAGON_BONES_BEGIN


// add by howe begin
// for Future exchange
class DBCCSprite : public cocos2d::Sprite
{
public:
    DBCCSprite();
    
    virtual ~DBCCSprite();
    
    CREATE_FUNC(DBCCSprite);
    
    static DBCCSprite * createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame)
    {
        DBCCSprite *sprite = new (std::nothrow) DBCCSprite();
        if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
        {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
        return nullptr;
    }
    //     virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
    {
        if (!_texture || !isVisible())
        {
            return;
        }
        cocos2d::Sprite::draw(renderer, transform, flags);
    }
    
    void setSlotTexture(cocos2d::Texture2D * texture)
    {
        if (texture)
        {
            _unflippedOffsetPositionFromCenter.set(0, 0);

            cocos2d::Sprite::setTexture(texture);
            cocos2d::Rect rect;

            rect.size = texture->getContentSize();
            cocos2d::Sprite::setTextureRect(rect);
        }
    }
    
    unsigned int getScriptID()
    {
#if CC_ENABLE_SCRIPT_BINDING
        return this->_ID;
#endif
        return 0;
    }
    
    static int ref_count;
};

class DBCCArmatureNode;

class DBCCArmature : public Armature
{
public:
    virtual cocos2d::Node* getCCDisplay() const;
    virtual cocos2d::EventDispatcher* getCCEventDispatcher() const;
    
public:
    DBCCArmature(ArmatureData *armatureData, DBAnimation *animation, IEventDispatcher *eventDispatcher, cocos2d::Node *display);
    virtual ~DBCCArmature();
    virtual void dispose() override;
    
    virtual Rectangle getBoundingBox() override;
    virtual cocos2d::Rect getCCBoundingBox();
    
    virtual DBCCSlot* getCCSlot(const std::string &slotName) const;
    
    virtual DBCCArmatureNode* getArmatureNode() const;
    virtual void setArmatureNode(DBCCArmatureNode *armatureNode);
    
    // add by howe begin
    void setSlotVisible(const std::string &slotName,bool visible)
    {
        auto slot = getCCSlot(slotName);
        if (slot)
        {
            slot->setVisible(visible);
        }
    }
    bool getSlotVisible(const std::string &slotName)
    {
        auto slot = getCCSlot(slotName);
        if (slot)
        {
            return slot->getVisible();
        }
        return false;
    }
    cocos2d::Sprite * getCCSlotSprite(const std::string &slotName)
    {
        auto slot = getCCSlot(slotName);
        if (slot)
        {
            cocos2d::Node* spNode = slot->getCCDisplay();
            return dynamic_cast<cocos2d::Sprite*>(spNode);
        }
        return nullptr;
    }
    cocos2d::Vec2 getSlotGlobalPosition(const std::string &slotName)
    {
        auto slot = getCCSlot(slotName);
        if (slot)
        {
            return slot->getGlobalPosition();
        }
        return cocos2d::Vec2(0,0);
    }
    void setSlotDisplayTexture(const std::string &slotName,const std::string &filepath)
    {
        auto slotSprite = getCCSlotSprite(slotName);
        auto dbSprite = dynamic_cast<DBCCSprite*>(slotSprite);
        if (dbSprite)
        {
            auto texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(filepath);
            if (texture)
            {
                dbSprite->setSlotTexture(texture);
            }
        }
    }
    void setSlotDisplaySpriteFrame(const std::string &slotName,cocos2d::SpriteFrame * frame)
    {
        auto slotSprite = getCCSlotSprite(slotName);
        if (slotSprite && frame)
        {
            slotSprite->setSpriteFrame(frame);
        }
    }
    void changeSlotDisplay(const std::string &slotName,cocos2d::Node * display)
    {
        if (!display)
        {
            return;
        }
        auto slot = getCCSlot(slotName);
        if (slot)
        {
            slot->setDisplayImage(display);
        }
    }
    void playAnimation(const std::string &animationName,int times)
    {
        auto animation = getAnimation();
        if (animation->hasAnimation(animationName))
        {
            auto animationState = animation->gotoAndPlay(animationName);
            animationState->setPlayTimes(times);
        }
    }
    void stopAnimation(const std::string &animationName,int times)
    {
        auto animation = getAnimation();
        if (animation->hasAnimation(animationName))
        {
            animation->gotoAndStop(animationName,times);
            this->advanceTime(0);
        }
    }
    
    Frame *getFrameByFrameName(const std::string &timeLineName,const std::string &frameName)
    {
        const auto &animationDataList = this->_armatureData->animationDataList;
        
        for (auto animationData : animationDataList)
        {
            if (animationData->name.compare(timeLineName) == 0)
            {
                for (auto frame : animationData->frameList)
                {
                    if (frame->event.compare(frameName) == 0)
                    {
                        return frame;
                    }
                }
            }
        }
        return nullptr;
    }
    
    Frame * getFrameByFrameEvent(const std::string &frameEvent)
    {
        const auto &animationDataList = this->_armatureData->animationDataList;
        
        for (auto animationData : animationDataList)
        {
            for (auto frame : animationData->frameList)
            {
                if (frame->event.compare(frameEvent) == 0)
                {
                    return frame;
                }
            }
        }
        return nullptr;
    }
    
    int getFrameRate()
    {
        const auto &animationDataList = this->_armatureData->animationDataList;
        for (auto animationData : animationDataList)
        {
            return animationData->frameRate;
        }
        return 24;
    }
    
    void registerEvent(bool value)
    {
        isEventListerner = value;
    }
    
    int getAnimationDuration(const std::string &act_name)
    {
        for (auto animationData :_armatureData->animationDataList)
        {
            if (animationData->name.compare(act_name) == 0)
            {
                return animationData->duration;
            }
        }
        return 0;
    }
protected:
    virtual void _sendAllEventImmediately() override;
    
private:
    
    bool isEventListerner;

    // add by howe end

protected:
    virtual void sortSlotsByZOrder() override;
    
private:
    DBCCArmatureNode *_armatureNode;
#if (DRAGON_BONES_ENABLE_LUA == 1)
    int _frameEventHandler;
    int _animationEventHandler;
#endif // DRAGON_BONES_ENABLE_LUA
    DRAGON_BONES_DISALLOW_COPY_AND_ASSIGN(DBCCArmature);
};

NAME_SPACE_DRAGON_BONES_END
#endif  // DBCC_ARMATURE_H
