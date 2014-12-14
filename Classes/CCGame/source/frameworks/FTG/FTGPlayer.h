#pragma once

#include "cocos2d.h"
#include "FTGCharacter.h"

NS_CC_BEGIN

class FTGPlayer : public FTGCharacter
{
public:
	FTGPlayer(void);
	virtual ~FTGPlayer(void);

	/** creators group */
	static FTGPlayer* create();
	static FTGPlayer* create(const std::string& filename);
	static FTGPlayer* createWithCharacterData(FTGCharacterData* data);

protected:
	virtual void onHit(AttackInfo &info) override;
};

NS_CC_END