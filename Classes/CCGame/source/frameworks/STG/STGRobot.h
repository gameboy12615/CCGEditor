#pragma once

#include "cocos2d.h"
#include "STGCharacter.h"

NS_CC_BEGIN

/** should only have difference with STGCharacter in creators and update function.
*/
class STGRobot : public STGCharacter
{
public:
	STGRobot(void);
	virtual ~STGRobot(void);

	/** creators group */
	static STGRobot* create();
	static STGRobot* create(const std::string& filename);
	static STGRobot* createWithCharacterData(STGCharacterData* data);

protected:
	virtual void onUpdate(float delta) override;
};

NS_CC_END