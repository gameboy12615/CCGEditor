#include "STGPlayer.h"
#include "../../CCGScene.h"

USING_NS_CC;

STGPlayer::STGPlayer(void)
{
	_isPlayer = true;
}

STGPlayer::~STGPlayer(void)
{
	removeAllChildren();
}

STGPlayer* STGPlayer::create(const std::string& filename)
{
	STGPlayer *player = new (std::nothrow) STGPlayer();
	if (player && player->initWithFile(filename))
	{
		player->initAdditional();
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

STGPlayer* STGPlayer::create()
{
	STGPlayer *player = new (std::nothrow) STGPlayer();
	if (player && player->init())
	{
		player->initAdditional();
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

STGPlayer* STGPlayer::createWithCharacterData(STGCharacterData* data)
{
	if (data == nullptr) return nullptr;

	STGPlayer* player = STGPlayer::create();
	if (player == nullptr) return nullptr;

	player->setName(data->name);
	player->setActionMap(data->actionMap);

	return player;
}

void STGPlayer::onUpdate(float delta)
{
	STGCharacter::onUpdate(delta);
	static float spellDelay = 0.0f;
	spellDelay += delta;

	if (getCurrentActionState() == ACTION_STATE_HIT		||
		getCurrentActionState() == ACTION_STATE_GUARD	||
		getCurrentActionState() == ACTION_STATE_CRASH	||
		getCurrentActionState() == ACTION_STATE_DOWN	||
		getCurrentActionState() == ACTION_STATE_DIE)
	{
		return; // player can not be contolled at such status.
	}

	auto scene = (CCGScene*)getScene();
	auto joystick = scene->getVirtualJoystick();

	/** update button input */
	auto attackButton = joystick->getAttackButton();
	if (attackButton != nullptr	&& attackButton->getIsActive())
	{
		if (isNear())
		{
			if (getCurrentActionState() != ACTION_STATE_NEAR_ATTACKA	&&
				getCurrentActionState() != ACTION_STATE_NEAR_ATTACKB	&&
				getCurrentActionState() != ACTION_STATE_NEAR_ATTACKC	&&
				getCurrentActionState() != ACTION_STATE_NEAR_ATTACKD	&&
				getCurrentActionState() != ACTION_STATE_SKILL)
			{
				runAction(ACTION_STATE_NEAR_ATTACKA);
			}
			else if (getCurrentActionState() == ACTION_STATE_NEAR_ATTACKA && isCurrentActionDone())
			{
				runAction(ACTION_STATE_NEAR_ATTACKB);
			}
			else if (getCurrentActionState() == ACTION_STATE_NEAR_ATTACKB && isCurrentActionDone())
			{
				runAction(ACTION_STATE_NEAR_ATTACKC);
			}
			else if (getCurrentActionState() == ACTION_STATE_NEAR_ATTACKC && isCurrentActionDone())
			{
				runAction(ACTION_STATE_NEAR_ATTACKD);
			}
			else if (getCurrentActionState() == ACTION_STATE_NEAR_ATTACKD && isCurrentActionDone())
			{
				runAction(ACTION_STATE_NEAR_ATTACKA);
			}
		}
		else
		{	
			if (spellDelay > MAX_FREE_TIME)
			{
				castSpell("data_marisa_bulletAa");
				spellDelay = 0.0f;
			}
		}
	}

	/** update joystick input */
	auto leftJoystick = joystick->getLeftJoystick();
	Vec2 velocity = leftJoystick->getVelocity() * 10;

	// player can't move when near attack and launch skill.
	if (joystick != nullptr	&&
		getCurrentActionState() != ACTION_STATE_NEAR_ATTACKA	&&
		getCurrentActionState() != ACTION_STATE_NEAR_ATTACKB	&&
		getCurrentActionState() != ACTION_STATE_NEAR_ATTACKC	&&
		getCurrentActionState() != ACTION_STATE_NEAR_ATTACKD	&&
		getCurrentActionState() != ACTION_STATE_SKILL)
	{
		if (velocity.x < 0)
		{
			if (getCurrentActionState() != ACTION_STATE_FLY_BACKWARD)
			{
				runAction(ACTION_STATE_FLY_BACKWARD);
			}
		}
		else
		{
			if (getCurrentActionState() != ACTION_STATE_FLY_FORWARD)
			{
				runAction(ACTION_STATE_FLY_FORWARD);
			}
		}

		Point pos = getPosition();
		pos.x += velocity.x;
		pos.y += velocity.y;
		
		setPosition(pos);
	}

	// if all action is done, play idle action
	if (isCurrentActionDone() && getCurrentActionState() != ACTION_STATE_FLY_FORWARD && _freeTime > MAX_FREE_TIME)
	{
		runAction(ACTION_STATE_FLY_FORWARD);
	}

	// update camera position.
	auto camera = scene->getCamera();
	if (camera != nullptr)
	{
		camera->setPosition3D(getPosition3D() + Vec3(0, 0, 500));
	}

	// update free time
	if (isCurrentActionDone())
	{
		_freeTime += delta;
	}
	else
	{
		_freeTime = 0.0f;
	}
}