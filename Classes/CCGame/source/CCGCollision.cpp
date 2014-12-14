#include "CCGCollision.h"
#include "CCGSprite.h"

USING_NS_CC;

CCGCollisionBox* CCGCollisionBox::create(const Rect& rect, CCGCollisionBox::BoxType type)
{
	CCGCollisionBox *box = new (std::nothrow) CCGCollisionBox();
	if (box && box->init(rect, type))
	{
		box->autorelease();
		return box;
	}
	CC_SAFE_DELETE(box);
	return nullptr;
}

bool CCGCollisionBox::init(const Rect& rect, CCGCollisionBox::BoxType type)
{
	if (Node::init())
	{
		_box = rect;
		_type = type;
		/** the position of box in _boxNode is same as the position in this node. */
		setPosition(Vec2(0, 0));
		setRotation(0);
		return true;
	}

	return false;
}

Rect CCGCollisionBox::getLocalBox()
{
	Node* boxNode = getParent();
	if (boxNode != nullptr)
	{
		Vec2 offset = boxNode->getPosition();
		Vec2 origin = _box.origin + offset;
		return Rect(origin.x, origin.y, _box.size.width, _box.size.height);
	}

	return _box;
}

Rect CCGCollisionBox::getWorldBox(CCGSprite* sprite)
{
	Rect localBox = getLocalBox();
	if (sprite != nullptr)
	{
		Vec2 origin = sprite->convertToWorldSpace(localBox.origin);
		Vec2 opposite = sprite->convertToWorldSpace(Vec2(localBox.origin.x + localBox.size.width, localBox.origin.y + localBox.size.height));
		Vec2 newOrigin = Vec2(std::min(origin.x, opposite.x), std::min(origin.y, opposite.y));
		Vec2 newOpposite = Vec2(std::max(origin.x, opposite.x), std::max(origin.y, opposite.y));
		return Rect(newOrigin.x, newOrigin.y, fabs(newOpposite.x - newOrigin.x), fabs(newOpposite.y - newOrigin.y));
	}

	return localBox;
}
