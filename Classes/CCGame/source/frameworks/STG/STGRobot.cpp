#include "STGRobot.h"

USING_NS_CC;

STGRobot::STGRobot(void)
{
	_isPlayer = false;
}

STGRobot::~STGRobot(void)
{
	removeAllChildren();
}

STGRobot* STGRobot::create(const std::string& filename)
{
	STGRobot *rob = new (std::nothrow) STGRobot();
	if (rob && rob->initWithFile(filename))
	{
		rob->initAdditional();
		rob->autorelease();
		return rob;
	}
	CC_SAFE_DELETE(rob);
	return nullptr;
}

STGRobot* STGRobot::create()
{
	STGRobot *rob = new (std::nothrow) STGRobot();
	if (rob && rob->init())
	{
		rob->initAdditional();
		rob->autorelease();
		return rob;
	}
	CC_SAFE_DELETE(rob);
	return nullptr;
}

STGRobot* createWithCharacterData(STGCharacterData* data)
{
	if (data == nullptr) return nullptr;

	STGRobot* rob = STGRobot::create();
	rob->setName(data->name);
	rob->setActionMap(data->actionMap);

	return rob;
}

void STGRobot::onUpdate(float delta)
{
	STGCharacter::onUpdate(delta);
}