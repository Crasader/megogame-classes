/**
 * @module game
 */
var cj = cj || {};

/**
 * @class GameSession
 */
cj.GameSession = {

/**
 * @method QueuePacket
 * @param {PacketBuff} arg0
 */
QueuePacket : function (
packetbuff 
)
{
},

/**
 * @method EndUpdateConnectingTick
 */
EndUpdateConnectingTick : function (
)
{
},

/**
 * @method BeginUpdateConnectingTick
 */
BeginUpdateConnectingTick : function (
)
{
},

/**
 * @method SendData
 * @param {unsigned int} arg0
 * @param {char} arg1
 * @param {unsigned int} arg2
 */
SendData : function (
int, 
char, 
int 
)
{
},

/**
 * @method sendCmd
 * @param {unsigned int} arg0
 */
sendCmd : function (
int 
)
{
},

/**
 * @method ReleaseGameSock
 */
ReleaseGameSock : function (
)
{
},

/**
 * @method EndUpdateTick
 */
EndUpdateTick : function (
)
{
},

/**
 * @method ConnectNewSock
 * @param {char} arg0
 * @param {unsigned int} arg1
 * @return {bool}
 */
ConnectNewSock : function (
char, 
int 
)
{
    return false;
},

/**
 * @method BeginUpdateTick
 */
BeginUpdateTick : function (
)
{
},

/**
 * @method IsActive
 * @return {bool}
 */
IsActive : function (
)
{
    return false;
},

/**
 * @method InitNet
 */
InitNet : function (
)
{
},

/**
 * @method Instance
 * @return {GameSession}
 */
Instance : function (
)
{
    return GameSession;
},

/**
 * @method SendRawData
 * @param {unsigned int} arg0
 * @param {CommonFnArgs} arg1
 */
SendRawData : function (
int, 
commonfnargs 
)
{
},

/**
 * @method InitDebuggerClient
 * @param {char} arg0
 */
InitDebuggerClient : function (
char 
)
{
},

/**
 * @method CloseNet
 */
CloseNet : function (
)
{
},

/**
 * @method GameSession
 * @constructor
 */
GameSession : function (
)
{
},

};

/**
 * @class Util
 */
cj.Util = {

/**
 * @method GetCcPositionTextureColor_noMVP_vert
 * @return {String}
 */
GetCcPositionTextureColor_noMVP_vert : function (
)
{
    return ;
},

/**
 * @method getSavedPath
 * @return {String}
 */
getSavedPath : function (
)
{
    return ;
},

/**
 * @method createFile
 * @param {String} arg0
 * @param {String} arg1
 * @return {bool}
 */
createFile : function (
str, 
str 
)
{
    return false;
},

/**
 * @method isFileParentCreated
 * @param {String} arg0
 * @return {bool}
 */
isFileParentCreated : function (
str 
)
{
    return false;
},

/**
 * @method closeKeyBoard
 * @param {cc.Node} arg0
 */
closeKeyBoard : function (
node 
)
{
},

/**
 * @method loopFiles
 * @param {String} arg0
 * @return {Array}
 */
loopFiles : function (
str 
)
{
    return new Array();
},

/**
 * @method GetCcPositionTextureColor_vert
 * @return {String}
 */
GetCcPositionTextureColor_vert : function (
)
{
    return ;
},

/**
 * @method getAllTextureNames
 * @return {Array}
 */
getAllTextureNames : function (
)
{
    return new Array();
},

/**
 * @method getRealFullpath
 * @param {String} arg0
 * @return {String}
 */
getRealFullpath : function (
str 
)
{
    return ;
},

/**
 * @method findPaths
 * @param {String} arg0
 * @param {String} arg1
 * @return {Array}
 */
findPaths : function (
str, 
str 
)
{
    return new Array();
},

/**
 * @method StrSplit
 * @param {String} arg0
 * @param {String} arg1
 * @param {Array} arg2
 */
StrSplit : function (
str, 
str, 
array 
)
{
},

/**
 * @method GetNodeUesrStr
 * @param {cc.Node} arg0
 * @return {String}
 */
GetNodeUesrStr : function (
node 
)
{
    return ;
},

/**
 * @method clearLabelKey
 */
clearLabelKey : function (
)
{
},

/**
 * @method addLabelKey
 * @param {String} arg0
 * @param {String} arg1
 */
addLabelKey : function (
str, 
str 
)
{
},

};

