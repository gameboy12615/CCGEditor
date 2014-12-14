#pragma once

#include "cocos2d.h"
#include "STGSpell.h"
#include "../../CCGCharacter.h"

NS_CC_BEGIN

/** this is pure class, should not create instance form it.
    should only have logical difference with CCGCharacter.
*/
class STGCharacter : public CCGCharacter
{
public:

	enum ActionState
	{
		ACTION_STATE_NONE = 0,
		ACTION_STATE_FLY_FORWARD,
		ACTION_STATE_FLY_BACKWARD,
		ACTION_STATE_FAR_ATTACK,
		ACTION_STATE_NEAR_ATTACKA,
		ACTION_STATE_NEAR_ATTACKB,
		ACTION_STATE_NEAR_ATTACKC,
		ACTION_STATE_NEAR_ATTACKD,
		ACTION_STATE_SKILL,
		ACTION_STATE_HIT,
		ACTION_STATE_GUARD,
		ACTION_STATE_CRASH,
		ACTION_STATE_DOWN,
		ACTION_STATE_DIE,
		ACTION_STATE_MAX
	};

	STGCharacter(void);
	virtual ~STGCharacter(void);

	/** cast spell */
	virtual CCGSpell* castSpell(std::string dataName) override;

	/** clone */
	virtual STGCharacter *clone() const override;

	/** state functions */
	ActionState& getCurrentActionState() { return _currentActionState; }
	ActionState& getLastActionState() { return _lastActionState; }
	void runAction(STGCharacter::ActionState state);
	bool isCurrentActionDone();

	/** basic state functions */
	bool isFiring() { return _isFiring; }

	/** bind action */
	void bindAction(STGCharacter::ActionState state, std::string animationName) { _actionMap[state] = animationName; }
	void setActionMap(std::string map[STGCharacter::ACTION_STATE_MAX]);

	/** callback functions */
	virtual void onHit(AttackInfo &info) override;

protected:
	
	/** local callback functions */
	virtual void onUpdate(float delta) override;

	ActionState _currentActionState{ ACTION_STATE_FLY_FORWARD };
	ActionState _lastActionState{ ACTION_STATE_FLY_FORWARD };
	std::string _actionMap[ACTION_STATE_MAX];	// stores animation name for each action state.

	/** character basic states */
	bool _isFiring{ false };
};

struct STGCharacterData : public CharacterData
{
	std::string actionMap[STGCharacter::ACTION_STATE_MAX];

	CREATE_FUNC(STGCharacterData);
};

NS_CC_END