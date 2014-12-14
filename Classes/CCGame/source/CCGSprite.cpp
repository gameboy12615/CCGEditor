#include "CCGSprite.h"
#include "CCGScene.h"

USING_NS_CC;

CCGSprite::CCGSprite(void)
{

}

CCGSprite::~CCGSprite(void)
{
	removeAllChildren();
}

void CCGSprite::enableAlphaTest(void)
{
	auto program = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV);
	GLint alphaValueLocation = glGetUniformLocation(program->getProgram(), GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE);
	program->use();
	program->setUniformLocationWith1f(alphaValueLocation, 0.05f);
	setShaderProgram(program);
}

bool CCGSprite::initAdditional(void)
{
	//enableAlphaTest();
#if CCG_COLLISION_BOX_DEBUG_DRAW
	/** create boxDrawNode for collision box drawing */
	_boxDrawNode = BoxDrawNode::create();
	_boxDrawNode->setPosition(Vec2(0, 0));
	_boxDrawNode->setGlobalZOrder(ZORDER_DEBUG_DRAW_NODE);
	addChild(_boxDrawNode.get());
#endif
	return true;
}

CCGSprite* CCGSprite::createWithTexture(Texture2D *texture)
{
	CCGSprite *sprite = new (std::nothrow) CCGSprite();
	if (sprite && sprite->initWithTexture(texture))
	{
		sprite->initAdditional();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

CCGSprite* CCGSprite::createWithTexture(Texture2D *texture, const Rect& rect, bool rotated)
{
	CCGSprite *sprite = new (std::nothrow) CCGSprite();
	if (sprite && sprite->initWithTexture(texture, rect, rotated))
	{
		sprite->initAdditional();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

CCGSprite* CCGSprite::create(const std::string& filename)
{
	CCGSprite *sprite = new (std::nothrow) CCGSprite();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->initAdditional();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

CCGSprite* CCGSprite::create(const std::string& filename, const Rect& rect)
{
	CCGSprite *sprite = new (std::nothrow) CCGSprite();
	if (sprite && sprite->initWithFile(filename, rect))
	{
		sprite->initAdditional();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

CCGSprite* CCGSprite::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
	CCGSprite *sprite = new (std::nothrow) CCGSprite();
	if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->initAdditional();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

CCGSprite* CCGSprite::createWithSpriteFrameName(const std::string& spriteFrameName)
{
	SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = { 0 };
	sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
	CCASSERT(frame != nullptr, msg);
#endif

	return createWithSpriteFrame(frame);
}

CCGSprite* CCGSprite::create()
{
	CCGSprite *sprite = new (std::nothrow) CCGSprite();
	if (sprite && sprite->init())
	{
		sprite->initAdditional();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void CCGSprite::setSpriteFrame(SpriteFrame *spriteFrame)
{
	Sprite::setSpriteFrame(spriteFrame);
	CCGSpriteFrame* newFrame = dynamic_cast<CCGSpriteFrame*>(spriteFrame);
	if (newFrame != nullptr)
	{
		_currentFrame = newFrame;
	}
}

void CCGSprite::runAnimationSequence()
{
	if (_curAnimationIndex < _animations.size())
	{
		CCGAnimation* animationPart = _animations.at(_curAnimationIndex);
		if (animationPart == nullptr) return;

		animationPart->setRestoreOriginalFrame(true);
		auto animatePart = Animate::create(animationPart);
		if (animatePart == nullptr) return;

		if (animationPart->isLoop())
		{
			runAction(CCRepeatForever::create(animatePart));
		}
		else
		{
			auto seq = Sequence::create(animatePart, CallFunc::create(CC_CALLBACK_0(CCGSprite::runAnimationSequence, this)), nullptr);
			runAction(seq);
		}

		_curAnimationIndex++;
		setCurrentAnimate(animatePart);
	}
}

void CCGSprite::runAnimation(std::string animationName)
{
	// stop all animation before play a new animation
	stopAnimation();

	// get animation from cache
	auto animationCache = AnimationCache::getInstance();
	CCGAnimation* animation = dynamic_cast<CCGAnimation*>(animationCache->getAnimation(animationName));

	if (animation != nullptr)
	{
		animation->setRestoreOriginalFrame(true);

		auto animate = Animate::create(animation);
		if (animate == nullptr) return;

		// run the animation
		if (animation->isLoop())
		{
			runAction(CCRepeatForever::create(animate));
		}
		else
		{
			runAction(animate);
		}

		setCurrentAnimate(animate);
	}
	else
	{	
		// only support animation sequence below 10 parts
		char str[10] = { 0 };
		for (int i = 0; i < 10; i++)
		{
			sprintf(str, ".part%d", i);
			CCGAnimation* animationPart = dynamic_cast<CCGAnimation*>(animationCache->getAnimation(animationName + std::string(str)));
			if (animationPart == nullptr) break;
			_animations.pushBack(animationPart);

			if (animationPart->isLoop()) break; // should not add animation part after loop part.
		}
		
		runAnimationSequence();
	}
}

void CCGSprite::stopAnimation()
{
	stopAllActions();
	_animations.clear();
	_curAnimationIndex = 0;
}

CCGAnimation* CCGSprite::getCurrentAnimation()
{
	if (_currentAnimate != nullptr)
	{
		return dynamic_cast<CCGAnimation*>(_currentAnimate->getAnimation());
	}
	return nullptr;
}

bool CCGSprite::isCurrentAnimationDone()
{
	if (_animations.size() > 0)
	{
		if (_curAnimationIndex == _animations.size() - 1)
		{
			CCGAnimation* animation = _animations.at(_curAnimationIndex);
			if (animation == nullptr) return true;
			if (animation->isLoop()) return false;
		}
		else
		{
			return false;
		}
	}

	if (_currentAnimate == nullptr) return true;
	return _currentAnimate->isDone();
}

void CCGSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Sprite::draw(renderer, transform, flags);
	_insideBounds = (flags & FLAGS_TRANSFORM_DIRTY) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;

	if (_insideBounds)
	{
#if CCG_COLLISION_BOX_DEBUG_DRAW
		drawCollisionBoxes();
#endif
	}
}

bool CCGSprite::isRelativeOwnedBy(CCGSprite* sprite)
{
	if (sprite == nullptr) return false;

	for (Node *p = _parent; p != nullptr; p = p->getParent())
	{
		CCGSprite* ps = dynamic_cast<CCGSprite*>(p);
		if (ps != nullptr && ps->getOwner() == sprite)
		{
			return true;
		}
	}

	return false;
}

#if CCG_COLLISION_BOX_DEBUG_DRAW
void CCGSprite::drawCollisionBoxes()
{
	if (_currentFrame != nullptr && _boxDrawNode != nullptr)
	{
		_boxDrawNode->clear();
		if (_currentFrame->getBodyBoxes().size() > 0)
		{
			for (auto& bodyBox : _currentFrame->getBodyBoxes())
			{
				_boxDrawNode->drawBox(bodyBox);
			}
		}

		if (_currentFrame->getAttackBoxes().size() > 0)
		{
			for (auto& attackBox : _currentFrame->getAttackBoxes())
			{
				_boxDrawNode->drawBox(attackBox);
			}
		}
	}
}

void CCGSprite::BoxDrawNode::drawBox(CCGCollisionBox* box)
{
	if (box != nullptr)
	{
		Rect localBox = box->getLocalBox();
		if (box->getType() == CCGCollisionBox::BOX_BODY)
		{
			drawRect(localBox.origin, localBox.origin + Vec2(localBox.size), Color4F(0, 1, 0, 1));
			drawSolidRect(localBox.origin + Vec2(0.8, 0.8), localBox.origin + Vec2(localBox.size) - Vec2(0.8, 0.8), Color4F(0, 1, 0, 0.5));
		}
		else
		{
			drawRect(localBox.origin, localBox.origin + Vec2(localBox.size), Color4F(1, 0, 0, 1));
			drawSolidRect(localBox.origin + Vec2(0.8, 0.8), localBox.origin + Vec2(localBox.size) - Vec2(0.8, 0.8), Color4F(1, 0, 0, 0.5));
		}
	}
}
#endif