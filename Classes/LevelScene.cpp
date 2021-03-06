//
//  LevelScene.cpp
//  mygame
//
//  Created by -T.c on 2017/5/31.
//
//

#include "LevelScene.hpp"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GlobalData.h"
#include "GlobalDefine.h"
#include "SelectLevel.h"
#include "HelloWorldScene.h"
#include "ImageScene.hpp"

USING_NS_CC;
using namespace CocosDenshion;

Scene* LevelScene::createScene()
{
    auto scene = Scene::create();
    auto layer = LevelScene::create();
    scene->addChild(layer);
    return scene;
}

bool LevelScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    if (getBoolFromXML(MUSIC_KEY))
    {
        if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
        {
            aduioEngine->pauseBackgroundMusic();
            aduioEngine->playBackgroundMusic("background2.mp3", true);
        }
        else
            aduioEngine->playBackgroundMusic("background2.mp3", true);
    }
    else
        aduioEngine->pauseBackgroundMusic();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    bgPic = Sprite::create("selectBg.jpg");
    bgPic->setPosition(WINSIZE.width / 2.0, WINSIZE.height / 2);
    auto size = bgPic->getContentSize();
    float scaleX = (float)visibleSize.width/(float)size.width;
    float scaleY = (float)visibleSize.height/(float)size.height;
    bgPic->setScale(scaleX, scaleY);
    this->addChild(bgPic);
    
    auto closeItem = MenuItemImage::create(
                                           "backA.png",
                                           "backB.png",
                                           CC_CALLBACK_1(LevelScene::closeFunc, this)); // 退出
    
    auto challengeItem = MenuItemImage::create(
                                               "battle.png",
                                               "battle.png",
                                               CC_CALLBACK_1(LevelScene::challengeFunc, this)); // 挑战
    
    closeItem->setPosition(WINSIZE.width-50 , WINSIZE.height / 12);
    challengeItem->setPosition(WINSIZE.width / 2, WINSIZE.height / 7);
    auto menu = Menu::create(closeItem, challengeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    auto gateOneItem = MenuItemImage::create(
                                             "choose_level1.png",
                                             "choose_level1.png",
                                             CC_CALLBACK_1(LevelScene::gateOneCallBack, this)); // 退出
    
    auto gateTwoItem = MenuItemImage::create(
                                             "choose_level2.png",
                                             "choose_level2.png",
                                             CC_CALLBACK_1(LevelScene::gateTwoCallBack, this)); // 退出
    
    auto gateThreeItem = MenuItemImage::create(
                                               "choose_level3.png",
                                               "choose_level3.png",
                                               CC_CALLBACK_1(LevelScene::gateThreeCallBack, this)); // 退出
    
    selectGateMenu = SelectLevel::create();
    selectGateMenu->addMenuItem(gateOneItem);
    selectGateMenu->addMenuItem(gateTwoItem);
    selectGateMenu->addMenuItem(gateThreeItem);
    selectGateMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 74);
    this->addChild(selectGateMenu, 2);
    
        return true;
}

//回调函数
void LevelScene::gateOneCallBack(cocos2d::Ref* pSender)
{
    PLAYEFFECT;
    setIntToXML(GAMELEVEL_KEY, 1);
    setIntToXML(SELECTGATE, 1);
    UserDefault::getInstance()->flush();
    m_iSelectGate = 1;
    log("First gate select!");
    Director::getInstance()->replaceScene(TransitionTurnOffTiles::create(1.0f, ImageScene::createScene()));
}
void LevelScene::gateTwoCallBack(cocos2d::Ref* pSender)
{
    PLAYEFFECT;
        setIntToXML(GAMELEVEL_KEY, 2);
        setIntToXML(SELECTGATE, 2);
        UserDefault::getInstance()->flush();
        m_iSelectGate = 2;
		iLevel = 2;
        Director::getInstance()->replaceScene(TransitionTurnOffTiles::create(1.0f, ImageScene::createScene()));
}
void LevelScene::gateThreeCallBack(cocos2d::Ref* pSender)
{
    PLAYEFFECT;
        setIntToXML(GAMELEVEL_KEY, 3);
        setIntToXML(SELECTGATE, 3);
        UserDefault::getInstance()->flush();
        m_iSelectGate = 3;
		iLevel = 3;
        Director::getInstance()->replaceScene(TransitionTurnOffTiles::create(1.0f, ImageScene::createScene()));
}

void LevelScene::closeFunc(Ref* pSender)
{
    PLAYEFFECT;
    SimpleAudioEngine::getInstance()->stopBackgroundMusic("background2.mp3");
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}
void LevelScene::challengeFunc(Ref* pSender)
{
    PLAYEFFECT;
    SimpleAudioEngine::getInstance()->stopBackgroundMusic("background2.mp3");
    selectGateMenu->getCurrentItem()->activate();
} 
