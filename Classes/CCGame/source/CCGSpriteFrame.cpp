#include "CCGSpriteFrame.h"
#include "CCGSprite.h"

USING_NS_CC;
CCGSpriteFrame::CCGSpriteFrame(void)
{

}

CCGSpriteFrame::~CCGSpriteFrame(void)
{
	if (_boxNode != nullptr)
	{
		_boxNode->removeAllChildren();
	}
}

CCGSpriteFrame* CCGSpriteFrame::create(const std::string& filename, const Rect& rect)
{
	CCGSpriteFrame *spriteFrame = new (std::nothrow) CCGSpriteFrame();
	spriteFrame->initWithTextureFilename(filename, rect);
	spriteFrame->initAdditional();
	spriteFrame->autorelease();

	return spriteFrame;
}

CCGSpriteFrame* CCGSpriteFrame::createWithTexture(Texture2D *texture, const Rect& rect)
{
	CCGSpriteFrame *spriteFrame = new (std::nothrow) CCGSpriteFrame();
	spriteFrame->initWithTexture(texture, rect);
	spriteFrame->initAdditional();
	spriteFrame->autorelease();

	return spriteFrame;
}

CCGSpriteFrame* CCGSpriteFrame::createWithTexture(Texture2D* texture, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize)
{
	CCGSpriteFrame *spriteFrame = new (std::nothrow) CCGSpriteFrame();
	spriteFrame->initWithTexture(texture, rect, rotated, offset, originalSize);
	spriteFrame->initAdditional();
	spriteFrame->autorelease();

	return spriteFrame;
}

CCGSpriteFrame* CCGSpriteFrame::create(const std::string& filename, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize)
{
	CCGSpriteFrame *spriteFrame = new (std::nothrow) CCGSpriteFrame();
	spriteFrame->initWithTextureFilename(filename, rect, rotated, offset, originalSize);
	spriteFrame->initAdditional();
	spriteFrame->autorelease();

	return spriteFrame;
}

bool CCGSpriteFrame::initAdditional(void)
{
	/** init box node */
	_boxNode = Node::create();
	_boxNode->setPosition(_offset);
	return true;
}

void CCGSpriteFrame::addCollisionBox(CCGCollisionBox* box, const Vec2 &offset)
{
	if (box != nullptr && _boxNode != nullptr)
	{
		box->setPosition(offset);
		_boxNode->addChild(box);
		if (box->getType() == CCGCollisionBox::BOX_BODY)
		{
			_bodyBoxes.pushBack(box);
		}
		else
		{
			_attackBoxes.pushBack(box);
		}
	}
}
