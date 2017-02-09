//
//  js_cpp_export.h
//  MegoGame
//
//  Created by howe on 15/3/6.
//
//

#ifndef __MegoGame__js_cpp_export__
#define __MegoGame__js_cpp_export__

#include <stdio.h>
#include <map>
#include <string>
#include <math.h>
/**/
#include "dragonbones/DragonBonesHeaders.h"
#include "dragonbones/renderer/cocos2d-x-3.x/DBCCRenderHeaders.h"

#include "net/GameSession.h"

#include "Defines.h"

#include "common/Util.h"

#include "common/SafeSprite.h"

#include "platform/PlatformManager.h"

#include "resLoader/HttpDownloadManager.h"
#include "resLoader/CURLHelper.h"

#include "ctmAction/ProgressAction.h"
#include "loginSystem/Account.h"
//#include "ReSprite/ReSprite.h"

/* */
#define target_namespace  "cj" //

#define classes    "GameSession Util AudioEngineHelper PlatformManager SafeSprite HttpDownloadManager CURLHelper ProgressAction Account ReSprite"

#define classes_have_no_parents     "GameSession PlatformManager AudioEngineHelper HttpDownloadManager CURLHelper"

#endif /* defined(__MegoGame__js_cpp_export__) */
