#include "DBCCFactory.h"
#include "DBCCTextureAtlas.h"
#include "DBCCSlot.h"
#include "DBCCEventDispatcher.h"
#include "base/ZipUtils.h"

USING_NS_CC;

NAME_SPACE_DRAGON_BONES_BEGIN
DBCCFactory* DBCCFactory::_instance = nullptr;

DBCCFactory* DBCCFactory::getInstance()
{
    if (!_instance)
    {
        _instance = new DBCCFactory();
    }
    return _instance;
}

void DBCCFactory::destroyInstance()
{
    if (_instance)
    {
       CC_SAFE_DELETE(_instance);
    }
}

DBCCFactory::DBCCFactory() {}
DBCCFactory::~DBCCFactory() {}

DBCCArmature* DBCCFactory::buildArmature(const std::string &armatureName) const
{
    return (DBCCArmature*) BaseFactory::buildArmature(armatureName);
}

DBCCArmature* DBCCFactory::buildArmature(const std::string &armatureName, const std::string &dragonBonesName) const
{
    return (DBCCArmature*) BaseFactory::buildArmature(armatureName, dragonBonesName);
}

DBCCArmature* DBCCFactory::buildArmature(const std::string &armatureName, const std::string &skinName, const std::string &animationName,
                                         const std::string &dragonBonesName, const std::string &textureAtlasName) const
{
    return (DBCCArmature*) BaseFactory::buildArmature(armatureName, skinName, animationName, dragonBonesName, textureAtlasName);
}

DBCCArmatureNode* DBCCFactory::buildArmatureNode(const std::string &armatureName) const
{
    auto armature = buildArmature(armatureName);
    return DBCCArmatureNode::create(armature);
}

DBCCArmatureNode* DBCCFactory::buildArmatureNode(const std::string &armatureName, const std::string &dragonBonesName) const
{
    auto armature = buildArmature(armatureName, dragonBonesName);
    return DBCCArmatureNode::create(armature);
}

DBCCArmatureNode* DBCCFactory::buildArmatureNode(const std::string &armatureName, const std::string &skinName, const std::string &animationName,
    const std::string &dragonBonesName, const std::string &textureAtlasName) const
{
    auto armature = buildArmature(armatureName, skinName, animationName, dragonBonesName, textureAtlasName);
    return DBCCArmatureNode::create(armature);
}

DragonBonesData* DBCCFactory::loadDragonBonesData(const std::string &dragonBonesFilePath, const std::string &name)
{
    DragonBonesData *existDragonBonesData = getDragonBonesData(name);

    if (existDragonBonesData)
    {
        return existDragonBonesData;
    }

    auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(dragonBonesFilePath);
    if (data.isNull())
    {
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
//        MessageBox(dragonBonesFilePath.c_str(), "Miss file or file is error");
#endif
        return nullptr;
    }
    
    static XMLDocument doc;
    // load skeleton.xml using XML parser.
    doc.Parse(reinterpret_cast<char*>(data.getBytes()), data.getSize());
    
    // armature scale
    float scale = cocos2d::Director::getInstance()->getContentScaleFactor();

    // paser dragonbones skeleton data.
    XMLDataParser parser;
    DragonBonesData *dragonBonesData = parser.parseDragonBonesData(doc.RootElement(), scale);
    addDragonBonesData(dragonBonesData, name);
    
    doc.Parse(nullptr,0);
    
    return dragonBonesData;
}

ITextureAtlas* DBCCFactory::loadTextureAtlas(const std::string &textureAtlasFile, const std::string &name)
{
    ITextureAtlas *existTextureAtlas = getTextureAtlas(name);

    if (existTextureAtlas)
    {
        refreshTextureAtlasTexture(name.empty() ? existTextureAtlas->textureAtlasData->name : name);
        return existTextureAtlas;
    }

    const auto &data = cocos2d::FileUtils::getInstance()->getDataFromFile(textureAtlasFile);
    if (data.getSize() == 0)
    {
        return nullptr;
    }

    // textureAtlas scale
    float scale = cocos2d::Director::getInstance()->getContentScaleFactor();

    XMLDocument doc;
    doc.Parse(reinterpret_cast<char*>(data.getBytes()), data.getSize());
    XMLDataParser parser;
    DBCCTextureAtlas *textureAtlas = new DBCCTextureAtlas();
    textureAtlas->textureAtlasData = parser.parseTextureAtlasData(doc.RootElement(), scale);

    size_t pos = textureAtlasFile.find_last_of("/");

    if (std::string::npos != pos)
    {
        std::string base_path = textureAtlasFile.substr(0, pos + 1);
        textureAtlas->textureAtlasData->imagePath = base_path + textureAtlas->textureAtlasData->imagePath;
    }

    //
    addTextureAtlas(textureAtlas, name);
    refreshTextureAtlasTexture(name.empty() ? textureAtlas->textureAtlasData->name : name);
    return textureAtlas;
}

