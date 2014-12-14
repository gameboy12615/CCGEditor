#pragma once

#include "cocos2d.h"
#include "ACTCharacter.h"

NS_CC_BEGIN

class ACTPlayer : public ACTCharacter
{
public:
	ACTPlayer(void);
	virtual ~ACTPlayer(void);

	/** creators group */
	static ACTPlayer* create();
	static ACTPlayer* create(const std::string& filename);
	static ACTPlayer* createWithCharacterData(ACTCharacterData* data);

protected:
	virtual void onHit(AttackInfo &info) override;
};

NS_CC_END