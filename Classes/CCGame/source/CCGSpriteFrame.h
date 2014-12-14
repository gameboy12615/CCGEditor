#pragma once

#include "cocos2d.h"
#include "CCGCollision.h"
#include "CCPtr.h"

NS_CC_BEGIN

class CCGSprite;

class CCGSpriteFrame : public SpriteFrame
{
public:
	CCGSpriteFrame(void);
	virtual ~CCGSpriteFrame(void);

	/** create functions */
	static CCGSpriteFrame* create(const std::string& filename, const Rect& rect);
	static CCGSpriteFrame* create(const std::string& filename, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);
	static CCGSpriteFrame* createWithTexture(Texture2D* pobTexture, const Rect& rect);
	static CCGSpriteFrame* createWithTexture(Texture2D* pobTexture, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);

	/** init additional */
	bool initAdditional(void);

	/** collision box functions */
	void addCollisionBox(CCGCollisionBox* box, const Vec2 &offset = Vec2(0, 0));
	Vector<CCGCollisionBox*>& getBodyBoxes() { return _bodyBoxes; }
	Vector<CCGCollisionBox*>& getAttackBoxes() { return _attackBoxes; }

protected:
	Vector<CCGCollisionBox*> _bodyBoxes; // if not specially, each frame should only have one body box.
	Vector<CCGCollisionBox*> _attackBoxes;
	/** box node is the parent of all the collision boxes in this frame */
	CCPtr<Node>	_boxNode{ nullptr };
};

NS_CC_END