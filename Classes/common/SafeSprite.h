//
//  SafeSprite.h
//  MegoGame
//
//  Created by howe on 15/4/24.
//
//

#ifndef __MegoGame__SafeSprite__
#define __MegoGame__SafeSprite__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;


class SafeSprite : public Sprite
{
public:
    SafeSprite();
    
    CREATE_FUNC(SafeSprite);
#ifndef SKIP_BY_JS_AUTO_BINDING
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
#endif
    unsigned int getScriptID()
    {
#if CC_ENABLE_SCRIPT_BINDING
        return this->_ID;
#endif
        return 0;
    }
};

class PolygonCache
{
public:
    static PolygonCache* getInstance();
    PolygonInfo* getPolygonInfoByFilename(std::string filename);
    void addPolygoInfoToCache(PolygonInfo& polygonInfo);
    
    PolygonCache();
    virtual ~PolygonCache();
    static void purgePolygonCache();
private:
    std::map<unsigned int,PolygonInfo> m_mapCache;
    
};


class ReSprite
: public Sprite
{
public:
    ReSprite();
    virtual ~ReSprite();
    
    static ReSprite* create(const std::string& filename);
    virtual bool initWithFile(const std::string& filename);
    
    bool pointInSprite(const Vec2& point);
    void setReSpriteFlipX(bool flipX);
    bool isReSpriteFlipX();
};

#endif /* defined(__MegoGame__SafeSprite__) */
