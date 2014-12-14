#include "CCGLuaEngine.h"

USING_NS_CC;

CCGLuaEngine* CCGLuaEngine::create(CCString *script, CCGSprite* sprite)
{
	CCGLuaEngine *luaHandle = new (std::nothrow) CCGLuaEngine();
	if (luaHandle && luaHandle->init(script, sprite))
	{
		luaHandle->autorelease();
		return luaHandle;
	}
	CC_SAFE_DELETE(luaHandle);
	return nullptr;
}

CCGLuaEngine* CCGLuaEngine::create(const char *scriptPath, CCGSprite* sprite)
{
	CCGLuaEngine *luaHandle = new (std::nothrow) CCGLuaEngine();
	if (luaHandle && luaHandle->init(scriptPath, sprite))
	{
		luaHandle->autorelease();
		return luaHandle;
	}
	CC_SAFE_DELETE(luaHandle);
	return nullptr;
}

CCGLuaEngine::~CCGLuaEngine()
{
	_stack = nullptr;
	_ls    = nullptr;
	_host  = nullptr;
}

bool CCGLuaEngine::init(CCString *script, CCGSprite* sprite)
{
	_stack = LuaStack::create();
	_ls = _stack->getLuaState();
	_host = sprite;

	const char* code = script->getCString();
	int isopen = luaL_dostring(_ls, code);
	if (isopen != 0)
	{
		CCLOG("%s load fail", code);
		return false;
	}

	return true;
}

bool CCGLuaEngine::init(const char *scriptPath, CCGSprite* sprite)
{
	CCString* script = CCString::createWithContentsOfFile(std::string(scriptPath));
	return init(script, sprite);
}

void CCGLuaEngine::callLuaStart()
{
	if (_host != nullptr && _ls != nullptr)
	{
		LuaPosition position;
		position.pos = _host->getPosition();
		position.angle = _host->getRotation();

		lua_getglobal(_ls, "start");

		/** start position */
		lua_newtable(_ls);
		/** start pos */
		lua_newtable(_ls);
		lua_pushnumber(_ls, position.pos.x);
		lua_setfield(_ls, -2, "x");
		lua_pushnumber(_ls, position.pos.y);
		lua_setfield(_ls, -2, "y");
		/** end pos */
		lua_setfield(_ls, -2, "pos");
		lua_pushnumber(_ls, position.angle);
		lua_setfield(_ls, -2, "angle");
		/** end position */

		lua_call(_ls, 1, 0);

		/** clear stack */
		lua_settop(_ls, 0);
	}
}

void CCGLuaEngine::callLuaUpdate(float delta)
{
	if (_host != nullptr && _ls != nullptr)
	{
		lua_getglobal(_ls, "update");
		lua_pushnumber(_ls, delta);

		lua_call(_ls, 1, 0);

		LuaPosition position;
		/** start position */
		lua_getglobal(_ls, "position");
		/** start pos */
		lua_pushstring(_ls, "pos");
		lua_gettable(_ls, -2);
		lua_pushstring(_ls, "x");
		lua_gettable(_ls, -2);
		position.pos.x = lua_tonumber(_ls, -1);
		lua_pop(_ls, 1);
		lua_pushstring(_ls, "y");
		lua_gettable(_ls, -2);
		position.pos.y = lua_tonumber(_ls, -1);
		lua_pop(_ls, 2);
		/** end pos */
		lua_pushstring(_ls, "angle");
		lua_gettable(_ls, -2);
		position.angle = lua_tonumber(_ls, -1);
		/** end position */
		/** clear stack */
		lua_settop(_ls, 0);

		_host->setPosition(position.pos);
		_host->setRotation(position.angle);
	}
}