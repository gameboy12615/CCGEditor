#pragma once

#include "cocos2d.h"
#include "CCPtr.h"
#include "external/SneakyJoystick/SneakyButton.h"
#include "external/SneakyJoystick/SneakyButtonSkinnedBase.h"
#include "external/SneakyJoystick/SneakyJoystick.h"
#include "external/SneakyJoystick/SneakyJoystickSkinnedBase.h"

NS_CC_BEGIN

class CCGJoystick : public SneakyJoystick
{

};

class CCGButton : public SneakyButton
{

};

class CCGVirtualJoystick : public Layer
{
public:
	CCGVirtualJoystick();
	virtual ~CCGVirtualJoystick();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(CCGVirtualJoystick);

	// access functions
	CCGJoystick* getLeftJoystick() { return _leftJoystick.get(); }
	CCGButton*   getAttackButton() { return _attackButton.get(); }

protected:
	CCPtr<CCGJoystick> _leftJoystick;
	CCPtr<CCGButton> _attackButton;
};

NS_CC_END