#include "FTGPlayer.h"

USING_NS_CC;

FTGPlayer::FTGPlayer(void)
{

}

FTGPlayer::~FTGPlayer(void)
{
	removeAllChildren();
}

FTGPlayer* FTGPlayer::create(const std::string& filename)
{
	FTGPlayer *player = new (std::nothrow) FTGPlayer();
	if (player && player->initWithFile(filename))
	{
		player->initAdditional();
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

FTGPlayer* FTGPlayer::create()
{
	FTGPlayer *player = new (std::nothrow) FTGPlayer();
	if (player && player->init())
	{
		player->initAdditional();
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

FTGPlayer* FTGPlayer::createWithCharacterData(FTGCharacterData* data)
{
	if (data == nullptr) return nullptr;

	FTGPlayer* player = FTGPlayer::create();
	player->setName(data->characterName);

	if (data->animationsData.size() > 0)
	{
		for (auto pAnimData : data->animationsData)
		{
			CCGAnimation::createToCacheWithAnimationData(pAnimData);
		}
	}

	return player;
}

void FTGPlayer::onHit(AttackInfo &info)
{

}
