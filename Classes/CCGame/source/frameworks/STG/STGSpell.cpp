#include "STGSpell.h"

USING_NS_CC;

STGSpell::STGSpell(void)
{
	memset(_spellMap, 0, sizeof(_spellMap));
}

STGSpell::~STGSpell(void)
{
	removeAllChildren();
}

STGSpell* STGSpell::create(const std::string& filename)
{
	STGSpell *spell = new (std::nothrow) STGSpell();
	if (spell && spell->initWithFile(filename))
	{
		spell->initAdditional();
		spell->autorelease();
		return spell;
	}
	CC_SAFE_DELETE(spell);
	return nullptr;
}

STGSpell* STGSpell::create()
{
	STGSpell *spell = new (std::nothrow) STGSpell();
	if (spell && spell->init())
	{
		spell->initAdditional();
		spell->autorelease();
		return spell;
	}
	CC_SAFE_DELETE(spell);
	return nullptr;
}

STGSpell* STGSpell::createWithSpellData(STGSpellData* data)
{
	if (data == nullptr) return nullptr;

	STGSpell* spell = STGSpell::create();
	spell->setDuration(data->duration);
	spell->setSpellMap(data->spellMap);

	return spell;
}

STGSpell *STGSpell::clone() const
{
	return nullptr;
}

void STGSpell::runState(STGSpell::SpellState state)
{
	runAnimation(_spellMap[state]);
}

void STGSpell::setSpellMap(std::string map[STGSpell::SPELL_STATE_MAX])
{
	_spellMap[SPELL_STATE_START] = map[SPELL_STATE_START];
}

void STGSpell::onHit()
{

}
