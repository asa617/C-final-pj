#include "PauseLayer.h"
#include "GlobalDefine.h"
#include "GlobalData.h"
#include "ImageScene.hpp"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace cocos2d::extension;

Scene* PauseLayer::createScene(char* name)
{
	Scene* scene = Scene::create();
	PauseLayer* layer = PauseLayer::create();

	auto sprite = Sprite::create(name);
	sprite->setPosition(WINSIZE.width / 2, WINSIZE.height / 2-10);
	sprite->setScaleX(1.2);
	//sprite->setFlippedY(true);
	scene->addChild(sprite, 0);
	scene->addChild(layer);

	return scene;
}

bool PauseLayer::init()
{
	if(!Layer::init())
	{
	return false;
	}

	auto size = Director::getInstance()->getWinSize();

	// 背景黑色的图片  

	//spriteOn = Sprite::create("PausePic.png");
	//spriteOn->setPosition(size.width, size.height);
	//spriteOn->setPosition(size.width  / 2, size.height  + spriteOn->getContentSize().height  / 2);
	//spriteDown->setPosition(size.width  / 2, -(spriteDown->getContentSize().height  / 2));
	//this->addChild(spriteOn);

	//继续游戏按钮
	auto ResumeItem = MenuItemSprite::create(Sprite::create("Resume.png"), Sprite::create("Resume.png"), [&](Ref *ref)
	{
		CallFunc* replace = CallFunc::create([]() {Director::getInstance()->popScene(); });
		runAction(replace);
		//Director::getInstance()->resume();
	});
	ResumeItem->setScale(0.5);
	ResumeItem->setPosition(130,320);


	// 返回游戏主界面  
	auto StartItem = MenuItemSprite::create(
		Sprite::create("Home.png"),Sprite::create("Home.png"),[&](Ref *ref)
		{//弹出保存的场景  
		Director::getInstance()->replaceScene(HelloWorld::createScene()); });
	StartItem->setScale(0.3);
	StartItem->setPosition(330.0, 320);

	// 重新开始游戏 
		auto AgainItem = MenuItemSprite::create(
		Sprite::create("Restart.png"), Sprite::create("Restart.png"),[&](Ref *ref)
		{//弹出保存的场景  
		Director::getInstance()->replaceScene(ImageScene::createScene()); });
		AgainItem->setScale(0.3);
		AgainItem->setPosition(530.0, 320.0);

	// 声音设置按钮  
		auto MusicOn = MenuItemSprite::create(Sprite::create("Voice.png"), Sprite::create("VoiceOff.png"));
		auto MusicOff = MenuItemSprite::create(Sprite::create("VoiceOff.png"), Sprite::create("Voice.png"));
		auto MusicToggle = MenuItemToggle::createWithTarget(this,menu_selector(PauseLayer::musicSet),MusicOn,MusicOff,NULL);
		MusicToggle->setScale(0.3);
		MusicToggle->setPosition(730, 320);
		auto menu = Menu::create(ResumeItem, StartItem, AgainItem, MusicToggle, NULL);
		menu->setPosition(Point::ZERO);
		addChild(menu);
		//auto moveDown = MoveBy::create(0.6, Point(0, -(spriteOn->getContentSize().height)));
		//spriteOn->runAction(moveDown);

}

void PauseLayer::musicSet(Ref* pSender)
{
	auto musicTemp = (MenuItemToggle*)pSender;

}
