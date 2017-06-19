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
            aduioEngine->playBackgroundMusic("gateMap.wav", true);
        }
        else
            aduioEngine->playBackgroundMusic("gateMap.wav", true);
    }
    else
        aduioEngine->pauseBackgroundMusic();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gateMap.plist");
    
    bgPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("GateMapBG.png"));
    bgPic->setPosition(WINSIZE.width / 2.0, WINSIZE.height / 2);
    this->addChild(bgPic);
    
    auto closeItem = MenuItemSprite::create(
                                            Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CloseNormal.png")),
                                            Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CloseSelected.png")),
                                            CC_CALLBACK_1(LevelScene::closeFunc, this)); // 退出
    
    auto challengeItem = MenuItemSprite::create(
                                                Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tiaozhanNormal.png")),
                                                Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tiaozhanSelected.png")),
                                                CC_CALLBACK_1(LevelScene::challengeFunc, this)); // 挑战
    
    closeItem->setPosition(WINSIZE.width - 47, WINSIZE.height - 44);
    challengeItem->setPosition(WINSIZE.width - 253, 7 * WINSIZE.height / 72);
    auto menu = Menu::create(closeItem, challengeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    auto gateOneItem = MenuItemSprite::create(
                                              Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1.png")),
                                              Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1.png")),
                                              CC_CALLBACK_1(LevelScene::gateOneCallBack, this)); // 退出
    
    auto gateTwoItem = MenuItemSprite::create(
                                              Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_2.png")),
                                              Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_2.png")),
                                              CC_CALLBACK_1(LevelScene::gateTwoCallBack, this)); // 退出
    
    auto gateThreeItem = MenuItemSprite::create(
                                                Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_3.png")),
                                                Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_3.png")),
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
    Director::getInstance()->replaceScene(ImageScene::createScene());
}
void LevelScene::gateTwoCallBack(cocos2d::Ref* pSender)
{
    PLAYEFFECT;
    log("Second gate select!");
    if (getBoolFromXML(GATEONE, false))
    {
        setIntToXML(GAMELEVEL_KEY, 2);
        setIntToXML(SELECTGATE, 2);
        UserDefault::getInstance()->flush();
        m_iSelectGate = 2;
        Director::getInstance()->replaceScene(ImageScene::createScene());
        
    }
}
void LevelScene::gateThreeCallBack(cocos2d::Ref* pSender)
{
    PLAYEFFECT;
    log("Third gate select!");
    if (getBoolFromXML(GATETWO, false))
    {
        setIntToXML(GAMELEVEL_KEY, 3);
        setIntToXML(SELECTGATE, 3);
        UserDefault::getInstance()->flush();
        m_iSelectGate = 3;
        Director::getInstance()->replaceScene(ImageScene::createScene());
    }
    else
    {
        //Label * label = Label::cr("");
    }
}

void LevelScene::closeFunc(Ref* pSender)
{
    PLAYEFFECT;
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}
void LevelScene::challengeFunc(Ref* pSender)
{
    PLAYEFFECT;
    selectGateMenu->getCurrentItem()->activate();
    // 	m_iSelectGate = 1;
    // 	Director::getInstance()->replaceScene(GameLayer::createScene());
} 
