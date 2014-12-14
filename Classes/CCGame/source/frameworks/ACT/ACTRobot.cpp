#include "ACTRobot.h"

USING_NS_CC;

ACTRobot::ACTRobot(void)
{

}

ACTRobot::~ACTRobot(void)
{
	removeAllChildren();
}

ACTRobot* ACTRobot::create(const std::string& filename)
{
	ACTRobot *rob = new (std::nothrow) ACTRobot();
	if (rob && rob->initWithFile(filename))
	{
		rob->initAdditional();
		rob->autorelease();
		return rob;
	}
	CC_SAFE_DELETE(rob);
	return nullptr;
}

ACTRobot* ACTRobot::create()
{
	ACTRobot *rob = new (std::nothrow) ACTRobot();
	if (rob && rob->init())
	{
		rob->initAdditional();
		rob->autorelease();
		return rob;
	}
	CC_SAFE_DELETE(rob);
	return nullptr;
}

ACTRobot* createWithCharacterData(ACTCharacterData* data)
{
	if (data == nullptr) return nullptr;

	ACTRobot* rob = ACTRobot::create();
	rob->setName(data->characterName);

	if (data->animationsData.size() > 0)
	{
		for (auto pAnimData : data->animationsData)
		{
			CCGAnimation::createToCacheWithAnimationData(pAnimData);
		}
	}

	return rob;
}

void ACTRobot::onHit(AttackInfo &info)
{

}