void DBCCFactory::refreshTextureAtlasTexture(const std::string &name)
{
    for (auto iterator = _textureAtlasMap.begin(); iterator != _textureAtlasMap.end(); ++iterator)
    {
        DBCCTextureAtlas *textureAtlas = static_cast<DBCCTextureAtlas*>(iterator->second);
        const TextureAtlasData *textureAtlasData = textureAtlas->textureAtlasData;

        if (iterator->first == name)
        {
            textureAtlas->reloadTexture();
        }
    }
}

void DBCCFactory::refreshAllTextureAtlasTexture()
{
    for (auto iterator = _textureAtlasMap.begin(); iterator != _textureAtlasMap.end(); ++iterator)
    {
        DBCCTextureAtlas *textureAtlas = static_cast<DBCCTextureAtlas*>(iterator->second);
        const TextureAtlasData *textureAtlasData = textureAtlas->textureAtlasData;
        textureAtlas->reloadTexture();
    }
}

bool DBCCFactory::hasDragonBones(const std::string &skeletonName, const std::string &armatureName, const std::string &animationName)
{
    auto dragonbonesData = getDragonBonesData(skeletonName);

    if (!dragonbonesData) { return false; }

    if (!armatureName.empty())
    {
        auto armatureData = dragonbonesData->getArmatureData(armatureName);

        if (!armatureData) { return false; }

        if (!animationName.empty())
        {
            auto animationData = armatureData->getAnimationData(animationName);
            return animationData != nullptr;
        }
    }

    return true;
}

DBCCArmature* DBCCFactory::generateArmature(const ArmatureData *armatureData) const
{
    auto animation = new DBAnimation();
    // sprite
    auto display = cocos2d::Node::create();
    display->setCascadeColorEnabled(true);
    display->setCascadeOpacityEnabled(true);
    display->retain();
    // eventDispatcher
//    edit by howe
//    DBCCEventDispatcher *eventDispatcher = new DBCCEventDispatcher();
//    eventDispatcher->eventDispatcher = new cocos2d::EventDispatcher();
//    eventDispatcher->eventDispatcher->setEnabled(true);
    // armature
    return new DBCCArmature((ArmatureData*)(armatureData), animation, nullptr, display);
}

DBCCSlot* DBCCFactory::generateSlot(const SlotData *slotData) const
{
    return new DBCCSlot((SlotData*)(slotData));
}

void* DBCCFactory::generateDisplay(const ITextureAtlas *textureAtlas, const TextureData *textureData, const DisplayData *displayData) const
{
    DBCCTextureAtlas *dbccTextureAtlas = (DBCCTextureAtlas*)(textureAtlas);

    if (!dbccTextureAtlas || !textureData) return nullptr;

    auto texture = dbccTextureAtlas->getTexture();
    if (!texture)
    {
        return DBCCSprite::create();
    }
    
    cocos2d::SpriteFrame *spriteFrame = textureData->spriteFrame;
    
    cocos2d::Size originSize(0,0);
    
    if (spriteFrame == nullptr)
    {
        const float x = textureData->region.x;
        const float y = textureData->region.y;
        const bool rotated = textureData->rotated;
        const float width = rotated ? textureData->region.height : textureData->region.width;
        const float height = rotated ? textureData->region.width : textureData->region.height;
        cocos2d::Rect rect(x, y, width, height);
        cocos2d::Vec2 offset;
        
        originSize.setSize(width, height);
        if (textureData->frame)
        {
            float px = -textureData->frame->x;
            float py = -textureData->frame->y;
            originSize.width = textureData->frame->width;
            originSize.height = textureData->frame->height;
            // offset = sprite center - trimed texture center
            float cx1 = px + rect.size.width / 2;
            float cy1 = originSize.height - py - rect.size.height / 2;
            float cx2 = originSize.width / 2;
            float cy2 = originSize.height / 2;
            offset.x = cx2 - cx1;
            offset.y = cy2 - cy1;
        }
        // sprite
        spriteFrame= cocos2d::SpriteFrame::createWithTexture(texture, rect,
                                                             textureData->rotated, offset, originSize);
    }
    else
    {
        originSize = spriteFrame->getOriginalSizeInPixels();
    }

//    cocos2d::Node *display = cocos2d::Sprite::createWithSpriteFrame(spriteFrame);
    DBCCSprite * display = DBCCSprite::createWithSpriteFrame(spriteFrame);
    
    display->setCascadeColorEnabled(true);
    display->setCascadeOpacityEnabled(true);
    display->retain();
    float pivotX = 0;
    float pivotY = 0;

    if (displayData)
    {
        pivotX = displayData->pivot.x;
        pivotY = displayData->pivot.y;
    }

    display->setAnchorPoint(cocos2d::Vec2(pivotX / originSize.width, 1.f - pivotY / originSize.height));
    display->setContentSize(originSize);
    return display;
}

