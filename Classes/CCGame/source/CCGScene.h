#pragma once

#include "cocos2d.h"
#include "CCPtr.h"
#include "CCGSprite.h"
#include "CCGCharacter.h"
#include "CCGVirtualJoystick.h"

NS_CC_BEGIN

class CCGSprite;

class CCGScene : public Scene
{
public:

	class PlayLayer : public cocos2d::Layer
	{

	};

	class GUILayer : public cocos2d::Layer
	{

	};

	CCGScene();
	virtual ~CCGScene();

	/** creators group */
	static CCGScene *create();
	static CCGScene *createWithSize(const Size& size);
#if CC_USE_PHYSICS
	static CCGScene *createWithPhysics();
#endif

	/** override addChild */
	virtual void addChild(Node * child) override;

	/** add GUI */
	virtual void addGUIChild(Node * child);

	/** stores player and enemy to array */
	void addPlayer(Node * child);
	Vector<CCGCharacter*>& getPlayers() { return _players; }
	void addEnemy(Node * child);
	Vector<CCGCharacter*>& getEnemies() { return _enemies; }
	void addCharacter(Node * child);

	/** enable scene functions */
	void enableFTGCameraTouchable(bool enable);
	void enableVirtualJoystick(bool enable);

	/** get scene elements */
	Camera* getCamera() { return _defaultCCGCamera.get(); }
	CCGVirtualJoystick* getVirtualJoystick() { return _defaultVirtualJoystick.get(); }
	float getGround() { return _ground; }
	Rect& getScreenBoundingBox() { return _screenBoundingBox; }

protected:

	CCPtr<Camera> _defaultCCGCamera { nullptr };
	CCPtr<Camera> _defaultGUICamera { nullptr };
	CCPtr<EventListenerTouchAllAtOnce> _defaultCameraListener { nullptr };
	CCPtr<CCGVirtualJoystick> _defaultVirtualJoystick { nullptr };
	Vector<CCGSprite*> _CCGSprites;
	Vector<CCGCharacter*> _players; // include players and friend robots.
	Vector<CCGCharacter*> _enemies;
	float _ground{ 0.0f };
	Rect  _screenBoundingBox;

	/** init additional */
	bool initAdditional(void);
	void initDefaultCameras(void);

	/** callbacks */
	void onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event *event);
	void updateCollision(float fDelta);

	/** other functions */
	void checkCollision(CCGCharacter* victim, CCGCharacter* attacker);
};

NS_CC_END