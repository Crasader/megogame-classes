//
//  GameDefines.h
//  MegoGame
//
//  Created by howe on 15/3/9.
//
//

#ifndef __MegoGame__GameDefines__
#define __MegoGame__GameDefines__

#include <stdio.h>
#include "cocos2d.h"
#include "../Defines.h"
USING_NS_CC;



#define YLJ_LOG( fmt, ... )             CCLOG( fmt, ##__VA_ARGS__ )
#define YLJ_ERROR( fmt, ... )           CCLOGERROR( fmt, ##__VA_ARGS__ )
#define YLJ_DEBUG( fmt, ... )           CCLOG( fmt, ##__VA_ARGS__ )
#define YLJ_SYSTEM_ERROR( a, fmt, ... ) CCLOG( fmt, __VA_ARGS__ )

#define ASSERTH  CC_ASSERT


#endif /* defined(__MegoGame__GameDefines__) */
