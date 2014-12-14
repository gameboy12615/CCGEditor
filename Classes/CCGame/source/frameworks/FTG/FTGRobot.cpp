#include "FTGRobot.h"

USING_NS_CC;

FTGRobot::FTGRobot(void)
{

}

FTGRobot::~FTGRobot(void)
{
	removeAllChildren();
}

FTGRobot* FTGRobot::create(const std::string& filename)
{
	FTGRobot *rob = new (std::nothrow) FTGRobot();
	if (rob && rob->initWithFile(filename))
	{
		rob->initAdditional();
		rob->autorelease();
		return rob;
	}
	CC_SAFE_DELETE(rob);
	return nullptr;
}

FTGRobot* FTGRobot::create()
{
	FTGRobot *rob = new (std::nothrow) FTGRobot();
	if (rob && rob->init())
	{
		rob->initAdditional();
		rob->autorelease();
		return rob;
	}
	CC_SAFE_DELETE(rob);
	return nullptr;
}

FTGRobot* createWithCharacterData(FTGCharacterData* data)
{
	if (data == nullptr) return nullptr;

	FTGRobot* rob = FTGRobot::create();
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

void FTGRobot::onHit(AttackInfo &info)
{

}