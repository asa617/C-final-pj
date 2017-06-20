//
//  ImageScene.cpp
//  mygame
//
//  Created by -T.c on 2017/5/26.
//  Added by loahao on 2017/6/10
//

#include "ImageScene.hpp"
#include "cocos2d.h"
#include "Hero.h"
#include "OperateLayer.h"
#include "GlobalDefine.h"
#include "MonsterControl.h"


class Hero;


Scene* ImageScene::createScene(){ //创建场景
    auto scene = Scene::create();
    auto layer = ImageScene::create();
    scene->addChild(layer);
    return scene;
}

bool ImageScene::init(){   //场景初始化
	if (!Layer::init())
	return false;
    //更改bgm
    if (getBoolFromXML(MUSIC_KEY))
    {
        if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
        {
            aduioEngine->pauseBackgroundMusic();
            aduioEngine->playBackgroundMusic("gameBGM.wav", true);
        }
        else
            aduioEngine->playBackgroundMusic("gameBGM.wav", true);
    }
    else
        aduioEngine->pauseBackgroundMusic();
    //地图载入
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto BgMap = Sprite::create("level_1_bg.png");
    BgMap->setPosition(getContentSize().width / 2,getContentSize().height / 2);
    auto size = BgMap->getContentSize();
	float scaleX = (float)visibleSize.width/(float)size.width;
    float scaleY = (float)visibleSize.height/(float)size.height;
    BgMap->setScale(scaleX, scaleY);
    this->addChild(BgMap,0);

	//添加英雄
	m_pHero = Hero::create();
	m_pHero->InitHeroSprite("Hero1.png", 1);
	m_pHero->setPosition(100, 250);
	this->addChild(m_pHero);

	MonsterControl *monster = MonsterControl::createWithHeroAndMap(m_pHero,BgMap);

	//添加按钮
	OperateLayer *pOperateLayer = OperateLayer::create();
	pOperateLayer->setDelegate(this);
	addChild(pOperateLayer);

	//暂停按钮
	auto pauseGameItem = MenuItemImage::create(
		                                       "pause.png",
		                                       "pause.png",
		                                       CC_CALLBACK_1(ImageScene::gamePauseCallback, this));
    pauseGameItem->setScale(0.15);
	pauseGameItem->setPosition(visibleSize.width-50,visibleSize.height-45);
    auto menu = Menu::create(pauseGameItem,nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu,3);

	//添加血条、能量条
	HpAndMpBg = Sprite::create("hpmpbg.png");
	HpAndMpBg->setPosition(130,visibleSize.height-50);
	auto HpMpSize = HpAndMpBg->getContentSize();
	HpBar = ProgressTimer::create(Sprite::create("hp.png"));
	HpBar->setType(ProgressTimer::Type::BAR);
	HpBar->setMidpoint(ccp(0, 0.5));
	HpBar->setBarChangeRate(ccp(1, 0));
	HpBar->setPercentage(100);
	HpBar->setPosition(138, visibleSize.height - 32);
	this->addChild(HpBar,2);
	MpBar = ProgressTimer::create(Sprite::create("mp.png"));
	MpBar->setType(ProgressTimer::Type::BAR);
	MpBar->setMidpoint(ccp(0, 0.5));
	MpBar->setBarChangeRate(ccp(1, 0));
	MpBar->setPercentage(0);
	MpBar->setPosition(78,visibleSize.height - 70);
	this->addChild(MpBar,2);
	this->addChild(HpAndMpBg, 1);


	this->scheduleUpdate();
	return true;
}


void ImageScene::attackButtonClick(int nAttackType)
{
	m_pHero->Attack(nAttackType);
}

void ImageScene::gamePauseCallback(Ref* pSender) {
    Director::getInstance()->pause();
}
