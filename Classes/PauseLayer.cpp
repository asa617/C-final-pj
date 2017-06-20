#include "PauseLayer.h"
#include "GlobalDefine.h"
#include "GlobalData.h"
#include "ImageScene.hpp"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "SelectedLevel.h"
#include "LevelScene.hpp"

USING_NS_CC;
using namespace cocos2d::extension;

Scene* PauseLayer::createScene(char* name)
{
	Scene* scene = Scene::create();
	PauseLayer* layer = PauseLayer::create();

	auto sprite = Sprite::create(name);
	sprite->setPosition(WINSIZE.width / 2, WINSIZE.height / 2-10);
	sprite->setScaleX(1.2);
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

	//继续游戏按钮
	auto ResumeItem = MenuItemSprite::create(Sprite::create("Resume.png"), Sprite::create("Resume.png"), [&](Ref *ref)
	{
		CallFunc* replace = CallFunc::create([]() {Director::getInstance()->popScene(); });
		runAction(replace);
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

}

void PauseLayer::musicSet(Ref* pSender)
{
	auto musicTemp = (MenuItemToggle*)pSender;
}

void PauseLayer::GameOver(float delta)
{
	String *name = String::createWithFormat("level_%d_bg.png", iLevel);
	auto BgMap = Sprite::create(name->getCString());
	auto visibleSize = Director::getInstance()->getVisibleSize();
	BgMap->setPosition(getContentSize().width / 2, getContentSize().height / 2);
	auto size = BgMap->getContentSize();
	float scaleX = (float)visibleSize.width / (float)size.width;
	float scaleY = (float)visibleSize.height / (float)size.height;
	BgMap->setScale(scaleX, scaleY);
	addChild(BgMap, 4);

	auto ResumeItem = MenuItemSprite::create(
		Sprite::create("Resume.png"), Sprite::create("Resume.png"), [&](Ref *ref)
	{
		Director::getInstance()->replaceScene(LevelScene::createScene()); });
	ResumeItem->setScale(0.2);
	ResumeItem->setPosition(250, 200);

	auto StartItem = MenuItemSprite::create(
		Sprite::create("Home.png"), Sprite::create("Home.png"), [&](Ref *ref)
	{
		Director::getInstance()->replaceScene(HelloWorld::createScene()); });
	StartItem->setScale(0.1);
	StartItem->setPosition(380, 200);

	auto GameLose = Sprite::create("gameover.png");
	GameLose->setPosition(visibleSize.width / 2-100, visibleSize.height / 2 - 10);
	BgMap->addChild(GameLose);

	auto menu = Menu::create(ResumeItem, StartItem,NULL);
	menu->setPosition(Point::ZERO);
	BgMap->addChild(menu);
} 

void PauseLayer::GameWin(float delta)
{
	String *name = String::createWithFormat("level_%d_bg.png", iLevel);
	auto BgMap = Sprite::create(name->getCString());
	auto visibleSize = Director::getInstance()->getVisibleSize();
	BgMap->setPosition(getContentSize().width / 2, getContentSize().height / 2);
	auto size = BgMap->getContentSize();
	float scaleX = (float)visibleSize.width / (float)size.width;
	float scaleY = (float)visibleSize.height / (float)size.height;
	BgMap->setScale(scaleX, scaleY);
	addChild(BgMap,4);

	auto ResumeItem = MenuItemSprite::create(
		Sprite::create("Resume.png"), Sprite::create("Resume.png"), [&](Ref *ref)
	{
		Director::getInstance()->replaceScene(LevelScene::createScene()); });
		ResumeItem->setScale(0.35);
		ResumeItem->setPosition(320, 150);

	auto StartItem = MenuItemSprite::create(
		Sprite::create("Home.png"), Sprite::create("Home.png"), [&](Ref *ref)
	{
		Director::getInstance()->replaceScene(HelloWorld::createScene()); });
		StartItem->setScale(0.2);
		StartItem->setPosition(420, 150);

		auto GameWin = Sprite::create("victory.png");
		GameWin->setPosition(visibleSize.width / 2-40, visibleSize.height / 2 - 10);
		GameWin->setScale(0.5);
		BgMap->addChild(GameWin);

		auto menu = Menu::create(ResumeItem, StartItem, NULL);
		menu->setPosition(Point::ZERO);
		BgMap->addChild(menu);
}