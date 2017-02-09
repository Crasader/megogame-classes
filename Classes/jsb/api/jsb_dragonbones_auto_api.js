/**
 * @module dragonbones
 */
var db = db || {};

/**
 * @class Frame
 */
db.Frame = {

/**
 * @method getaction
 * @return {String}
 */
getaction : function (
)
{
    return ;
},

/**
 * @method getevent
 * @return {String}
 */
getevent : function (
)
{
    return ;
},

/**
 * @method getframeType
 * @return {dragonBones::Frame::FrameType}
 */
getframeType : function (
)
{
    return dragonBones::Frame::FrameType;
},

/**
 * @method dispose
 */
dispose : function (
)
{
},

/**
 * @method getduration
 * @return {int}
 */
getduration : function (
)
{
    return 0;
},

/**
 * @method getsound
 * @return {String}
 */
getsound : function (
)
{
    return ;
},

/**
 * @method geteventParameters
 * @return {String}
 */
geteventParameters : function (
)
{
    return ;
},

/**
 * @method getposition
 * @return {int}
 */
getposition : function (
)
{
    return 0;
},

};

/**
 * @class EventData
 */
db.EventData = {

/**
 * @method getBone
 * @return {dragonBones::Bone}
 */
getBone : function (
)
{
    return dragonBones::Bone;
},

/**
 * @method getFrame
 * @return {dragonBones::Frame}
 */
getFrame : function (
)
{
    return dragonBones::Frame;
},

/**
 * @method getType
 * @return {dragonBones::EventData::EventType}
 */
getType : function (
)
{
    return dragonBones::EventData::EventType;
},

/**
 * @method getArmature
 * @return {dragonBones::Armature}
 */
getArmature : function (
)
{
    return dragonBones::Armature;
},

/**
 * @method getCurrentEventTargetId
 * @return {unsigned int}
 */
getCurrentEventTargetId : function (
)
{
    return 0;
},

/**
 * @method getFrameLabel
 * @return {String}
 */
getFrameLabel : function (
)
{
    return ;
},

/**
 * @method getSound
 * @return {String}
 */
getSound : function (
)
{
    return ;
},

/**
 * @method getStringType
 * @return {String}
 */
getStringType : function (
)
{
    return ;
},

/**
 * @method getAnimationName
 * @return {String}
 */
getAnimationName : function (
)
{
    return ;
},

/**
 * @method typeToString
 * @param {dragonBones::EventData::EventType} arg0
 * @return {String}
 */
typeToString : function (
eventtype 
)
{
    return ;
},

/**
 * @method returnObject
 * @param {dragonBones::EventData} arg0
 */
returnObject : function (
eventdata 
)
{
},

/**
 * @method clearObjects
 */
clearObjects : function (
)
{
},

/**
 * @method borrowObject
 * @param {dragonBones::EventData::EventType} arg0
 * @return {dragonBones::EventData}
 */
borrowObject : function (
eventtype 
)
{
    return dragonBones::EventData;
},

/**
 * @method EventData
 * @constructor
 */
EventData : function (
)
{
},

};

/**
 * @class DBCCArmatureNode
 */
