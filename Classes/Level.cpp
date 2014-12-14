#include "Level.h"
#include "CCSTG.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool Level::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	setAnchorPoint(Vec2(0, 0));
	setPosition3D(Vec3(0, 0, 0));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto ground = CCGSprite::create("textures/ground.png");
	ground->setPosition3D(Vec3(origin.x, origin.y - 200, 0));
	ground->setRotation3D(Vec3(-90, 0, 0));
	ground->setGlobalZOrder(-2000);
	addChild(ground, 0);

	CreateMarisa();
	CreateReimu();

	auto mare = CCGSprite::create("textures/mare.png");
	mare->setAnchorPoint(Vec2(0.5, 0));
	mare->setPosition3D(Vec3(origin.x, origin.y - 200, -1000));
	addChild(mare, 0);

	auto spr3D = Sprite3D::create("Sprite3DTest/boss1.obj");
	spr3D->setScale(20.f);
	spr3D->setTexture("Sprite3DTest/boss.png");
	spr3D->setPosition3D(Vec3(origin.x, origin.y, -500));
	spr3D->runAction(RepeatForever::create(RotateBy::create(3, 360)));
	addChild(spr3D);

	_drawNode = DrawNode::create();
	_drawNode->setPosition3D(Vec3(origin.x, origin.y, 0));
	_drawNode->setCameraMask((unsigned short)CameraFlag::USER1);
	addChild(_drawNode.get(), 0);

	// Layer update callback
	schedule(schedule_selector(Level::updateLayer), 0.0f);
	scheduleUpdate();
	return true;
}

void Level::updateLayer(float fDelta)
{

}

void Level::update(float delta)
{
#if 0
	static int count = 0;
	static bool bAttach = false;
	if (count++ >= 200)
	{
		if (bAttach)
		{
			if (_drawNode->getParent() == static_cast<Node*>(this))
				removeChild(_drawNode.get(), false);
			if (_drawNode->getParent() != static_cast<Node*>(_marisa.get()))
				_marisa->addChild(_drawNode.get());
		}
		else
		{
			if (_drawNode->getParent() == static_cast<Node*>(_marisa.get()))
				_marisa->removeChild(_drawNode.get(), false);
			if (_drawNode->getParent() != static_cast<Node*>(this))
				addChild(_drawNode.get());
		}
		count = 0;
		bAttach = bAttach ? false : true;
	}
#endif
}

