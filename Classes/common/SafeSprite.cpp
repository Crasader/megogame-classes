//
//  SafeSprite.cpp
//  MegoGame
//
//  Created by howe on 15/4/24.
//
//

#include "SafeSprite.h"


SafeSprite::SafeSprite()
{}

void SafeSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if (!_texture)
    {
        return;
    }
    Sprite::draw(renderer, transform, flags);
}

/********************************************************************/

unsigned int StrHash(const char *str)
{
    unsigned int seed = 131;
    unsigned int hash = 0;
    
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
    return (hash & 0x7FFFFFFF);
}

static PolygonCache* m_shareInstance = nullptr;

PolygonCache* PolygonCache::getInstance()
{
    if (m_shareInstance == nullptr){
        m_shareInstance = new PolygonCache();
    }
    return m_shareInstance;
}

PolygonCache::PolygonCache()
{
    m_mapCache.clear();
}

PolygonCache::~PolygonCache()
{
    m_mapCache.clear();
}

PolygonInfo* PolygonCache::getPolygonInfoByFilename(std::string filename)
{
    std::map<unsigned int,PolygonInfo>::iterator it = m_mapCache.find(StrHash(filename.c_str()));
    if (it != m_mapCache.end()){
        return &it->second;
    }
    return nullptr;
}

void PolygonCache::addPolygoInfoToCache(PolygonInfo& polygonInfo)
{
    m_mapCache[StrHash(polygonInfo.filename.c_str())] = polygonInfo;
}

void PolygonCache::purgePolygonCache()
{
    if (m_shareInstance){
        delete m_shareInstance;
        m_shareInstance = nullptr;
    }
}

#pragma mark - ReSprite -
ReSprite::ReSprite()
{
    
}

ReSprite::~ReSprite()
{
    
}

ReSprite* ReSprite::create(const std::string& filename)
{
    PolygonInfo *pPolygonInfo = PolygonCache::getInstance()->getPolygonInfoByFilename(filename);
    if (pPolygonInfo == nullptr){
        PolygonInfo info = std::move( AutoPolygon::generatePolygon(filename,Rect::ZERO,4.0) ); // std::move add by howe
        pPolygonInfo = &info;
        PolygonCache::getInstance()->addPolygoInfoToCache(info);
    }
    
    ReSprite *reSprite = new (std::nothrow) ReSprite();
    if(reSprite && reSprite->initWithPolygon(*pPolygonInfo))
    {
        reSprite->autorelease();
        reSprite->debugDraw(false);
        return reSprite;
    }
    CC_SAFE_DELETE(reSprite);
    return nullptr;
}

bool ReSprite::initWithFile(const std::string& filename)
{
    PolygonInfo* pPolygonInfo = PolygonCache::getInstance()->getPolygonInfoByFilename(filename);
    if (pPolygonInfo != nullptr){
        return this->initWithPolygon(*pPolygonInfo);
        
    }
    PolygonInfo info = std::move( AutoPolygon::generatePolygon(filename,Rect::ZERO,4.0) ); // std::move add by howe
    PolygonCache::getInstance()->addPolygoInfoToCache(info);
    return this->initWithPolygon(info);
    
}

inline int chg_sign(int x, int sign)
{
    return (x + sign) ^ sign;
}

bool is_in_triangle(const Vec2& a, const Vec2& b, const Vec2& c, const Vec2& p)
{
    Vec2 ab(b -a), ac(c - a), ap(p - a);
    int abc = ab.cross(ac);
    int abp = ab.cross(ap);
    int apc = ap.cross(ac);
    int pbc = abc - abp - apc;
    const int sign = (abc >= 0) - 1;
    
    return (chg_sign(abp, sign) | chg_sign(apc, sign) | chg_sign(pbc, sign)) >= 0;
}
/** add by howe    */
bool is_in_triangle(const Vec3& a, const Vec3& b, const Vec3& c, const Vec2& p)
{
    Vec2 ab(b.x -a.x,b.y-a.y), ac(c.x - a.x,c.y-a.y), ap(p.x - a.x,p.y-a.y);
    int abc = ab.cross(ac);
    int abp = ab.cross(ap);
    int apc = ap.cross(ac);
    int pbc = abc - abp - apc;
    const int sign = (abc >= 0) - 1;
    
    return (chg_sign(abp, sign) | chg_sign(apc, sign) | chg_sign(pbc, sign)) >= 0;
}

bool ReSprite::pointInSprite(const cocos2d::Vec2 &point)
{
    auto last = _polyInfo.triangles.indexCount/3;
    auto _indices = _polyInfo.triangles.indices;
    auto _verts = _polyInfo.triangles.verts;
    for(unsigned int i = 0; i < last; i++)
    {
        const Vec3 &pot1 =_verts[_indices[i*3]].vertices;
        const Vec3 &pot2 = _verts[_indices[i*3+1]].vertices;
        const Vec3 &pot3 = _verts[_indices[i*3+2]].vertices;
        
//        if (is_in_triangle(Vec2(pot1.x, pot1.y),Vec2(pot2.x,pot2.y),Vec2(pot3.x,pot3.y),point)){
//            return true;
//        }
        /** add by howe   */
        if (is_in_triangle(pot1,pot2,pot3,point)){
            return true;
        }
        
    }
    return false;
}

void ReSprite::setReSpriteFlipX(bool flipX)
{
    this->setScaleX(flipX ? -1 : 1);
}

bool ReSprite::isReSpriteFlipX()
{
    return (-1 == (int)this->getScaleX());
}
