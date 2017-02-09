//
//  TextAddAction.h
//  MegoGame
//
//  Created by sxp on 15/6/29.
//
//  just use UIText
//
//
//
//

#ifndef __MegoGame__ProgressAction__
#define __MegoGame__ProgressAction__

#include <stdio.h>

#include "cocos2d.h"
using namespace cocos2d;


class ProgressAction : public cocos2d::ActionInterval
{
    
public:
    //create frame callback func
    typedef std::function<void(Ref*,float)> myProgressActionCallback;
    
    static ProgressAction* create(float duration, float starNum, float endNum,const myProgressActionCallback& _callback);
    static ProgressAction* create(float duration, float starNum, float endNum);
    
    virtual ProgressAction* clone() const override;
    virtual ProgressAction* reverse(void) const  override;
    virtual void startWithTarget(Node *target) override;
    
    virtual void setProgressActionCallback(const myProgressActionCallback& _callback);
    
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ProgressAction();
    virtual ~ProgressAction();
    bool initWithDuration(float duration, float starNum, float endNum,const myProgressActionCallback& _callback);
protected:
    float starNum;
    float endNum;
    myProgressActionCallback _callback;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ProgressAction);
};


#endif /* defined(__MegoGame__ProgressAction__) */
