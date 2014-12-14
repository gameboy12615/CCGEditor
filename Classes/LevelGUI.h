#pragma once

#include "cocos2d.h"
#include "CCSTG.h"

NS_CC_BEGIN

class LevelGUI : public cocos2d::Layer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(LevelGUI);

	void update(float delta);

protected:
	CCPtr<LabelTTF> _debugInfo;
};

NS_CC_END