void Level::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_customCommand.init(1);
	_customCommand.func = CC_CALLBACK_0(Level::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

void Level::onDraw(const Mat4 &transform, uint32_t flags)
{
	//_drawNode->drawSolidRect(Vec2(-2000, -2000), Vec2(2000, 2000), Color4F(180, 180, 180, 255));
}

void Level::CreateMarisa()
{
	AnimationData *animData = AnimationData::create();
	// marisa_fly_forward
	animData->plistFile = "marisa/fly_forward.plist";
	animData->baseFrameName = "fly_forward";
	animData->bLoop = true;
	animData->startFrame = 0;
	animData->endFrame = 4;
	animData->animationName = "anim_marisa_fly_forward";
	animData->intervalTime = 0.1f;
	animData->attackInfo.duration = 0.0f;
	for (int i = 0; i <= animData->endFrame - animData->startFrame; i++)
	{
		std::vector<CCGCollisionBox*> frameBoxes;
		frameBoxes.push_back(CCGCollisionBox::create(Rect(80, 0, 50, 100), CCGCollisionBox::BOX_ATTACK));
		frameBoxes.push_back(CCGCollisionBox::create(Rect(0, 0, 100, 50), CCGCollisionBox::BOX_BODY));
		animData->collisionData.push_back(frameBoxes);
	}
	CCGAnimation::createToCacheWithAnimationData(animData);

	// marisa_fly_backward.part0
	animData = AnimationData::create();
	animData->plistFile = "marisa/fly_backward.plist";
	animData->baseFrameName = "fly_backward";
	animData->bLoop = false;
	animData->startFrame = 0;
	animData->endFrame = 3;
	animData->animationName = "anim_marisa_fly_backward.part0";
	animData->intervalTime = 0.05f;
	animData->attackInfo.duration = 0.0f;
	for (int i = 0; i <= animData->endFrame - animData->startFrame; i++)
	{
		std::vector<CCGCollisionBox*> frameBoxes;
		auto box = CCGCollisionBox::create(Rect(0, 0, 100, 50), CCGCollisionBox::BOX_ATTACK);
		frameBoxes.push_back(box);
		animData->collisionData.push_back(frameBoxes);
	}
	CCGAnimation::createToCacheWithAnimationData(animData);

	// marisa_fly_backward.part1
	animData = AnimationData::create();
	animData->plistFile = "marisa/fly_backward.plist";
	animData->baseFrameName = "fly_backward";
	animData->bLoop = true;
	animData->startFrame = 4;
	animData->endFrame = 8;
	animData->animationName = "anim_marisa_fly_backward.part1";
	animData->intervalTime = 0.1f;
	animData->attackInfo.duration = 0.0f;
	for (int i = 0; i <= animData->endFrame - animData->startFrame; i++)
	{
		std::vector<CCGCollisionBox*> frameBoxes;
		auto box = CCGCollisionBox::create(Rect(0, 0, 100, 50), CCGCollisionBox::BOX_ATTACK);
		frameBoxes.push_back(box);
		animData->collisionData.push_back(frameBoxes);
	}
	CCGAnimation::createToCacheWithAnimationData(animData);

	// marisa_near_attackA
	animData = AnimationData::create();
	animData->plistFile = "marisa/near_attackA.plist";
	animData->baseFrameName = "near_attackA";
	animData->bLoop = false;
	animData->startFrame = 0;
	animData->endFrame = 7;
	animData->animationName = "anim_marisa_near_attackA";
	animData->intervalTime = 0.1f;
	animData->attackInfo.duration = 0.0f;
	for (int i = 0; i <= animData->endFrame - animData->startFrame; i++)
	{
		std::vector<CCGCollisionBox*> frameBoxes;
		auto box = CCGCollisionBox::create(Rect(0, 0, 100, 50), CCGCollisionBox::BOX_ATTACK);
		frameBoxes.push_back(box);
		animData->collisionData.push_back(frameBoxes);
	}
	CCGAnimation::createToCacheWithAnimationData(animData);

	// marisa_near_attackB
	animData = AnimationData::create();
	animData->plistFile = "marisa/near_attackB.plist";
	animData->baseFrameName = "near_attackB";
	animData->bLoop = false;
	animData->startFrame = 0;
	animData->endFrame = 8;
	animData->animationName = "anim_marisa_near_attackB";
	animData->intervalTime = 0.1f;
	animData->attackInfo.duration = 0.0f;
	for (int i = 0; i <= animData->endFrame - animData->startFrame; i++)
	{
		std::vector<CCGCollisionBox*> frameBoxes;
		auto box = CCGCollisionBox::create(Rect(0, 0, 100, 50), CCGCollisionBox::BOX_ATTACK);
		frameBoxes.push_back(box);
		animData->collisionData.push_back(frameBoxes);
	}
	CCGAnimation::createToCacheWithAnimationData(animData);

	// marisa_near_attackC
	animData = AnimationData::create();
	animData->plistFile = "marisa/near_attackC.plist";
	animData->baseFrameName = "near_attackC";
	animData->bLoop = false;
	animData->startFrame = 0;
	animData->endFrame = 9;
	animData->animationName = "anim_marisa_near_attackC";
	animData->intervalTime = 0.1f;
	animData->attackInfo.duration = 0.0f;
	for (int i = 0; i <= animData->endFrame - animData->startFrame; i++)
	{
		std::vector<CCGCollisionBox*> frameBoxes;
		auto box = CCGCollisionBox::create(Rect(0, 0, 100, 50), CCGCollisionBox::BOX_ATTACK);
		frameBoxes.push_back(box);
		animData->collisionData.push_back(frameBoxes);
	}
	CCGAnimation::createToCacheWithAnimationData(animData);

	// marisa_near_attackD
	animData = AnimationData::create();
	animData->plistFile = "marisa/near_attackD.plist";
	animData->baseFrameName = "near_attackD";
	animData->bLoop = false;
	animData->startFrame = 0;
	animData->endFrame = 5;
	animData->animationName = "anim_marisa_near_attackD";
	animData->intervalTime = 0.1f;
	animData->attackInfo.duration = 0.0f;
	for (int i = 0; i <= animData->endFrame - animData->startFrame; i++)
	{
		std::vector<CCGCollisionBox*> frameBoxes;
		auto box = CCGCollisionBox::create(Rect(0, 0, 100, 50), CCGCollisionBox::BOX_ATTACK);
		frameBoxes.push_back(box);
		animData->collisionData.push_back(frameBoxes);
	}
	CCGAnimation::createToCacheWithAnimationData(animData);

	// create an sprite without texture
	STGCharacterData* characterData = STGCharacterData::create();
	characterData->name = "marisa";
	characterData->actionMap[STGCharacter::ACTION_STATE_FLY_FORWARD] = "anim_marisa_fly_forward";
	characterData->actionMap[STGCharacter::ACTION_STATE_FLY_BACKWARD] = "anim_marisa_fly_backward";
	characterData->actionMap[STGCharacter::ACTION_STATE_NEAR_ATTACKA] = "anim_marisa_near_attackA";
	characterData->actionMap[STGCharacter::ACTION_STATE_NEAR_ATTACKB] = "anim_marisa_near_attackB";
	characterData->actionMap[STGCharacter::ACTION_STATE_NEAR_ATTACKC] = "anim_marisa_near_attackC";
	characterData->actionMap[STGCharacter::ACTION_STATE_NEAR_ATTACKD] = "anim_marisa_near_attackD";

	_marisa = STGPlayer::createWithCharacterData(characterData);
	addChild(_marisa.get());
	_marisa->setPosition3D(Vec3(-100, 0, 0));
	_marisa->runAction(STGCharacter::ACTION_STATE_FLY_FORWARD);

	// marisa_bulletAa
	animData = AnimationData::create();
	//memset(animData, 0, sizeof(AnimationData));
	animData->plistFile = "marisa/bulletAa.plist";
	animData->baseFrameName = "bulletAa";
	animData->bLoop = true;
	animData->startFrame = 0;
	animData->endFrame = 13;
	animData->animationName = "anim_marisa_bulletAa";
	animData->intervalTime = 0.1f;
	animData->attackInfo.duration = 0.0f;
	for (int i = 0; i <= animData->endFrame - animData->startFrame; i++)
	{
		std::vector<CCGCollisionBox*> frameBoxes;
		auto box = CCGCollisionBox::create(Rect(0, 0, 64, 64), CCGCollisionBox::BOX_ATTACK);
		frameBoxes.push_back(box);
		animData->collisionData.push_back(frameBoxes);
	}
	CCGAnimation::createToCacheWithAnimationData(animData);

	// marisa_bullet_script
	CCGLuaCache* luaCache = CCGLuaCache::getInstance();
	luaCache->addScriptWithFile("Scripts/luatest.lua", "script_marisa_bullet");

	// create spell data
	STGSpellData *spellData = STGSpellData::create();
	spellData->canDestory = true;
	spellData->duration = 5;
	spellData->scriptName = "script_marisa_bullet";
	spellData->startPosition = Point(50, 0);
	spellData->spellMap[STGSpell::SPELL_STATE_START] = "anim_marisa_bulletAa";

	CCGDataCache* dataCache = CCGDataCache::getInstance();
	dataCache->addData(spellData, "data_marisa_bulletAa");
}

void Level::CreateReimu()
{
	AnimationData *animData = AnimationData::create();
	//memset(animData, 0, sizeof(AnimationData));
	animData->plistFile = "reimu/fly.plist";
	animData->baseFrameName = "dashFrontAir";
	animData->bLoop = true;
	animData->startFrame = 0;
	animData->endFrame = 4;
	animData->animationName = "anim_reimu_fly";
	animData->intervalTime = 0.1f;
	for (int i = 0; i <= animData->endFrame - animData->startFrame; i++)
	{
		std::vector<CCGCollisionBox*> frameBoxes;
		auto box = CCGCollisionBox::create(Rect(0, 0, 50, 50), CCGCollisionBox::BOX_BODY);
		frameBoxes.push_back(box);
		animData->collisionData.push_back(frameBoxes);
	}
	CCGAnimation::createToCacheWithAnimationData(animData);

	// create an sprite without texture
	_reimu = STGRobot::create();
	_reimu->setName("reimu");
	_reimu->setPosition3D(Vec3(300, 0, 0));
	_reimu->setRotation3D(Vec3(0, 180, 0));
	addChild(_reimu.get());
	_reimu->runAnimation("anim_reimu_fly");
}