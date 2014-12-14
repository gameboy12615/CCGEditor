#include "FTGSpell.h"

USING_NS_CC;

FTGSpell::FTGSpell(void)
{
	memset(_spellMap, 0, sizeof(_spellMap));
}

FTGSpell::~FTGSpell(void)
{
	removeAllChildren();
}

FTGSpell* FTGSpell::create(const std::string& filename)
{
	FTGSpell *spell = new (std::nothrow) FTGSpell();
	if (spell && spell->initWithFile(filename))
	{
		spell->initAdditional();
		spell->autorelease();
		return spell;
	}
	CC_SAFE_DELETE(spell);
	return nullptr;
}

FTGSpell* FTGSpell::create()
{
	FTGSpell *spell = new (std::nothrow) FTGSpell();
	if (spell && spell->init())
	{
		spell->initAdditional();
		spell->autorelease();
		return spell;
	}
	CC_SAFE_DELETE(spell);
	return nullptr;
}

FTGSpell* FTGSpell::createWithSpellData(FTGSpellData* data)
{
	if (data == nullptr) return nullptr;

	FTGSpell* spell = FTGSpell::create();
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