// add by howe begin

bool DBCCFactory::loadDragonBonesDataEasy(const std::string &dragonBonesFile)
{
    size_t pos = dragonBonesFile.find_last_of("/");
    size_t pos1 = dragonBonesFile.find_last_of(".");
    if (pos == std::string::npos || pos1 == std::string::npos)
    {
        CCLOG("1.loadDragonBonesDataEasy xml %s",dragonBonesFile.c_str());
        return false;
    }
    const std::string xml_tag_name = dragonBonesFile.substr(pos + 1,pos1-pos - 1);
    return loadDragonBonesData(dragonBonesFile,xml_tag_name);
}

bool DBCCFactory::loadTextureWithXML(const std::string &xml_file)
{
    size_t pos = xml_file.find_last_of("/");
    size_t pos1 = xml_file.find_last_of(".");
    if (pos == std::string::npos || pos1 == std::string::npos)
    {
        CCLOG(" %s",xml_file.c_str());
        return false;
    }
    const std::string xml_tag_name = xml_file.substr(pos + 1,pos1-pos - 1);
    return loadTextureAtlas(xml_file,xml_tag_name);
}

bool DBCCFactory::loadTextureWithPlist(const std::string &plist_file)
{
    size_t pos = plist_file.find_last_of("/");
    size_t pos1 = plist_file.find_last_of(".");
    if (pos == std::string::npos || pos1 == std::string::npos)
    {
        CCLOG("error:1.%s",plist_file.c_str());
        return false;
    }
    const std::string plist_tag_name = plist_file.substr(pos + 1,pos1-pos - 1);
    pos = plist_tag_name.find_last_of("_");
    if (pos == std::string::npos)
    {
        CCLOG("error:2.%s",plist_file.c_str());
        return false;
    }
    
    ITextureAtlas *existTextureAtlas = getTextureAtlas(plist_tag_name);
    if (existTextureAtlas)
    {
        refreshTextureAtlasTexture(plist_tag_name.empty() ? existTextureAtlas->textureAtlasData->name : plist_tag_name);
        return false;
    }
    
    const std::string &fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(plist_file);
    if (!cocos2d::FileUtils::getInstance()->isFileExist(fullPath))
    {
        CCLOG("error canot find file  %s",plist_file.c_str());
        
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
//        MessageBox(plist_file.c_str(), "Miss file");
#endif
        return false;
    }
    cocos2d::ValueMap dict = cocos2d::FileUtils::getInstance()->getValueMapFromFile(fullPath);
    if (dict.size() < 1)
    {
        CCLOG("error:%s failed",fullPath.c_str());
        
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
        MessageBox(plist_file.c_str(), "Parse Error");
#endif
        return false;
    }
    
    std::string textureFileName("");
    
    if (dict.find("metadata") != dict.end())
    {
        cocos2d::ValueMap& metadataDict = dict["metadata"].asValueMap();
        // try to read  texture file name from meta data
        textureFileName = metadataDict["textureFileName"].asString();
    }
    pos = plist_file.find_last_of("/");
    
    if (std::string::npos != pos)
    {
        std::string base_path = plist_file.substr(0, pos + 1);
        textureFileName = base_path + textureFileName;
    }
    
    TextureAtlasData *textureAtlasData = new TextureAtlasData();
    textureAtlasData->name = plist_tag_name;
    textureAtlasData->imagePath = textureFileName;
    cocos2d::ValueMap& framesDict = dict["frames"].asValueMap();
    
    auto textureCache = cocos2d::Director::getInstance()->getTextureCache();
    
    //    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_file);
    auto texture = textureCache->addImage(textureFileName);
    /*
     */
    for (auto iter = framesDict.begin(); iter != framesDict.end(); ++iter)
    {
        cocos2d::ValueMap& frameDict = iter->second.asValueMap();
        std::string spriteFrameName = iter->first;
        size_t fpos = spriteFrameName.find(".");
        spriteFrameName = spriteFrameName.substr(0,fpos);
        spriteFrameName = "parts/" + spriteFrameName;
        
        TextureData *textureData = new TextureData();
        
        textureData->name = spriteFrameName;
        textureData->spriteFrame = new cocos2d::SpriteFrame();
        textureData->spriteFrame->initWithTexture(texture,
                                                  cocos2d::RectFromString(frameDict["frame"].asString()),
                                                  frameDict["rotated"].asBool(),
                                                  cocos2d::PointFromString(frameDict["offset"].asString()),
                                                  cocos2d::SizeFromString(frameDict["sourceSize"].asString()));
        textureAtlasData->textureDataList.push_back(textureData);
    }
    
    DBCCTextureAtlas *textureAtlas = new DBCCTextureAtlas();
    textureAtlas->textureAtlasData = textureAtlasData;
    addTextureAtlas(textureAtlas,plist_tag_name);
    refreshTextureAtlasTexture(plist_tag_name.empty() ? textureAtlas->textureAtlasData->name : plist_tag_name);
    return true;
}

