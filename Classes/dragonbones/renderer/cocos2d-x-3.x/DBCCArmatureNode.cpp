#include "dbccMacro.h"
#include "DBCCArmatureNode.h"


NAME_SPACE_DRAGON_BONES_BEGIN

DBCCArmatureNode* DBCCArmatureNode::create(DBCCArmature *armature)
{
    DBCCArmatureNode *ret = new DBCCArmatureNode();
    
    if (ret && ret->initWithDBCCArmature(armature, nullptr))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

DBCCArmatureNode* DBCCArmatureNode::createWithWorldClock(DBCCArmature *armature, WorldClock *clock)
{
    DBCCArmatureNode *ret = new DBCCArmatureNode();
    if (!clock)
        clock = WorldClock::getInstance();

    if (ret && ret->initWithDBCCArmature(armature, clock))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

bool DBCCArmatureNode::initWithDBCCArmature(DBCCArmature *armature, WorldClock *clock)
{
    if (armature != nullptr)
    {
        _blendfunc = cocos2d::BlendFunc::ALPHA_PREMULTIPLIED;
        
        _armature = armature;
        _armature->setArmatureNode(this);
//        _clock = clock;
//        if (clock)
//        {
//            clock->add(this);
//        }else
//        {
//            scheduleUpdate();
//        }
        auto node= armature->getCCDisplay();
        addChild(node);
        setCascadeOpacityEnabled(true);
        setCascadeColorEnabled(true);
        return true;
    }

	return false;
}


DBCCArmatureNode::DBCCArmatureNode()
    :_armature(nullptr)
    ,_clock(nullptr)
    ,animationPause(false)
    ,canSetOpacity(true)
{
}
DBCCArmatureNode::~DBCCArmatureNode()
{
//    if (_clock)
//    {
//        _clock->remove(this);
//        _clock = nullptr;
//    } else 
//    {
//        unscheduleUpdate();
//    }
    if (_armature)
    {
        delete _armature;
        _armature = nullptr;
    }
}
void DBCCArmatureNode::onEnter()
{
    Node::onEnter();
    scheduleUpdate();
    this->update(0.01);
}
void DBCCArmatureNode::onExit()
{
    animationPause = true;
    unscheduleUpdate();
    
    Node::onExit();
}
cocos2d::Rect DBCCArmatureNode::getBoundingBox() const
{
    const auto &rect = _armature->getCCBoundingBox();
    return cocos2d::RectApplyTransform(rect, getNodeToParentTransform());
}

cocos2d::Rect DBCCArmatureNode::getInnerBoundingBox() const
{
    return _armature->getCCBoundingBox();
}

void DBCCArmatureNode::update(float dt)
{
    if (animationPause)
    {
        return;
    }
//    DBASSERT(!_clock, "can not has clock when update!");
    advanceTime(dt);
}

void DBCCArmatureNode::advanceTime(float dt)
{
    retain();
    _armature->advanceTime(dt);
    release();
}

void setNodeShaderProgram(cocos2d::Node * container, cocos2d::GLProgram *glprogram)
{
    for ( auto child : container->getChildren())
    {
        auto sp = dynamic_cast<cocos2d::Sprite*>(child);
        if (sp)
        {
            sp->setGLProgram(glprogram);
        }
        setNodeShaderProgram(child,glprogram);
    }
}

void DBCCArmatureNode::setGLShaderProgram(cocos2d::GLProgram *glprogram)
{
    Node::setGLProgram(glprogram);
    for ( auto childNode : _children)
    {
        setNodeShaderProgram(childNode,glprogram);
    }
}

void DBCCArmatureNode::setBlendFunc(const cocos2d::BlendFunc &blendFunc)
{
    if (_blendfunc==blendFunc)
    {
        return;
    }
    if (blendFunc==cocos2d::BlendFunc::ALPHA_PREMULTIPLIED )
    {
        return;
    }
    _blendfunc=blendFunc;
    std::function<void(cocos2d::Node * container,const cocos2d::BlendFunc &blendFunc)> blendFucCall;
    
    blendFucCall = [&blendFucCall](cocos2d::Node * container,const cocos2d::BlendFunc &blendFunc)
    {
        for ( auto child : container->getChildren())
        {
            auto sp = dynamic_cast<cocos2d::Sprite*>(child);
            if (sp)
            {
                sp->setBlendFunc(blendFunc);
            }
            else
            {
                blendFucCall(child,blendFunc);
            }
        }
    };
    blendFucCall(this,blendFunc);
}


NAME_SPACE_DRAGON_BONES_END
