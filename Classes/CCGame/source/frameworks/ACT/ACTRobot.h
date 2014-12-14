#pragma once

#include "cocos2d.h"
#include "ACTCharacter.h"

NS_CC_BEGIN

class ACTRobot : public ACTCharacter
{
public:
	ACTRobot(void);
	virtual ~ACTRobot(void);

	/** creators group */
	static ACTRobot* create();
	static ACTRobot* create(const std::string& filename);
	static ACTRobot* createWithCharacterData(ACTCharacterData* data);

protected:
	virtual void onHit(AttackInfo &info) override;
};

NS_CC_END