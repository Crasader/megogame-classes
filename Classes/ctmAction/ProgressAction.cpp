//
//  TextAddAction.cpp
//  MegoGame
//
//  Created by sxp on 15/6/29.
//
//


#include "ProgressAction.h"


ProgressAction* ProgressAction::create(float duration, float starNum, float endNum,const myProgressActionCallback& _callback){

    auto a = new (std::nothrow) ProgressAction();
    
    if(a->initWithDuration(duration, starNum, endNum,_callback)){
        return a;
    }
    return NULL;
}
ProgressAction* ProgressAction::create(float duration, float starNum, float endNum){
    
    auto a = new (std::nothrow) ProgressAction();
    
    if(a->initWithDuration(duration, starNum, endNum,nullptr)){
        return a;
    }
    return NULL;
}

ProgressAction::ProgressAction():starNum(0),endNum(0),_callback(nullptr)
{
    
}
ProgressAction::~ProgressAction() {
}

ProgressAction* ProgressAction::clone() const
{
    return ProgressAction::create(_duration, starNum, endNum,_callback);
}

ProgressAction* ProgressAction::reverse(void) const
{
    return ProgressAction::create(_duration, endNum, starNum,_callback);
};

void ProgressAction::startWithTarget(Node *target)
{
    cocos2d::ActionInterval::startWithTarget(target);
}

bool ProgressAction::initWithDuration(float duration, float starNum, float endNum,const myProgressActionCallback& _callback)
{
    if (ActionInterval::initWithDuration(duration))
    {
        this->starNum = starNum;
        this->endNum = endNum;
        this->_callback = _callback;
        return true;
    }
    return false;
}

void ProgressAction::setProgressActionCallback(const myProgressActionCallback& _callback){
    this->_callback = _callback;
}
/**
 * @param time in seconds
 */
void ProgressAction::update(float time)
{
    if(_callback)
    {
        _callback(this->getOriginalTarget(), starNum + (endNum - starNum)*time);
    }
};