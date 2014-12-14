#pragma once

#include "cocos2d.h"
#include "CCGSpriteFrame.h"
#include "CCGAnimation.h"
#include "CCGConfig.h"

NS_CC_BEGIN

class CCGSprite : public Sprite
{
public:

	CCGSprite(void);
	virtual ~CCGSprite(void);

	/** creators group */
	static CCGSprite* create();
	static CCGSprite* create(const std::string& filename);
	static CCGSprite* create(const std::string& filename, const Rect& rect);
	static CCGSprite* createWithTexture(Texture2D *texture);
	static CCGSprite* createWithTexture(Texture2D *texture, const Rect& rect, bool rotated = false);
	static CCGSprite* createWithSpriteFrame(SpriteFrame *spriteFrame);
	static CCGSprite* createWithSpriteFrameName(const std::string& spriteFrameName);

	/** the owner of spell is character */
	void setOwner(CCGSprite* sprite) { _owner = sprite; }
	CCGSprite* getOwner() { return _owner; }

	/** frame functions */
	virtual void setSpriteFrame(SpriteFrame* newFrame) override;
	virtual CCGSpriteFrame* getCurrentFrame() { return _currentFrame; }

	/** animation functions */
	void setCurrentAnimate(Animate* animate) { _currentAnimate = animate; }
	Animate* getCurrentAnimate() { return _currentAnimate.get(); }
	CCGAnimation* getCurrentAnimation();
	void runAnimation(std::string animationName);
	void stopAnimation();
	bool isCurrentAnimationDone();

	/** draw functions */
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

	/** other functions */
	bool isRelativeOwnedBy(CCGSprite* sprite);

	/** callback functions */
	virtual void onHit(AttackInfo &info) {}
	virtual void onHit() {}

protected:

	enum SpriteZOrder
	{
		ZORDER_NONE = 0,
		ZORDER_CHARACTER = 0,
		ZORDER_SPELL,
		ZORDER_DEBUG_DRAW_NODE,
		ZORDER_MAX
	};

#if CCG_COLLISION_BOX_DEBUG_DRAW
	class BoxDrawNode : public DrawNode
	{
	public:
		CREATE_FUNC(BoxDrawNode);
		void drawBox(CCGCollisionBox* box);
	};
	void drawCollisionBoxes();

	/** use to draw collision boxes */
	CCPtr<BoxDrawNode> _boxDrawNode{ nullptr };
#endif

	/** init additional */
	virtual bool initAdditional(void);

	/** callback functions */
	virtual void onNear() {}
	void runAnimationSequence();

	/** other functions */
	void enableAlphaTest(void);

	/** current frame */
	CCGSpriteFrame*			_currentFrame{ nullptr };
	/** current action */
	CCPtr<Animate>			_currentAnimate{ nullptr };
	/** animation array for multiple animation action */
	Vector<CCGAnimation*>	_animations;
	unsigned int			_curAnimationIndex;
	/** other elements */
	CustomCommand			_customCommand;
	/** the mother which breed this sprite */
	CCGSprite*				_owner{ nullptr };
};

NS_CC_END