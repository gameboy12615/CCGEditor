#include "ACTSpell.h"

USING_NS_CC;

ACTSpell::ACTSpell(void)
{
	memset(_spellMap, 0, sizeof(_spellMap));
}

ACTSpell::~ACTSpell(void)
{
	removeAllChildren();
}

ACTSpell* ACTSpell::create(const std::string& filename)
{
	ACTSpell *spell = new (std::nothrow) ACTSpell();
	if (spell && spell->initWithFile(filename))
	{
		spell->initAdditional();
		spell->autorelease();
		return spell;
	}
	CC_SAFE_DELETE(spell);
	return nullptr;
}

ACTSpell* ACTSpell::create()
{
	ACTSpell *spell = new (std::nothrow) ACTSpell();
	if (spell && spell->init())
	{
		spell->initAdditional();
		spell->autorelease();
		return spell;
	}
	CC_SAFE_DELETE(spell);
	return nullptr;
}

ACTSpell* ACTSpell::createWithSpellData(ACTSpellData* data)
{
	if (data == nullptr) return nullptr;

	ACTSpell* spell = ACTSpell::create();
	spell->setPosition(data->startPosition);
	spell->setDuration(data->duration);

	if (data->animationsData.size() > 0)
	{
		for (auto pAnimData : data->animationsData)
		{
			CCGAnimation::createToCacheWithAnimationData(pAnimData);
		}
	}

	return spell;
}