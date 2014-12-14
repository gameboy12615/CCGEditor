#include "CCGVirtualJoystick.h"

USING_NS_CC;

CCGVirtualJoystick::CCGVirtualJoystick()
{

}

CCGVirtualJoystick::~CCGVirtualJoystick()
{
	removeAllChildren();
}

// on "init" you need to initialize your instance
bool CCGVirtualJoystick::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	// set joystick params.
	float defaultThumbRadius = 64;
	float defaultBackgroundRadius = 100;
	float defaultDeathRadius = 10;
	Vec2  defaultJoystickPosition = Vec2(200, 200);

	_leftJoystick = static_cast<CCGJoystick*>(new SneakyJoystick());
	_leftJoystick->initWithRect(Rect::ZERO);
	_leftJoystick->setAutoCenter(true);  
	_leftJoystick->setHasDeadzone(true);
	_leftJoystick->setDeadRadius(defaultDeathRadius);

	SneakyJoystickSkinnedBase *leftJoystickSkin = new SneakyJoystickSkinnedBase();
	leftJoystickSkin->autorelease();
	leftJoystickSkin->init();

	// set background sprite
	leftJoystickSkin->setBackgroundSprite(CCSprite::create("joystick/RadialJoy_Area.png"));
	auto backgroundSpriteSize = leftJoystickSkin->getBackgroundSprite()->getContentSize();
	leftJoystickSkin->getBackgroundSprite()->setScaleX(2* defaultBackgroundRadius / backgroundSpriteSize.width);
	leftJoystickSkin->getBackgroundSprite()->setScaleY(2* defaultBackgroundRadius / backgroundSpriteSize.height);

	// set thumb sprite
	leftJoystickSkin->setThumbSprite(CCSprite::create("joystick/Button_normal.png"));
	auto thumbSpriteSize = leftJoystickSkin->getThumbSprite()->getContentSize();
	leftJoystickSkin->getThumbSprite()->setScaleX(2 * defaultThumbRadius / thumbSpriteSize.width);
	leftJoystickSkin->getThumbSprite()->setScaleY(2 * defaultThumbRadius / thumbSpriteSize.height);

	leftJoystickSkin->setPosition(defaultJoystickPosition);
	leftJoystickSkin->setJoystick(_leftJoystick.get());
	this->addChild(leftJoystickSkin);

	// create attack button
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2  defaultAttackButtonPosition = Vec2(visibleSize.width - 200, 200);

	_attackButton = static_cast<CCGButton*>(new SneakyButton());
	_attackButton->initWithRect(Rect::ZERO);
	_attackButton->setIsToggleable(false);
	_attackButton->setIsHoldable(false);

	SneakyButtonSkinnedBase *attackButtonSkin = new SneakyButtonSkinnedBase();
	attackButtonSkin->autorelease();
	attackButtonSkin->init();

	attackButtonSkin->setDefaultSprite(CCSprite::create("joystick/attackButton_normal.png"));
	attackButtonSkin->setPressSprite(CCSprite::create("joystick/attackButton_pressed.png"));
	attackButtonSkin->setActivatedSprite(CCSprite::create("joystick/attackButton_pressed.png"));

	attackButtonSkin->setPosition(defaultAttackButtonPosition);
	attackButtonSkin->setButton(_attackButton.get());
	this->addChild(attackButtonSkin);

	return true;
}
