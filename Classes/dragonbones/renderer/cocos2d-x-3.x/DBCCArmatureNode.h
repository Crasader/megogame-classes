#ifndef DBCC_ARMATURE_NODE_H
#define DBCC_ARMATURE_NODE_H

#include "dbccMacro.h"
#include "../../DragonBonesHeaders.h"
#include "cocos2d.h"
#include "DBCCSlot.h"
#include "DBCCArmature.h"

#if (DRAGON_BONES_ENABLE_LUA == 1)
#include "CCLuaValue.h"
#endif // DRAGON_BONES_ENABLE_LUA



NAME_SPACE_DRAGON_BONES_BEGIN

class DBCCArmatureNode : public cocos2d::Node, public IAnimatable
{
public:
#ifndef SKIP_BY_JS_AUTO_BINDING
    virtual DBCCSlot* getCCSlot(const std::string &slotName) const { return _armature->getCCSlot(slotName); };
	virtual cocos2d::Node* getCCDisplay() const { return _armature->getCCDisplay(); };
	virtual cocos2d::EventDispatcher* getCCEventDispatcher() const { return _armature->getCCEventDispatcher(); };
#endif

	virtual cocos2d::Rect getBoundingBox() const override;
    virtual cocos2d::Rect getInnerBoundingBox() const;

public:
    // create DBCCArmatureNode without WorldClock
    static DBCCArmatureNode* create(DBCCArmature *armature);
    /**
     * create DDCCArmatureNode with WorldClock
     * @param armature
     * @param clock if null, use WorldClock::getInstance()
     * @return 
     */
    static DBCCArmatureNode* createWithWorldClock(DBCCArmature *armature, WorldClock *clock);
    virtual bool initWithDBCCArmature(DBCCArmature *armature, WorldClock *clock);
    
    DBCCArmatureNode();
    virtual ~DBCCArmatureNode();

    virtual void onExit() override;
    virtual void onEnter() override;
#ifndef SKIP_BY_JS_AUTO_BINDING

	DBCCArmature* getArmature() const { return _armature; };
	DBAnimation* getAnimation() const { return _armature->getAnimation(); };

	virtual void update(float dt) override;
    virtual void advanceTime(float dt) override;
#endif

// add by howe begin
    
    void playOpacityAnimation(bool enabled)
    {
        canSetOpacity = enabled;
    }
    bool getIsOpactityAnimation()
    {
        return canSetOpacity;
    }
    
    void pauseAnimation(bool isPause)
    {
        animationPause = isPause;
    }
    
    virtual void setGLShaderProgram(cocos2d::GLProgram *glprogram);
    virtual void setBlendFunc(const cocos2d::BlendFunc &blendFunc) ;
    virtual const cocos2d::BlendFunc &getBlendFunc() { return _blendfunc;};
    
    unsigned int getScriptID()
    {
#if CC_ENABLE_SCRIPT_BINDING
        return this->_ID;
#endif
    }
    
    
    void setSlotVisible(const std::string &slotName,bool visible)
    {
        _armature->setSlotVisible(slotName,visible);
    }
    bool getSlotVisible(const std::string &slotName)
    {
        return _armature->getSlotVisible(slotName);
    }
    cocos2d::Sprite * getCCSlotSprite(const std::string &slotName)
    {
        return _armature->getCCSlotSprite(slotName);
    }
    cocos2d::Vec2 getSlotGlobalPosition(const std::string &slotName)
    {
        return _armature->getSlotGlobalPosition(slotName);
    }
    void setSlotDisplayTexture(const std::string &slotName,const std::string &filepath)
    {
        _armature->setSlotDisplayTexture(slotName,filepath);
    }
    void setSlotDisplaySpriteFrame(const std::string &slotName,cocos2d::SpriteFrame * frame)
    {
        _armature->setSlotDisplaySpriteFrame(slotName,frame);

    }
//    void changeSlotDisplay(const std::string &slotName,cocos2d::Node * display)
//    {
//        _armature->changeSlotDisplay(slotName,display);
//    }
    
    void playAnimation(const std::string &animationName,int times)
    {
        _armature->playAnimation(animationName,times);
    }
    void stopAnimation(const std::string &animationName,int times)
    {
        _armature->stopAnimation(animationName,times);
    }
    
    Frame *getFrameByFrameName(const std::string &timeLineName,const std::string &frameName)
    {
        return _armature->getFrameByFrameName(timeLineName,frameName);
    }
    
    Frame * getFrameByFrameEvent(const std::string &frameEvent)
    {
        return _armature->getFrameByFrameEvent( frameEvent );

    }
    
    int getDBADuration(const std::string &act_name)
    {
        return _armature->getAnimationDuration(act_name);
    }
    
    int getFrameRate()
    {
        return _armature->getFrameRate();
    }
    
    void registerEvent(bool value)
    {
        _armature->registerEvent(value);
    }

    
private:
    cocos2d::BlendFunc _blendfunc;
    bool animationPause;
    bool canSetOpacity;
// add by howe end

protected:
    DBCCArmature *_armature;
    WorldClock *_clock;
    
private:
    DRAGON_BONES_DISALLOW_COPY_AND_ASSIGN(DBCCArmatureNode);
};
NAME_SPACE_DRAGON_BONES_END
#endif  // DBCC_ARMATURE_NODE_H
