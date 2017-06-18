#include"PauseLayer.h"
#include"cocos2d.h"
#include"GlobalDefine.h"
#include"HelloWorldScene.h"
#include"GlobalData.h"
#include"extensions/cocos-ext.h"
#include"ImageScene.cpp"
/*
Scene* PauseLayer::createScene(RenderTexture* rt)
{
	Scene* scene = Scene::create();
	PauseLayer* layer = PauseLayer::create();

	auto sprite = Sprite::createWithTexture(rt->getSprite()->getTexture());
	sprite->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	sprite->setFlippedY(true);
	//	sprite->setColor(cocos2d::ccGRAY);
	scene->addChild(sprite, 0);

	scene->addChild(layer);

	return scene;
}

bool PauseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto size = Director::getInstance()->getWinSize();

	// 背景黑色的图片
	spriteOn = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pauseBG1.png"));
	spriteDown = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pauseBG2.png"));
	spriteOn->setPosition(size.width / 2, size.height + spriteOn->getContentSize().height / 2);
	spriteDown->setPosition(size.width / 2, -(spriteDown->getContentSize().height / 2));
	this->addChild(spriteOn);
	this->addChild(spriteDown);

	// 继续游戏按钮
	auto resumeItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("playNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("playSelected.png")),
		[&](Ref * ref) {
		//PLAYEFFECT;
		//弹出保存的场景
		auto moveOn = MoveBy::create(0.5f, Point(0, (spriteOn->getContentSize().height)));
		auto moveDown = MoveBy::create(0.5f, Point(0, -spriteDown->getContentSize().height));
		CallFunc* replace = CallFunc::create([]() {Director::getInstance()->popScene(); });
		Action* resume = Sequence::create(moveOn, replace, NULL);
		spriteDown->runAction(moveDown);
		spriteOn->runAction(resume);
	});

}*/