DBCCArmature *DBCCFactory::buildArmatureWithTag(const std::string &config_tag_name)
{
    size_t pos = config_tag_name.find_last_of("_");
    if (pos == std::string::npos)
    {
        CCLOG("8.%s",config_tag_name.c_str());
        return nullptr;
    }
    
    std::string textureName(config_tag_name);
    
    size_t len = config_tag_name.length();
    size_t pos1 = config_tag_name.find_last_of(".");
    if (pos1 > pos)
    {
        len = pos1 - (pos + 1);
        textureName = config_tag_name.substr(0,pos1);
    }
    std::string armature_key_name = config_tag_name.substr(pos + 1,len);
    
    auto armature = buildArmature(armature_key_name, "", armature_key_name, armature_key_name, textureName);
    
    return armature;
}

DBCCArmatureNode *DBCCFactory::buildArmatureNodeWithTag(const std::string &plist_tag_name)
{
    auto armature = buildArmatureWithTag(plist_tag_name);
    return DBCCArmatureNode::create(armature);
}

DBCCArmatureNode * DBCCFactory::loadTextureAndBuildArmatureNode(const std::string &plist_file)
{
    if(loadTextureWithPlist(plist_file))
    {
        size_t pos = plist_file.find_last_of("/");
        size_t pos1 = plist_file.find_last_of(".");
        if (pos == std::string::npos || pos1 == std::string::npos)
        {
            CCLOG("9. %s",plist_file.c_str());
            return nullptr;
        }
        if (pos1 > pos)
        {
            const std::string plist_tag_name = plist_file.substr(pos + 1,pos1 - pos - 1);
            return buildArmatureNodeWithTag(plist_tag_name);
        }
    }
    return nullptr;
}

DBCCArmatureNode * DBCCFactory::buildArmatureNodeWithDragonBonesDataAndTexture(const std::string &dragonBonesName,const std::string &textureAtlasName)
{
    dragonBones::DBCCArmatureNode * node = dragonBones::DBCCFactory::getInstance()->buildArmatureNode(dragonBonesName, "", dragonBonesName, dragonBonesName, textureAtlasName);
    return node;
}

cocos2d::Sprite* DBCCFactory::getTextureSprite(const std::string &textureName, const std::string &textureAtlasName, const DisplayData *displayData)
{
    cocos2d::Sprite* m_pSprite =  (cocos2d::Sprite*)getTextureDisplay(textureName,textureAtlasName,displayData);
    return m_pSprite;
}


// add by howe end

NAME_SPACE_DRAGON_BONES_END