/**
 * @class AudioEngineHelper
 */
cj.AudioEngineHelper = {

/**
 * @method lazyInit
 * @return {bool}
 */
lazyInit : function (
)
{
    return false;
},

/**
 * @method setCurrentTime
 * @param {int} arg0
 * @param {float} arg1
 * @return {bool}
 */
setCurrentTime : function (
int, 
float 
)
{
    return false;
},

/**
 * @method getVolume
 * @param {int} arg0
 * @return {float}
 */
getVolume : function (
int 
)
{
    return 0;
},

/**
 * @method uncache
 * @param {String} arg0
 */
uncache : function (
str 
)
{
},

/**
 * @method resumeAll
 */
resumeAll : function (
)
{
},

/**
 * @method stopAll
 */
stopAll : function (
)
{
},

/**
 * @method pause
 * @param {int} arg0
 */
pause : function (
int 
)
{
},

/**
 * @method end
 */
end : function (
)
{
},

/**
 * @method getMaxAudioInstance
 * @return {int}
 */
getMaxAudioInstance : function (
)
{
    return 0;
},

/**
 * @method getCurrentTime
 * @param {int} arg0
 * @return {float}
 */
getCurrentTime : function (
int 
)
{
    return 0;
},

/**
 * @method setVolumeAll
 * @param {float} arg0
 */
setVolumeAll : function (
float 
)
{
},

/**
 * @method PlayEffectT
 * @param {char} arg0
 * @return {int}
 */
PlayEffectT : function (
char 
)
{
    return 0;
},

/**
 * @method setMaxAudioInstance
 * @param {int} arg0
 * @return {bool}
 */
setMaxAudioInstance : function (
int 
)
{
    return false;
},

/**
 * @method isLoop
 * @param {int} arg0
 * @return {bool}
 */
isLoop : function (
int 
)
{
    return false;
},

/**
 * @method pauseAll
 */
pauseAll : function (
)
{
},

/**
 * @method uncacheAll
 */
uncacheAll : function (
)
{
},

/**
 * @method setVolume
 * @param {int} arg0
 * @param {float} arg1
 */
setVolume : function (
int, 
float 
)
{
},

/**
 * @method play2d
 * @param {String} arg0
 * @param {bool} arg1
 * @param {float} arg2
 * @return {int}
 */
play2d : function (
str, 
bool, 
float 
)
{
    return 0;
},

/**
 * @method getState
 * @param {int} arg0
 * @return {cc.experimental::AudioEngine::AudioState}
 */
getState : function (
int 
)
{
    return 0;
},

/**
 * @method resume
 * @param {int} arg0
 */
resume : function (
int 
)
{
},

/**
 * @method stop
 * @param {int} arg0
 */
stop : function (
int 
)
{
},

/**
 * @method getDuration
 * @param {int} arg0
 * @return {float}
 */
getDuration : function (
int 
)
{
    return 0;
},

/**
 * @method setLoop
 * @param {int} arg0
 * @param {bool} arg1
 */
setLoop : function (
int, 
bool 
)
{
},

/**
 * @method SetEffectVolume
 * @param {float} arg0
 */
SetEffectVolume : function (
float 
)
{
},

/**
 * @method setFinishCallback
 * @param {int} arg0
 */
setFinishCallback : function (
int 
)
{
},

};

/**
 * @class SafeSprite
 */
cj.SafeSprite = {

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
 * @method create
 * @return {SafeSprite}
 */
create : function (
)
{
    return SafeSprite;
},

/**
 * @method SafeSprite
 * @constructor
 */
SafeSprite : function (
)
{
},

};

/**
 * @class ReSprite
 */
