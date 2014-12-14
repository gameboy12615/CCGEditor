#pragma once

#include "cocos2d.h"

NS_CC_BEGIN

class CCGSprite;

class CCGCollisionBox : public Node
{
public:

	enum BoxType
	{
		BOX_BODY,
		BOX_ATTACK
	};

	/** create functions */
	static CCGCollisionBox* create(const Rect& rect, CCGCollisionBox::BoxType type);

	/** init functions */
	virtual bool init(const Rect& rect, CCGCollisionBox::BoxType type);

	/** access functions */
	Rect getLocalBox(); // local box in sprite space. do not support box rotation in sprite space.
	Rect getWorldBox(CCGSprite* sprite); // world box in world space.
	CCGCollisionBox::BoxType getType() { return _type; }

protected:
	/** collision box */
	Rect	_box;
	BoxType _type;
};

NS_CC_END