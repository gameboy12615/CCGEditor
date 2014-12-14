#pragma once

#include "cocos2d.h"
#include "FTGCharacter.h"

NS_CC_BEGIN

class FTGRobot : public FTGCharacter
{
public:
	FTGRobot(void);
	virtual ~FTGRobot(void);

	/** creators group */
	static FTGRobot* create();
	static FTGRobot* create(const std::string& filename);
	static FTGRobot* createWithCharacterData(FTGCharacterData* data);

protected:
	virtual void onHit(AttackInfo &info) override;
};

NS_CC_END