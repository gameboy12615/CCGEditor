#pragma once

#include "cocos2d.h"

NS_CC_BEGIN

#ifndef CCG_COLLISION_BOX_DEBUG_DRAW
#define CCG_COLLISION_BOX_DEBUG_DRAW 1
#endif

#ifndef CCG_USE_COLLISION_BOX
#define CCG_USE_COLLISION_BOX 1
#endif

#ifndef CCG_LUA_DEBUG
#define CCG_LUA_DEBUG 1
#endif

class CCGConfig
{
public:

	static CCGConfig* getInstance();
	virtual bool init();

	/** game configs */
	CC_SYNTHESIZE(float, _nearDistance, NearDistance);
};

NS_CC_END