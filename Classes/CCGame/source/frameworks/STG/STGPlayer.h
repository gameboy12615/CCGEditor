#pragma once

#include "cocos2d.h"
#include "STGCharacter.h"

NS_CC_BEGIN

/** should only have difference with STGCharacter in creators and update function.  
*/
class STGPlayer : public STGCharacter
{
public:

#define MAX_FREE_TIME 0.2	// if no action after 0.1s, will change to idle action.

	STGPlayer(void);
	virtual ~STGPlayer(void);

	/** creators group */
	static STGPlayer* create();
	static STGPlayer* create(const std::string& filename);
	static STGPlayer* createWithCharacterData(STGCharacterData* data);

protected:
	virtual void onUpdate(float delta) override;

	float _freeTime{0.0f};
};

NS_CC_END