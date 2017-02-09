#include "base/ccConfig.h"
#ifndef __dragonbones_h__
#define __dragonbones_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_dragonBones_Frame_class;
extern JSObject *jsb_dragonBones_Frame_prototype;

bool js_dragonbones_Frame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dragonbones_Frame_finalize(JSContext *cx, JSObject *obj);
void js_register_dragonbones_Frame(JSContext *cx, JS::HandleObject global);
void register_all_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_dragonbones_Frame_getaction(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_Frame_getevent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_Frame_getframeType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_Frame_dispose(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_Frame_getduration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_Frame_getsound(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_Frame_geteventParameters(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_Frame_getposition(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_EventData_class;
extern JSObject *jsb_dragonBones_EventData_prototype;

bool js_dragonbones_EventData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dragonbones_EventData_finalize(JSContext *cx, JSObject *obj);
void js_register_dragonbones_EventData(JSContext *cx, JS::HandleObject global);
void register_all_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_dragonbones_EventData_getBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_EventData_getFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_EventData_getType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_EventData_getArmature(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_EventData_getCurrentEventTargetId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_EventData_getFrameLabel(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_EventData_getSound(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_EventData_getStringType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_EventData_getAnimationName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_EventData_typeToString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_EventData_returnObject(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_EventData_clearObjects(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_EventData_borrowObject(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_EventData_EventData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_DBCCArmatureNode_class;
extern JSObject *jsb_dragonBones_DBCCArmatureNode_prototype;

bool js_dragonbones_DBCCArmatureNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dragonbones_DBCCArmatureNode_finalize(JSContext *cx, JSObject *obj);
void js_register_dragonbones_DBCCArmatureNode(JSContext *cx, JS::HandleObject global);
void register_all_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_dragonbones_DBCCArmatureNode_getIsOpactityAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_getFrameByFrameEvent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_getDBADuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_setSlotDisplaySpriteFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_getSlotGlobalPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_registerEvent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_setSlotDisplayTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_stopAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_setGLShaderProgram(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_getFrameByFrameName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_getCCSlotSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_playAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_getInnerBoundingBox(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_getScriptID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_getFrameRate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_playOpacityAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_pauseAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_getSlotVisible(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_setSlotVisible(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCArmatureNode_DBCCArmatureNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_DBCCFactory_class;
extern JSObject *jsb_dragonBones_DBCCFactory_prototype;

bool js_dragonbones_DBCCFactory_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dragonbones_DBCCFactory_finalize(JSContext *cx, JSObject *obj);
void js_register_dragonbones_DBCCFactory(JSContext *cx, JS::HandleObject global);
void register_all_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_dragonbones_DBCCFactory_removeAllDBData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCFactory_buildArmatureNodeWithTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCFactory_loadTextureWithPlist(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCFactory_getTextureSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCFactory_loadDragonBonesDataEasy(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCFactory_hasDragonBones(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCFactory_removeAllTextureAtlas(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCFactory_refreshAllTextureAtlasTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCFactory_loadTextureWithXML(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCFactory_removeTextureData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCFactory_refreshTextureAtlasTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCFactory_buildArmatureNodeWithDragonBonesDataAndTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCFactory_removeDBData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCFactory_loadTextureAndBuildArmatureNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCFactory_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCFactory_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_dragonbones_DBCCFactory_DBCCFactory(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __dragonbones_h__
