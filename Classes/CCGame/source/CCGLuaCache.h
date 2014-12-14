#pragma once

#include "cocos2d.h"
#include "CCGLuaEngine.h"
#include "CCGConfig.h"

NS_CC_BEGIN

class CCGLuaCache : public Ref
{
public:

	/** Returns the shared instance of the Lua cache */
	static CCGLuaCache* getInstance();
	static void destroyInstance();
	bool init(void);

	/** Adds a lua script with a name.
	*/
	void addScript(CCString *script, const std::string& name);
	void addScriptWithFile(const std::string& filename, const std::string& name);
	void removeScript(const std::string& name);
	CCString* getScript(const std::string& name);

	/** Adds a lua script path with a name.
	*/
	void addScriptPathWithFile(const std::string& filename, const std::string& name);
	void removeScriptPath(const std::string& name);
	CCString* getScriptPath(const std::string& name);

protected:
	Map<std::string, CCString*> _scripts;
	Map<std::string, CCString*> _scriptPaths;
};

NS_CC_END