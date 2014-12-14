#pragma once

#include "cocos2d.h"
#include "CCGCollision.h"
#include "CCGDataCache.h"
#include "CCPtr.h"

NS_CC_BEGIN

struct AttackInfo
{
	float			damage;
	float			duration;		// if duration is 0, means one hit.
	float			hitInterval;	// hit interval time.
	float			freezeTime;		// freeze time when be hit.
};

struct AnimationData : public CCGData
{
	std::string		animationName;
	std::string		plistFile;		// plist file defines the frames.
	std::string		baseFrameName;	// baseFrameName + frame index is the frame name.
	unsigned int	startFrame;
	unsigned int	endFrame;
	AttackInfo		attackInfo;
	bool			bLoop;
	bool			bCancellable;
	float			intervalTime;
	std::vector<std::vector<CCGCollisionBox*>>	collisionData;

	CREATE_FUNC(AnimationData);
};

class CCGAnimation : public Animation
{
public:
	CCGAnimation(void);
	virtual ~CCGAnimation(void);

	/** creators group */
	static CCGAnimation* create(void);
	static CCGAnimation* createWithSpriteFrames(const Vector<SpriteFrame*>& arrayOfSpriteFrameNames, float delay = 0.0f, unsigned int loops = 1);
	static CCGAnimation* create(const Vector<AnimationFrame*>& arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops = 1);
	static bool	createToCacheWithAnimationData(AnimationData *data);

	/** other functions */
	void		setAttackInfo(AttackInfo& attackInfo) { memcpy(&_attackInfo, &attackInfo, sizeof(AttackInfo)); }
	AttackInfo& getAttackInfo() { return _attackInfo; }
	void		setLoop(bool loop) { _bLoop = loop; }
	bool		isLoop() { return _bLoop; }
	void		setCancellable(bool cancellable) { _bCancellable = cancellable; }
	bool		isCancellable() { return _bCancellable; }

protected:
	AttackInfo	_attackInfo;
	bool		_bLoop;
	bool		_bCancellable;
};

NS_CC_END