db.DBCCArmatureNode = {

/**
 * @method getIsOpactityAnimation
 * @return {bool}
 */
getIsOpactityAnimation : function (
)
{
    return false;
},

/**
 * @method getFrameByFrameEvent
 * @param {String} arg0
 * @return {dragonBones::Frame}
 */
getFrameByFrameEvent : function (
str 
)
{
    return dragonBones::Frame;
},

/**
 * @method getDBADuration
 * @param {String} arg0
 * @return {int}
 */
getDBADuration : function (
str 
)
{
    return 0;
},

/**
 * @method setSlotDisplaySpriteFrame
 * @param {String} arg0
 * @param {cc.SpriteFrame} arg1
 */
setSlotDisplaySpriteFrame : function (
str, 
spriteframe 
)
{
},

/**
 * @method getSlotGlobalPosition
 * @param {String} arg0
 * @return {vec2_object}
 */
getSlotGlobalPosition : function (
str 
)
{
    return cc.Vec2;
},

/**
 * @method registerEvent
 * @param {bool} arg0
 */
registerEvent : function (
bool 
)
{
},

/**
 * @method setSlotDisplayTexture
 * @param {String} arg0
 * @param {String} arg1
 */
setSlotDisplayTexture : function (
str, 
str 
)
{
},

/**
 * @method stopAnimation
 * @param {String} arg0
 * @param {int} arg1
 */
stopAnimation : function (
str, 
int 
)
{
},

/**
 * @method setGLShaderProgram
 * @param {cc.GLProgram} arg0
 */
setGLShaderProgram : function (
glprogram 
)
{
},

/**
 * @method getFrameByFrameName
 * @param {String} arg0
 * @param {String} arg1
 * @return {dragonBones::Frame}
 */
getFrameByFrameName : function (
str, 
str 
)
{
    return dragonBones::Frame;
},

/**
 * @method getBlendFunc
 * @return {cc.BlendFunc}
 */
getBlendFunc : function (
)
{
    return cc.BlendFunc;
},

/**
 * @method getCCSlotSprite
 * @param {String} arg0
 * @return {cc.Sprite}
 */
getCCSlotSprite : function (
str 
)
{
    return cc.Sprite;
},

/**
 * @method playAnimation
 * @param {String} arg0
 * @param {int} arg1
 */
playAnimation : function (
str, 
int 
)
{
},

/**
 * @method getInnerBoundingBox
 * @return {rect_object}
 */
getInnerBoundingBox : function (
)
{
    return cc.Rect;
},

/**
 * @method getScriptID
 * @return {unsigned int}
 */
getScriptID : function (
)
{
    return 0;
},

/**
 * @method getFrameRate
 * @return {int}
 */
getFrameRate : function (
)
{
    return 0;
},

/**
 * @method setBlendFunc
 * @param {cc.BlendFunc} arg0
 */
setBlendFunc : function (
blendfunc 
)
{
},

/**
 * @method playOpacityAnimation
 * @param {bool} arg0
 */
playOpacityAnimation : function (
bool 
)
{
},

/**
 * @method pauseAnimation
 * @param {bool} arg0
 */
pauseAnimation : function (
bool 
)
{
},

/**
 * @method getSlotVisible
 * @param {String} arg0
 * @return {bool}
 */
getSlotVisible : function (
str 
)
{
    return false;
},

/**
 * @method setSlotVisible
 * @param {String} arg0
 * @param {bool} arg1
 */
setSlotVisible : function (
str, 
bool 
)
{
},

/**
 * @method create
 * @param {dragonBones::DBCCArmature} arg0
 * @return {dragonBones::DBCCArmatureNode}
 */
create : function (
dbccarmature 
)
{
    return dragonBones::DBCCArmatureNode;
},

/**
 * @method DBCCArmatureNode
 * @constructor
 */
DBCCArmatureNode : function (
)
{
},

};

/**
 * @class DBCCFactory
 */
db.DBCCFactory = {

/**
 * @method removeAllDBData
 */
removeAllDBData : function (
)
{
},

/**
 * @method buildArmatureNodeWithTag
 * @param {String} arg0
 * @return {dragonBones::DBCCArmatureNode}
 */
buildArmatureNodeWithTag : function (
str 
)
{
    return dragonBones::DBCCArmatureNode;
},

/**
 * @method loadTextureWithPlist
 * @param {String} arg0
 * @return {bool}
 */
loadTextureWithPlist : function (
str 
)
{
    return false;
},

/**
 * @method getTextureSprite
 * @param {String} arg0
 * @param {String} arg1
 * @param {dragonBones::DisplayData} arg2
 * @return {cc.Sprite}
 */
getTextureSprite : function (
str, 
str, 
displaydata 
)
{
    return cc.Sprite;
},

/**
 * @method loadDragonBonesDataEasy
 * @param {String} arg0
 * @return {bool}
 */
loadDragonBonesDataEasy : function (
str 
)
{
    return false;
},

/**
 * @method hasDragonBones
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @return {bool}
 */
hasDragonBones : function (
str, 
str, 
str 
)
{
    return false;
},

/**
 * @method removeAllTextureAtlas
 */
removeAllTextureAtlas : function (
)
{
},

/**
 * @method refreshAllTextureAtlasTexture
 */
refreshAllTextureAtlasTexture : function (
)
{
},

/**
 * @method loadTextureWithXML
 * @param {String} arg0
 * @return {bool}
 */
loadTextureWithXML : function (
str 
)
{
    return false;
},

/**
 * @method removeTextureData
 * @param {String} arg0
 */
removeTextureData : function (
str 
)
{
},

/**
 * @method refreshTextureAtlasTexture
 * @param {String} arg0
 */
refreshTextureAtlasTexture : function (
str 
)
{
},

/**
 * @method buildArmatureNodeWithDragonBonesDataAndTexture
 * @param {String} arg0
 * @param {String} arg1
 * @return {dragonBones::DBCCArmatureNode}
 */
buildArmatureNodeWithDragonBonesDataAndTexture : function (
str, 
str 
)
{
    return dragonBones::DBCCArmatureNode;
},

/**
 * @method removeDBData
 * @param {String} arg0
 */
removeDBData : function (
str 
)
{
},

/**
 * @method loadTextureAndBuildArmatureNode
 * @param {String} arg0
 * @return {dragonBones::DBCCArmatureNode}
 */
loadTextureAndBuildArmatureNode : function (
str 
)
{
    return dragonBones::DBCCArmatureNode;
},

/**
 * @method destroyInstance
 */
destroyInstance : function (
)
{
},

/**
 * @method getInstance
 * @return {dragonBones::DBCCFactory}
 */
getInstance : function (
)
{
    return dragonBones::DBCCFactory;
},

/**
 * @method DBCCFactory
 * @constructor
 */
DBCCFactory : function (
)
{
},

};
