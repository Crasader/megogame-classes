#include "DBCCArmature.h"
#include "DBCCEventDispatcher.h"
#include "DBCCArmatureNode.h"

#if (DRAGON_BONES_ENABLE_LUA == 1)
#include "DBCCLuaUtils.h"
#include "CCLuaEngine.h"
#endif // DRAGON_BONES_ENABLE_LUA

#include "cocos2d_specifics.hpp"
#include "jsapi.h"

void _callJSFunction(dragonBones::EventData *eventData)
{
    static const char DB_EVENT_CALL[] = "DB_OnEventCallHandler";

    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject gl(cx, ScriptingCore::getInstance()->getGlobalObject());
    
    static bool hasAction;
    JS::RootedValue temp_retval(cx);
    
    if (JS_HasProperty(cx, gl, DB_EVENT_CALL, &hasAction) && hasAction)
    {
        if(!JS_GetProperty(cx, gl, DB_EVENT_CALL, &temp_retval))
        {
            return;
        }
        if(temp_retval == JSVAL_VOID)
        {
            return;
        }
//        JSAutoCompartment ac(cx, gl);
        
        js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::EventData>(cx, eventData);

        jsval dataVal = OBJECT_TO_JSVAL(jsProxy->obj);

        JS::RootedValue retval(cx);
        JS_CallFunctionName(cx, gl, DB_EVENT_CALL,JS::HandleValueArray::fromMarkedLocation(1, &dataVal), &retval);
        
    }
}

NAME_SPACE_DRAGON_BONES_BEGIN

cocos2d::Node* DBCCArmature::getCCDisplay() const
{
    return static_cast<cocos2d::Node*>(_display);
}

cocos2d::EventDispatcher* DBCCArmature::getCCEventDispatcher() const
{
    return static_cast<DBCCEventDispatcher*>(_eventDispatcher)->eventDispatcher;
}

DBCCArmature::DBCCArmature(ArmatureData *armatureData, DBAnimation *animation, IEventDispatcher *eventDispatcher, cocos2d::Node *display)
    : Armature(armatureData, animation, eventDispatcher, display)
    ,_armatureNode(nullptr)
    ,isEventListerner(false)
#if (DRAGON_BONES_ENABLE_LUA == 1)
    ,_frameEventHandler(0)
    ,_animationEventHandler(0)
#endif // DRAGON_BONES_ENABLE_LUA
{
}
DBCCArmature::~DBCCArmature()
{
#if (DRAGON_BONES_ENABLE_LUA == 1)
    unregisterFrameEventHandler();
    unregisterAnimationEventHandler();
#endif // DRAGON_BONES_ENABLE_LUA

    dispose();
}
void DBCCArmature::dispose()
{
    _delayDispose = true;
    if(!_animation || _lockDispose)
    {
        return;
    }

    if (_display)
    {
        getCCDisplay()->cleanup();
        getCCDisplay()->release();
    }

    Armature::dispose();
}

Rectangle DBCCArmature::getBoundingBox()
{
    auto r = getCCBoundingBox();
    return Rectangle(r.origin.x, r.origin.y, r.size.width, r.size.height);
}

cocos2d::Rect DBCCArmature::getCCBoundingBox()
{
    float minx = 0, miny = 0, maxx = 0, maxy = 0;
    bool first = true;
    for (const auto slot : _slotList)
    {
        if (!slot->getVisible() || !slot->isShowDisplay()) { continue; }
        auto r = slot->getBoundingBox();
        if (first)
        {
            first = false;
            minx = r.x;
            miny = r.y;
            maxx = r.x + r.width;
            maxy = r.y + r.height;
        }
        else
        {
            minx = r.x < minx ? r.x : minx;
            miny = r.y < miny ? r.y : miny;
            maxx = r.x + r.width > maxx ? r.x + r.width : maxx;
            maxy = r.y + r.height > maxy ? r.y + r.height : maxy;
        }
    }
    cocos2d::Rect rect(minx, miny, maxx - minx, maxy - miny);
    return cocos2d::RectApplyTransform(rect, getCCDisplay()->getNodeToParentTransform());
}

DBCCSlot* DBCCArmature::getCCSlot(const std::string &slotName) const
{
    Slot *slot = getSlot(slotName);
    return slot ? static_cast<DBCCSlot*>(slot) : nullptr;
}

void DBCCArmature::sortSlotsByZOrder()
{
    std::sort(_slotList.begin() , _slotList.end() , sortSlot);

    int nShowCount = 0;
    int nDisplayChildrenCount = static_cast<cocos2d::Node*>(getCCDisplay())->getChildrenCount();

    for (size_t i = 0, l = _slotList.size(); i < l; ++i)
    {
        Slot *slot = _slotList[i];
        if (slot->isShowDisplay())
        {
            cocos2d::Node* slotDisplayNode = static_cast<cocos2d::Node*>(slot->getDisplay());
            if (slotDisplayNode)
            {
                slotDisplayNode->setLocalZOrder(nDisplayChildrenCount + nShowCount);
            }
            nShowCount += 1;
        }
    }
    _slotsZOrderChanged = false;
}

DBCCArmatureNode* DBCCArmature::getArmatureNode() const
{
    return _armatureNode;
}
void DBCCArmature::setArmatureNode(DBCCArmatureNode *armatureNode)
{
    _armatureNode = armatureNode;
}

void DBCCArmature::_sendAllEventImmediately()
{
    if (!_eventDataList.empty())
    {
        
        for (auto eventData : _eventDataList)
        {
            if (isEventListerner && this->getArmatureNode())
            {
                eventData->currentEventTargetId = this->getArmatureNode()->getScriptID();
                _callJSFunction(eventData);
            }
            if (_listener)
            {
                _listener(eventData);
            }
            //            _eventDispatcher->dispatchEvent(_eventDataList[i]);
            EventData::returnObject(eventData);
        }
        //
        //        for (size_t i = 0, l = _eventDataList.size(); i < l; ++i)
        //        {
        //            if (_listener)
        //            {
        //                _listener(_eventDataList[i]);
        //            }
        //            //            _eventDispatcher->dispatchEvent(_eventDataList[i]);
        //            EventData::returnObject(_eventDataList[i]);
        //        }
        _eventDataList.clear();
    }
}


int DBCCSprite::ref_count = 0;

DBCCSprite::DBCCSprite()
{
    DBCCSprite::ref_count+= 1;
}
DBCCSprite::~DBCCSprite()
{
    DBCCSprite::ref_count -=1;
}

NAME_SPACE_DRAGON_BONES_END