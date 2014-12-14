#include "CCGAnimation.h"
#include "CCGSpriteFrameCache.h"
#include "CCGSpriteFrame.h"

USING_NS_CC;

CCGAnimation::CCGAnimation(void)
{

}

CCGAnimation::~CCGAnimation(void)
{

}

CCGAnimation* CCGAnimation::create(void)
{
	CCGAnimation *animation = new (std::nothrow) CCGAnimation();
	animation->init();
	animation->autorelease();

	return animation;
}

CCGAnimation* CCGAnimation::createWithSpriteFrames(const Vector<SpriteFrame*>& frames, float delay/* = 0.0f*/, unsigned int loops/* = 1*/)
{
	CCGAnimation *animation = new (std::nothrow) CCGAnimation();
	animation->initWithSpriteFrames(frames, delay, loops);
	animation->autorelease();

	return animation;
}

CCGAnimation* CCGAnimation::create(const Vector<AnimationFrame*>& arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops /* = 1 */)
{
	CCGAnimation *animation = new (std::nothrow) CCGAnimation();
	animation->initWithAnimationFrames(arrayOfAnimationFrameNames, delayPerUnit, loops);
	animation->autorelease();
	return animation;
}

bool CCGAnimation::createToCacheWithAnimationData(AnimationData *data)
{
	if (data == nullptr || data->endFrame > 999) return false;

	// add frames to cache
	auto frameCache = CCGSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile(data->plistFile);

	// create animation.
	Vector<SpriteFrame*> animFrames;
	char str[10] = { 0 };

	for (int i = data->startFrame; i <= data->endFrame; i++)
	{
		sprintf(str, "%03d.png", i);
		std::string frameName = data->baseFrameName + std::string(str);
		SpriteFrame* frame = frameCache->getSpriteFrameByName(frameName);
		if (data->collisionData.size() > 0)
		{
			std::vector<CCGCollisionBox*> frameBoxes = data->collisionData[i - data->startFrame];
			if (frameBoxes.size() <= 0) continue;
			for (auto box : frameBoxes)
			{
				static_cast<CCGSpriteFrame*>(frame)->addCollisionBox(box);
			}
		}

		animFrames.pushBack(frame);
	}

	CCGAnimation* animation = CCGAnimation::createWithSpriteFrames(animFrames, data->intervalTime);
	animation->setAttackInfo(data->attackInfo);
	animation->setLoop(data->bLoop);
	animation->setCancellable(data->bCancellable);

	// Add an animation to the Cache
	auto animCache = AnimationCache::getInstance();
	animCache->addAnimation(static_cast<Animation*>(animation), data->animationName);

	return true;
}