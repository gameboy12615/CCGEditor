#pragma once

#include "cocos2d.h"
#include "CCSTG.h"

NS_CC_BEGIN
class Level : public cocos2d::Layer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Level);

	void updateLayer(float fDelta);
	void update(float delta);
	void CreateMarisa();
	void CreateReimu();

protected:
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	void onDraw(const Mat4 &transform, uint32_t flags);
	CustomCommand _customCommand;
	CCPtr<STGPlayer> _marisa;
	CCPtr<STGRobot> _reimu;
	CCPtr<DrawNode> _drawNode;
};

NS_CC_END