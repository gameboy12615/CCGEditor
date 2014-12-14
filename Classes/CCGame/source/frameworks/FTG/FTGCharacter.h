#pragma once

#include "cocos2d.h"
#include "FTGSpell.h"
#include "../../CCGSprite.h"

NS_CC_BEGIN

struct FTGCharacterData
{
	std::string		characterName;
	std::vector<AnimationData*> animationsData;
};

/** this is pure class, should not create instance form it */
class FTGCharacter : public CCGSprite
{
public:

	enum ActionState
	{
		ACTION_STATE_NONE = 0,
		ACTION_STATE_IDLE,
		ACTION_STATE_WALK_FRONT,
		ACTION_STATE_WALK_BACK,
		ACTION_STATE_JUMP,
		ACTION_STATE_JUMP_FRONT,
		ACTION_STATE_JUMP_BACK,
		ACTION_STATE_DASH_FRONT,
		ACTION_STATE_DASH_BACK,
		ACTION_STATE_CRASH,
		ACTION_STATE_DOWN,
		ACTION_STATE_EMOTION,
		ACTION_STATE_GUARD_AIR,
		ACTION_STATE_GUARD_BAIR,
		ACTION_STATE_GUARD_UNDER,
		ACTION_STATE_GUARD_BUNDER,
		ACTION_STATE_GUARD_UPPER,
		ACTION_STATE_GUARD_BUPPER,
		ACTION_STATE_HIT_AIR,
		ACTION_STATE_HIT_SIT,
		ACTION_STATE_HIT_SPIN,
		ACTION_STATE_HIT_UNDER,
		ACTION_STATE_HIT_UPPER,
		ACTION_STATE_ATTACK_AA,
		ACTION_STATE_ATTACK_AB,
		ACTION_STATE_ATTACK_AC,
		ACTION_STATE_ATTACK_AD,
		ACTION_STATE_ATTACK_BA,
		ACTION_STATE_ATTACK_BB,
		ACTION_STATE_ATTACK_BC,
		ACTION_STATE_ATTACK_BD,
		ACTION_STATE_ATTACK_CA,
		ACTION_STATE_ATTACK_CB,
		ACTION_STATE_ATTACK_CC,
		ACTION_STATE_ATTACK_CD,
		ACTION_STATE_MAX
	};

	FTGCharacter(void);
	virtual ~FTGCharacter(void);

	/** cast spell */
	FTGSpell* castSpell(FTGSpellData* data);

	/** state functions */
	ActionState& getCurrentActionState() { return _currentActionState; }
	ActionState& getLastActionState() { return _lastActionState; }
	bool isInAir() { return _inAir; }

	/** bind action */
	void bindAction(FTGCharacter::ActionState state, std::string animationName) { _actionMap[state] = animationName; }

protected:
	ActionState _currentActionState{ ACTION_STATE_IDLE };
	ActionState _lastActionState{ ACTION_STATE_IDLE };
	bool		_inAir{false};
	std::string _actionMap[ACTION_STATE_MAX];	// stores animation name for each action state.
};

NS_CC_END