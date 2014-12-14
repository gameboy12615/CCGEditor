#include "CCGScene.h"
#include "CCGConfig.h"

USING_NS_CC;

CCGScene::CCGScene()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// create default FTG camera
	_defaultCCGCamera = Camera::createPerspective(60, visibleSize.width / visibleSize.height, 1, 5000);
	addChild(_defaultCCGCamera.get());

	// create default GUI camera
	_defaultGUICamera = Camera::createOrthographic(visibleSize.width, visibleSize.height, -1024, 1024);
	addGUIChild(_defaultGUICamera.get());

	// temp define
	_ground = -200;
	_screenBoundingBox = Rect(-visibleSize.width / 2, -visibleSize.height / 2, visibleSize.width, visibleSize.height);
}

CCGScene::~CCGScene()
{
	removeAllChildren();
}

CCGScene* CCGScene::create()
{
	CCGScene *ret = new (std::nothrow) CCGScene();
	if (ret && ret->init())
	{
		ret->initAdditional();
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

CCGScene* CCGScene::createWithSize(const Size& size)
{
	CCGScene *ret = new (std::nothrow) CCGScene();
	if (ret && ret->initWithSize(size))
	{
		ret->initAdditional();
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

#if CC_USE_PHYSICS
CCGScene* CCGScene::createWithPhysics()
{
	CCGScene *ret = new (std::nothrow) CCGScene();
	if (ret && ret->initWithPhysics())
	{
		ret->initAdditional();
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}
#endif

void CCGScene::addChild(Node * child)
{
	Node::addChild(child);
	child->setCameraMask((unsigned short)CameraFlag::USER1);
	addCharacter(child);
}

void CCGScene::addPlayer(Node * child)
{
	CCGCharacter* player = dynamic_cast<CCGCharacter*>(child);
	if (player != nullptr)
	{
		_players.pushBack(player);
	}
}

void CCGScene::addEnemy(Node * child)
{
	CCGCharacter* enemy = dynamic_cast<CCGCharacter*>(child);
	if (enemy != nullptr)
	{
		_enemies.pushBack(enemy);
	}
}

void CCGScene::addCharacter(Node * child)
{
	/** check and add character */
	CCGCharacter* chara = dynamic_cast<CCGCharacter*>(child);
	if (chara != nullptr)
	{
		if (chara->isPlayer())
		{
			addPlayer(child);
		}
		else
		{
			addEnemy(child);
		}
	}

	for (auto subChild : child->getChildren())
	{
		addCharacter(subChild);
	}
}

void CCGScene::addGUIChild(Node * child)
{
	Node::addChild(child);
	child->setCameraMask((unsigned short)CameraFlag::USER2);
}

void CCGScene::enableFTGCameraTouchable(bool enable)
{
	if (enable == true)
	{
		// create camera listener
		if (_defaultCameraListener != nullptr) return;
		_defaultCameraListener = EventListenerTouchAllAtOnce::create();
		_defaultCameraListener->onTouchesMoved = CC_CALLBACK_2(CCGScene::onTouchesMoved, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(_defaultCameraListener.get(), this);
	}
	else
	{
		if (_defaultCameraListener != nullptr)
		{
			_eventDispatcher->removeEventListener(_defaultCameraListener.get());
			_defaultCameraListener = nullptr;
		}
	}
}

void CCGScene::enableVirtualJoystick(bool enable)
{
	if (enable == true)
	{
		// create default virtual joystick
		if (_defaultVirtualJoystick != nullptr)	return;
		_defaultVirtualJoystick = CCGVirtualJoystick::create();
		addGUIChild(_defaultVirtualJoystick.get());
	}
	else
	{
		if (_defaultVirtualJoystick != nullptr)
		{
			removeChild(_defaultVirtualJoystick.get());
			_defaultVirtualJoystick = nullptr;
		}
	}
}

bool CCGScene::initAdditional(void)
{
	initDefaultCameras();
	schedule(schedule_selector(CCGScene::updateCollision), 0.0f);

	return true;
}

void CCGScene::initDefaultCameras(void)
{
	if (_defaultCCGCamera != nullptr)
	{
		// init default FTG camera
		_defaultCCGCamera->setCameraFlag(CameraFlag::USER1);
		_defaultCCGCamera->lookAt(Vec3(0, 0, 0), Vec3(0, 1, 0));
		_defaultCCGCamera->setPosition3D(Vec3(0, 0, 500));
	}

	if (_defaultGUICamera != nullptr)
	{
		// init default GUI camera
		_defaultGUICamera->setCameraFlag(CameraFlag::USER2);
		_defaultGUICamera->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));
		_defaultGUICamera->setRotation3D(Vec3(0.f, 0.f, 0.f));
	}
}

void CCGScene::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event *event)
{
	if (_defaultCCGCamera != nullptr)
	{
		if (touches.size() == 1)
		{
			auto touch = touches[0];
			_defaultCCGCamera->setPosition3D(_defaultCCGCamera->getPosition3D() + Vec3(-touch->getDelta().x, -touch->getDelta().y, 0));
		}
		else if (touches.size() == 2)
		{
			auto touch1 = touches[0];
			auto touch2 = touches[1];
			auto prevDist = (touch1->getPreviousLocation() - touch2->getPreviousLocation()).length();
			auto dist = (touch1->getLocation() - touch2->getLocation()).length();
			auto deltaDist = dist - prevDist;
			_defaultCCGCamera->setPositionZ(_defaultCCGCamera->getPositionZ() - deltaDist);
		}
	}
}

void CCGScene::updateCollision(float fDelta)
{
	for (auto player : getPlayers())
	{
		if (player == nullptr) continue;
		player->setNear(false);
		for (auto enemy : getEnemies())
		{
			if (enemy == nullptr) continue;
			checkCollision(player, enemy);
			checkCollision(enemy, player);
			player->checkNear(enemy);
		}
	}

	for (auto enemy : getEnemies())
	{
		if (enemy == nullptr) continue;
		enemy->setNear(false);
		for (auto player : getPlayers())
		{
			enemy->checkNear(player);
		}
	}
}

void CCGScene::checkCollision(CCGCharacter* victim, CCGCharacter* attacker)
{
#if CCG_USE_COLLISION_BOX
	if (victim == nullptr || attacker == nullptr || victim == attacker) return;

	CCGSpriteFrame* victimCurFrame = victim->getCurrentFrame();
	CCGSpriteFrame* attackerCurFrame = attacker->getCurrentFrame();
	if (victimCurFrame == nullptr || attackerCurFrame == nullptr) return;

	/** if one victimBodyBox collided with one attackerAttackBox, call onHit() callback */
	/** generally, each frame only have one body box */
	for (auto victimBodyBox : victimCurFrame->getBodyBoxes())
	{
		if (victimBodyBox == nullptr) continue;
		bool bHit = false;
		Rect victimBodyRect = victimBodyBox->getWorldBox(victim);
		
		/** check collision with attacker attack box */
		for (auto attackerAttackBox : attackerCurFrame->getAttackBoxes())
		{
			if (attackerAttackBox == nullptr) continue;
			Rect attackerAttackRect = attackerAttackBox->getWorldBox(attacker);
			if (victimBodyRect.intersectsRect(attackerAttackRect))
			{
				CCGAnimation* attackerCurAnimation = attacker->getCurrentAnimation();
				if (attackerCurAnimation != nullptr)
				{
					victim->onHit(attackerCurAnimation->getAttackInfo());
				}
				bHit = true;
				break;
			}
		}

		/** check collison with attacker spells */
		for (auto spell : attacker->getSpells())
		{
			if (spell == nullptr) continue;
			CCGSpriteFrame* spellCurFrame = spell->getCurrentFrame();
			if (spellCurFrame == nullptr) continue;
			for (auto spellBox : spellCurFrame->getAttackBoxes())
			{
				if (spellBox == nullptr) continue;
				Rect spellRect = spellBox->getWorldBox(spell);
				if (victimBodyRect.intersectsRect(spellRect))
				{
					CCGAnimation* spellCurAnimation = spell->getCurrentAnimation();
					if (spellCurAnimation != nullptr)
					{
						victim->onHit(spellCurAnimation->getAttackInfo());
						spell->onHit();
					}
					bHit = true;
					break;
				}
			}
		}

		/* if one body box already be hited, even this frame have multiple body boxes, do not check any more. */
		if (bHit == true) return;
	}
#endif
}
