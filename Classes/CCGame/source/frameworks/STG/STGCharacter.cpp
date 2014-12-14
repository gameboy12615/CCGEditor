#include "STGCharacter.h"
#include "../../CCGScene.h"
#include "../../CCGLuaCache.h"

USING_NS_CC;

STGCharacter::STGCharacter(void)
{
	memset(_actionMap, 0, sizeof(_actionMap));
}

STGCharacter::~STGCharacter(void)
{
	removeAllChildren();
}

STGCharacter *STGCharacter::clone() const
{
	return nullptr;
}

CCGSpell* STGCharacter::castSpell(std::string dataName)
{
	CCGDataCache *dataCache = CCGDataCache::getInstance();
	STGSpellData* data = dynamic_cast<STGSpellData*>(dataCache->getData(dataName));

	if (data != nullptr)
	{
		STGSpell* spell = STGSpell::createWithSpellData(static_cast<STGSpellData*>(data));
		addSpell(spell);
		Vec2 pos = getPosition();
		spell->setPosition(getPosition() + data->startPosition);
		spell->setRotation(getRotation());
		spell->runState(STGSpell::SPELL_STATE_START);
		spell->runLuaScript(data->scriptName);
		return spell;
	}
	return nullptr;
}

void STGCharacter::runAction(STGCharacter::ActionState state)
{
	runAnimation(_actionMap[state]);
	_lastActionState = _currentActionState;
	_currentActionState = state;
}

bool STGCharacter::isCurrentActionDone()
{
	return isCurrentAnimationDone();
}

void STGCharacter::onHit(AttackInfo &info)
{

}

void STGCharacter::onUpdate(float delta)
{

}

void STGCharacter::setActionMap(std::string map[STGCharacter::ACTION_STATE_MAX])
{
	_actionMap[ACTION_STATE_FLY_FORWARD] = map[ACTION_STATE_FLY_FORWARD];
	_actionMap[ACTION_STATE_FLY_BACKWARD] = map[ACTION_STATE_FLY_BACKWARD];
	_actionMap[ACTION_STATE_FAR_ATTACK] = map[ACTION_STATE_FAR_ATTACK];
	_actionMap[ACTION_STATE_NEAR_ATTACKA] = map[ACTION_STATE_NEAR_ATTACKA];
	_actionMap[ACTION_STATE_NEAR_ATTACKB] = map[ACTION_STATE_NEAR_ATTACKB];
	_actionMap[ACTION_STATE_NEAR_ATTACKC] = map[ACTION_STATE_NEAR_ATTACKC];
	_actionMap[ACTION_STATE_NEAR_ATTACKD] = map[ACTION_STATE_NEAR_ATTACKD];
	_actionMap[ACTION_STATE_SKILL] = map[ACTION_STATE_SKILL];
	_actionMap[ACTION_STATE_HIT] = map[ACTION_STATE_HIT];
	_actionMap[ACTION_STATE_GUARD] = map[ACTION_STATE_GUARD];
	_actionMap[ACTION_STATE_CRASH] = map[ACTION_STATE_CRASH];
	_actionMap[ACTION_STATE_DOWN] = map[ACTION_STATE_DOWN];
	_actionMap[ACTION_STATE_DIE] = map[ACTION_STATE_DIE];
}