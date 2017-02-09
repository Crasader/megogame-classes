//
//  Common.h
//  MegoGame
//
//  Created by howe on 15/4/3.
//
//

#ifndef __MegoGame__Common__
#define __MegoGame__Common__

#include <stdio.h>
#include "jsapi.h"


void init_custom_jsb();

void __register_custom_jsb_all(JSContext* cx, JS::HandleObject obj);


#endif /* defined(__MegoGame__Common__) */