cj.ReSprite = {

/**
 * @method isReSpriteFlipX
 * @return {bool}
 */
isReSpriteFlipX : function (
)
{
    return false;
},

/**
 * @method setReSpriteFlipX
 * @param {bool} arg0
 */
setReSpriteFlipX : function (
bool 
)
{
},

/**
 * @method initWithFile
 * @param {String} arg0
 * @return {bool}
 */
initWithFile : function (
str 
)
{
    return false;
},

/**
 * @method pointInSprite
 * @param {vec2_object} arg0
 * @return {bool}
 */
pointInSprite : function (
vec2 
)
{
    return false;
},

/**
 * @method create
 * @param {String} arg0
 * @return {ReSprite}
 */
create : function (
str 
)
{
    return ReSprite;
},

/**
 * @method ReSprite
 * @constructor
 */
ReSprite : function (
)
{
},

};

/**
 * @class PlatformManager
 */
cj.PlatformManager = {

/**
 * @method reportNotification
 * @param {String} arg0
 */
reportNotification : function (
str 
)
{
},

/**
 * @method getNetworkType
 * @return {NetworkType}
 */
getNetworkType : function (
)
{
    return NetworkType;
},

/**
 * @method createNode
 * @param {String} arg0
 * @return {cc.Node}
 */
createNode : function (
str 
)
{
    return cc.Node;
},

/**
 * @method getDeviceType
 * @return {String}
 */
getDeviceType : function (
)
{
    return ;
},

/**
 * @method getDeviceToken
 * @return {String}
 */
getDeviceToken : function (
)
{
    return ;
},

/**
 * @method getMacAddress
 * @return {String}
 */
getMacAddress : function (
)
{
    return ;
},

/**
 * @method getInstance
 * @return {PlatformManager}
 */
getInstance : function (
)
{
    return PlatformManager;
},

/**
 * @method getDeviceName
 * @return {String}
 */
getDeviceName : function (
)
{
    return ;
},

/**
 * @method setLangueIdentify
 * @param {String} arg0
 */
setLangueIdentify : function (
str 
)
{
},

/**
 * @method setTextInPasteboard
 * @param {String} arg0
 */
setTextInPasteboard : function (
str 
)
{
},

/**
 * @method getDeviceSystem
 * @return {String}
 */
getDeviceSystem : function (
)
{
    return ;
},

/**
 * @method logOutAndCallJS
 */
logOutAndCallJS : function (
)
{
},

/**
 * @method DestoryPlatform
 */
DestoryPlatform : function (
)
{
},

/**
 * @method gameCall
 * @param {String} arg0
 * @param {String} arg1
 */
gameCall : function (
str, 
str 
)
{
},

/**
 * @method getPlatformId
 * @return {int}
 */
getPlatformId : function (
)
{
    return 0;
},

/**
 * @method getDeviceUid
 * @return {String}
 */
getDeviceUid : function (
)
{
    return ;
},

/**
 * @method getValueForKey
 * @param {String} arg0
 * @return {String}
 */
getValueForKey : function (
str 
)
{
    return ;
},

/**
 * @method InitPlatform
 */
InitPlatform : function (
)
{
},

/**
 * @method getLangueIdentify
 * @return {String}
 */
getLangueIdentify : function (
)
{
    return ;
},

/**
 * @method getDeviceUidType
 * @return {String}
 */
getDeviceUidType : function (
)
{
    return ;
},

/**
 * @method sharedFaceBook
 * @param {String} arg0
 */
sharedFaceBook : function (
str 
)
{
},

/**
 * @method getDeviceMemory
 * @return {String}
 */
getDeviceMemory : function (
)
{
    return ;
},

/**
 * @method getAppVersion
 * @return {String}
 */
getAppVersion : function (
)
{
    return ;
},

/**
 * @method loginSuccessAndCallJS
 * @param {Array} arg0
 */
loginSuccessAndCallJS : function (
array 
)
{
},

/**
 * @method deleteAllNotification
 */
deleteAllNotification : function (
)
{
},

/**
 * @method reportEvent
 * @param {String} arg0
 */
reportEvent : function (
str 
)
{
},

/**
 * @method setValueForKey
 * @param {String} arg0
 * @param {String} arg1
 */
setValueForKey : function (
str, 
str 
)
{
},

/**
 * @method PlatformManager
 * @constructor
 */
PlatformManager : function (
)
{
},

};

