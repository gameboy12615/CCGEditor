#pragma once

#include "cocos2d.h"
#include "CCGSprite.h"
#include "CCGLuaEngine.h"
#include "CCGDataCache.h"
#include "CCPtr.h"

NS_CC_BEGIN

class CCGLuaEngine;

struct SpellData : public CCGData
{
	Point			startPosition;
	float			duration{ 0.0f }; // 0 means persist until out of the screen or the animation is over.
	bool			canDestory{ true };
	std::string     scriptName;
};

class CCGSpell : public CCGSprite, public Clonable
{
	friend class CCGLuaEngine;

public:

	CCGSpell(void);
	virtual ~CCGSpell(void);

	void setDuration(float duration) { _duration = duration; }
	void runLuaScript(std::string scriptName);
	void dettachLuaScript();
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;
	void onDraw(const Mat4 &transform, uint32_t flags);

protected:
	/** init additional */
	virtual bool initAdditional(void);

	/** loacl callback functions */
	void update(float delta);

	float _duration;
	bool  _canDestory;
	CCPtr<CCGLuaEngine> _luaHandle{ nullptr };
	GLProgram* _pShaderProgram{ nullptr };
};

NS_CC_END