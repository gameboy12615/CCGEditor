#pragma once

#include "cocos2d.h"   
#include "CCLuaEngine.h"
#include "CCGSprite.h"

extern "C" {
#include "lua.h"   
#include "lualib.h"   
#include "lauxlib.h"
};

NS_CC_BEGIN

class CCGLuaEngine : public Ref
{
public:
	struct LuaPosition
	{
		Vec2  pos;
		float angle;
	};

	static CCGLuaEngine* create(CCString *script, CCGSprite* sprite);
	static CCGLuaEngine* create(const char *scriptPath, CCGSprite* sprite);
	void callLuaStart();
	void callLuaUpdate(float delta);

private:
	virtual bool init(CCString *script, CCGSprite* sprite);
	virtual bool init(const char *scriptPath, CCGSprite* sprite);
	~CCGLuaEngine();

	CCPtr<LuaStack> _stack{ nullptr };
	lua_State* _ls  { nullptr };
	CCGSprite* _host{ nullptr };
};

NS_CC_END