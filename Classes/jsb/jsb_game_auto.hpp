#include "base/ccConfig.h"
#ifndef __game_h__
#define __game_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_GameSession_class;
extern JSObject *jsb_GameSession_prototype;

bool js_game_GameSession_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_game_GameSession_finalize(JSContext *cx, JSObject *obj);
void js_register_game_GameSession(JSContext *cx, JS::HandleObject global);
void register_all_game(JSContext* cx, JS::HandleObject obj);
bool js_game_GameSession_QueuePacket(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_GameSession_EndUpdateConnectingTick(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_GameSession_BeginUpdateConnectingTick(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_GameSession_SendData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_GameSession_sendCmd(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_GameSession_ReleaseGameSock(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_GameSession_EndUpdateTick(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_GameSession_ConnectNewSock(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_GameSession_BeginUpdateTick(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_GameSession_IsActive(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_GameSession_InitNet(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_GameSession_Instance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_GameSession_SendRawData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_GameSession_InitDebuggerClient(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_GameSession_CloseNet(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_GameSession_GameSession(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_Util_class;
extern JSObject *jsb_Util_prototype;

bool js_game_Util_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_game_Util_finalize(JSContext *cx, JSObject *obj);
void js_register_game_Util(JSContext *cx, JS::HandleObject global);
void register_all_game(JSContext* cx, JS::HandleObject obj);
bool js_game_Util_GetCcPositionTextureColor_noMVP_vert(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Util_getSavedPath(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Util_createFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Util_isFileParentCreated(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Util_closeKeyBoard(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Util_loopFiles(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Util_GetCcPositionTextureColor_vert(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Util_getAllTextureNames(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Util_getRealFullpath(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Util_findPaths(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Util_StrSplit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Util_GetNodeUesrStr(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Util_clearLabelKey(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Util_addLabelKey(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_AudioEngineHelper_class;
extern JSObject *jsb_AudioEngineHelper_prototype;

bool js_game_AudioEngineHelper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_game_AudioEngineHelper_finalize(JSContext *cx, JSObject *obj);
void js_register_game_AudioEngineHelper(JSContext *cx, JS::HandleObject global);
void register_all_game(JSContext* cx, JS::HandleObject obj);
bool js_game_AudioEngineHelper_lazyInit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_setCurrentTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_getVolume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_uncache(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_resumeAll(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_stopAll(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_pause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_end(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_getMaxAudioInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_getCurrentTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_setVolumeAll(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_PlayEffectT(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_setMaxAudioInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_isLoop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_pauseAll(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_uncacheAll(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_setVolume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_play2d(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_getState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_resume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_stop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_getDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_setLoop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_SetEffectVolume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_AudioEngineHelper_setFinishCallback(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_SafeSprite_class;
extern JSObject *jsb_SafeSprite_prototype;

bool js_game_SafeSprite_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_game_SafeSprite_finalize(JSContext *cx, JSObject *obj);
void js_register_game_SafeSprite(JSContext *cx, JS::HandleObject global);
void register_all_game(JSContext* cx, JS::HandleObject obj);
bool js_game_SafeSprite_getScriptID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_SafeSprite_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_SafeSprite_SafeSprite(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ReSprite_class;
extern JSObject *jsb_ReSprite_prototype;

bool js_game_ReSprite_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_game_ReSprite_finalize(JSContext *cx, JSObject *obj);
void js_register_game_ReSprite(JSContext *cx, JS::HandleObject global);
void register_all_game(JSContext* cx, JS::HandleObject obj);
bool js_game_ReSprite_isReSpriteFlipX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ReSprite_setReSpriteFlipX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ReSprite_initWithFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ReSprite_pointInSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ReSprite_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ReSprite_ReSprite(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_PlatformManager_class;
extern JSObject *jsb_PlatformManager_prototype;

bool js_game_PlatformManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_game_PlatformManager_finalize(JSContext *cx, JSObject *obj);
void js_register_game_PlatformManager(JSContext *cx, JS::HandleObject global);
void register_all_game(JSContext* cx, JS::HandleObject obj);
bool js_game_PlatformManager_reportNotification(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_getNetworkType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_createNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_getDeviceType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_getDeviceToken(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_getMacAddress(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_getDeviceName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_setLangueIdentify(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_setTextInPasteboard(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_getDeviceSystem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_logOutAndCallJS(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_DestoryPlatform(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_gameCall(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_getPlatformId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_getDeviceUid(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_getValueForKey(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_InitPlatform(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_getLangueIdentify(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_getDeviceUidType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_sharedFaceBook(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_getDeviceMemory(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_getAppVersion(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_loginSuccessAndCallJS(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_deleteAllNotification(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_reportEvent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_setValueForKey(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_PlatformManager_PlatformManager(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_HttpDownloadManager_class;
extern JSObject *jsb_HttpDownloadManager_prototype;

bool js_game_HttpDownloadManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_game_HttpDownloadManager_finalize(JSContext *cx, JSObject *obj);
void js_register_game_HttpDownloadManager(JSContext *cx, JS::HandleObject global);
void register_all_game(JSContext* cx, JS::HandleObject obj);
bool js_game_HttpDownloadManager_isInDownLoadList(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_HttpDownloadManager_setHttpRequest(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_HttpDownloadManager_stopAllHttpRequest(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_HttpDownloadManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_HttpDownloadManager_HttpDownloadManager(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CURLHelper_class;
extern JSObject *jsb_CURLHelper_prototype;

bool js_game_CURLHelper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_game_CURLHelper_finalize(JSContext *cx, JSObject *obj);
void js_register_game_CURLHelper(JSContext *cx, JS::HandleObject global);
void register_all_game(JSContext* cx, JS::HandleObject obj);
bool js_game_CURLHelper_getLocalFileSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_CURLHelper_getHttpString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_CURLHelper_downloadFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_CURLHelper_getDownloadFileSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_CURLHelper_getHttpHeader(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ProgressAction_class;
extern JSObject *jsb_ProgressAction_prototype;

bool js_game_ProgressAction_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_game_ProgressAction_finalize(JSContext *cx, JSObject *obj);
void js_register_game_ProgressAction(JSContext *cx, JS::HandleObject global);
void register_all_game(JSContext* cx, JS::HandleObject obj);
bool js_game_ProgressAction_initWithDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ProgressAction_setProgressActionCallback(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ProgressAction_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ProgressAction_ProgressAction(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_Account_class;
extern JSObject *jsb_Account_prototype;

bool js_game_Account_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_game_Account_finalize(JSContext *cx, JSObject *obj);
void js_register_game_Account(JSContext *cx, JS::HandleObject global);
void register_all_game(JSContext* cx, JS::HandleObject obj);
bool js_game_Account_getLoginUid(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Account_buy(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Account_center(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Account_doLoginGame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Account_switchAccount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Account_isLogin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Account_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Account_logout(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Account_clearLoginUid(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Account_exit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Account_login(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Account_doLogoutGame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Account_gameCall(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Account_platformCall(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Account_shareInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_Account_Account(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __game_h__
