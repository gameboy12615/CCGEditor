#include "CCGCharacter.h"
#include "CCGScene.h"
#include "CCGConfig.h"

USING_NS_CC;

CCGCharacter::CCGCharacter(void)
{

}

CCGCharacter::~CCGCharacter(void)
{
	removeAllChildren();
}

void CCGCharacter::addSpell(CCGSpell * spell)
{
	if (spell != nullptr)
	{
		spell->setOwner(this);
		_spells.pushBack(spell);

		CCGScene* scene = dynamic_cast<CCGScene*>(getScene());
		if (scene != nullptr)
		{
			scene->addChild(spell);
		}
	}
}

void CCGCharacter::checkNear(CCGCharacter* other)
{
	if (other == nullptr) return;

	CCGConfig* config = CCGConfig::getInstance();
	if (Vec2(this->getPosition() - other->getPosition()).length() < config->getNearDistance())
	{
		this->setNear(true);
	}
}

bool CCGCharacter::initAdditional(void)
{
	CCGSprite::initAdditional();
	scheduleUpdate();
	setGlobalZOrder(ZORDER_CHARACTER);

	return true;
}