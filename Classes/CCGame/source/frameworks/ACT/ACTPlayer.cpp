#include "ACTPlayer.h"

USING_NS_CC;

ACTPlayer::ACTPlayer(void)
{

}

ACTPlayer::~ACTPlayer(void)
{
	removeAllChildren();
}

ACTPlayer* ACTPlayer::create(const std::string& filename)
{
	ACTPlayer *player = new (std::nothrow) ACTPlayer();
	if (player && player->initWithFile(filename))
	{
		player->initAdditional();
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

ACTPlayer* ACTPlayer::create()
{
	ACTPlayer *player = new (std::nothrow) ACTPlayer();
	if (player && player->init())
	{
		player->initAdditional();
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

ACTPlayer* ACTPlayer::createWithCharacterData(ACTCharacterData* data)
{
	if (data == nullptr) return nullptr;

	ACTPlayer* player = ACTPlayer::create();
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

void ACTPlayer::onHit(AttackInfo &info)
{

}