/**
 * @class HttpDownloadManager
 */
cj.HttpDownloadManager = {

/**
 * @method isInDownLoadList
 * @param {String} arg0
 * @return {bool}
 */
isInDownLoadList : function (
str 
)
{
    return false;
},

/**
 * @method setHttpRequest
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @param {bool} arg3
 * @return {bool}
 */
setHttpRequest : function (
str, 
str, 
str, 
bool 
)
{
    return false;
},

/**
 * @method stopAllHttpRequest
 */
stopAllHttpRequest : function (
)
{
},

/**
 * @method getInstance
 * @return {HttpDownloadManager}
 */
getInstance : function (
)
{
    return HttpDownloadManager;
},

/**
 * @method HttpDownloadManager
 * @constructor
 */
HttpDownloadManager : function (
)
{
},

};

/**
 * @class CURLHelper
 */
cj.CURLHelper = {

/**
 * @method getLocalFileSize
 * @param {String} arg0
 * @return {long}
 */
getLocalFileSize : function (
str 
)
{
    return 0;
},

/**
 * @method getHttpString
 * @param {String} arg0
 * @return {String}
 */
getHttpString : function (
str 
)
{
    return ;
},

/**
 * @method downloadFile
 * @param {String} arg0
 * @param {String} arg1
 * @return {int}
 */
downloadFile : function (
str, 
str 
)
{
    return 0;
},

/**
 * @method getDownloadFileSize
 * @param {String} arg0
 * @return {long}
 */
getDownloadFileSize : function (
str 
)
{
    return 0;
},

/**
 * @method getHttpHeader
 * @param {String} arg0
 * @return {String}
 */
getHttpHeader : function (
str 
)
{
    return ;
},

};

/**
 * @class ProgressAction
 */
cj.ProgressAction = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @param {function} arg3
 * @return {bool}
 */
initWithDuration : function (
float, 
float, 
float, 
func 
)
{
    return false;
},

/**
 * @method setProgressActionCallback
 * @param {function} arg0
 */
setProgressActionCallback : function (
func 
)
{
},

/**
 * @method create
* @param {float|float} float
* @param {float|float} float
* @param {float|float} float
* @param {function} func
* @return {ProgressAction|ProgressAction}
*/
create : function(
float,
float,
float,
func 
)
{
    return ProgressAction;
},

/**
 * @method ProgressAction
 * @constructor
 */
ProgressAction : function (
)
{
},

};

/**
 * @class Account
 */
cj.Account = {

/**
 * @method getLoginUid
 * @return {String}
 */
getLoginUid : function (
)
{
    return ;
},

/**
 * @method buy
 * @param {String} arg0
 */
buy : function (
str 
)
{
},

/**
 * @method center
 */
center : function (
)
{
},

/**
 * @method doLoginGame
 * @param {String} arg0
 */
doLoginGame : function (
str 
)
{
},

/**
 * @method switchAccount
 */
switchAccount : function (
)
{
},

/**
 * @method isLogin
 * @return {bool}
 */
isLogin : function (
)
{
    return false;
},

/**
 * @method init
 */
init : function (
)
{
},

/**
 * @method logout
 */
logout : function (
)
{
},

/**
 * @method clearLoginUid
 */
clearLoginUid : function (
)
{
},

/**
 * @method exit
 * @return {bool}
 */
exit : function (
)
{
    return false;
},

/**
 * @method login
 */
login : function (
)
{
},

/**
 * @method doLogoutGame
 */
doLogoutGame : function (
)
{
},

/**
 * @method gameCall
 * @param {String} arg0
 * @param {String} arg1
 * @return {String}
 */
gameCall : function (
str, 
str 
)
{
    return ;
},

/**
 * @method platformCall
 * @param {String} arg0
 * @param {String} arg1
 * @return {String}
 */
platformCall : function (
str, 
str 
)
{
    return ;
},

/**
 * @method shareInstance
 * @return {Account}
 */
shareInstance : function (
)
{
    return Account;
},

/**
 * @method Account
 * @constructor
 */
Account : function (
)
{
},

};
