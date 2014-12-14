#include "ACTCharacter.h"

USING_NS_CC;

ACTCharacter::ACTCharacter(void)
{
	memset(_actionMap, 0, sizeof(_actionMap));
}

ACTCharacter::~ACTCharacter(void)
{
	removeAllChildren();
}

ACTSpell* ACTCharacter::castSpell(ACTSpellData* data)
{
	return ACTSpell::createWithSpellData(data);
}