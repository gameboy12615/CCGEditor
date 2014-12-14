#include "FTGCharacter.h"

USING_NS_CC;

FTGCharacter::FTGCharacter(void)
{
	memset(_actionMap, 0, sizeof(_actionMap));
}

FTGCharacter::~FTGCharacter(void)
{
	removeAllChildren();
}

FTGSpell* FTGCharacter::castSpell(FTGSpellData* data)
{
	return FTGSpell::createWithSpellData(data);
}