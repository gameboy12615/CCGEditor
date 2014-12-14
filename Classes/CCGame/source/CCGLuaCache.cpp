#include "CCGLuaCache.h"

USING_NS_CC;

static CCGLuaCache *s_SharedLuaCache = nullptr;

CCGLuaCache* CCGLuaCache::getInstance()
{
	if (!s_SharedLuaCache)
	{
		s_SharedLuaCache = new (std::nothrow) CCGLuaCache();
		CCASSERT(s_SharedLuaCache, "FATAL: Not enough memory");
		s_SharedLuaCache->init();
	}

	return s_SharedLuaCache;
}

void CCGLuaCache::destroyInstance()
{
	CC_SAFE_RELEASE_NULL(s_SharedLuaCache);
}

bool CCGLuaCache::init()
{
	return true;
}

void CCGLuaCache::addScript(CCString *script, const std::string& name)
{
	_scripts.insert(name, script);
}

void CCGLuaCache::addScriptWithFile(const std::string& filename, const std::string& name)
{
#ifdef CCG_LUA_DEBUG
	addScriptPathWithFile(filename, name);
#else
	std::string filePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(filename);
	CCString* pstrFileContent = CCString::createWithContentsOfFile(filePath.c_str());
	if (pstrFileContent != nullptr)
	{
		addScript(pstrFileContent, name);
	}
	else
	{
		CCLOG("Script load failed : %s", filePath.c_str());
	}
#endif
}

void CCGLuaCache::removeScript(const std::string& name)
{
	if (name.size() == 0)
		return;

	_scripts.erase(name);
}

CCString* CCGLuaCache::getScript(const std::string& name)
{
	return _scripts.at(name);
}

void CCGLuaCache::addScriptPathWithFile(const std::string& filename, const std::string& name)
{
	std::string filePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(filename);
	_scriptPaths.insert(name, CCString::create(filePath));
}

void CCGLuaCache::removeScriptPath(const std::string& name)
{
	if (name.size() == 0)
		return;

	_scriptPaths.erase(name);
}

CCString* CCGLuaCache::getScriptPath(const std::string& name)
{
	return _scriptPaths.at(name);
}