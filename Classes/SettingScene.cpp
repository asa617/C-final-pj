//
//  SettingScene.cpp
//  mygame
//
//  Created by -T.c on 2017/5/31.
//
//

#include "SettingScene.hpp"
USING_NS_CC;
using namespace CocosDenshion;

Scene* SettingScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SettingScene::create();
    scene->addChild(layer);
    return scene;
}

bool SettingScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto s = Sprite::create("optionbg.png");
    s->setPosition(visibleSize.width/2,visibleSize.height/2);
    auto size = s->getContentSize();
    float scaleX = (float)visibleSize.width/(float)size.width;
    s->setScale(scaleX, scaleX);
    this->addChild(s);
    
    //音效
    auto soundOnMenuItem = MenuItemImage::create(
                                                 "on.png",
                                                 "on.png");
    auto soundOffMenuItem = MenuItemImage::create(
                                                  "off.png",
                                                  "off.png");
    auto soundToggleMenuItem = MenuItemToggle::createWithCallback(
                                                CC_CALLBACK_1(SettingScene::menuSoundToggleCallback, this),
                                                                  soundOnMenuItem,
                                                                  soundOffMenuItem,
                                                                  NULL);
    soundToggleMenuItem->setPosition(570,375);
    
    //背景音乐
    auto musicOnMenuItem = MenuItemImage::create(
                                                 "on.png",
                                                 "on.png");
    auto musicOffMenuItem = MenuItemImage::create(
                                                  "off.png",
                                                  "off.png");
    auto musicToggleMenuItem = MenuItemToggle::createWithCallback(
                                                CC_CALLBACK_1(SettingScene::menuMusicToggleCallback, this),
                                                                  musicOnMenuItem,
                                                                  musicOffMenuItem,
                                                                  NULL);
    musicToggleMenuItem->setPosition(570,250);
    
    //返回菜单
    auto okMenuItem = MenuItemImage::create(
                                            "backtomenu.png",
                                            "backtomenu.png",
                                            CC_CALLBACK_1(SettingScene::menuOkCallback, this));
    
    okMenuItem->setPosition(450,140);
    
    auto mn = Menu::create(soundToggleMenuItem,musicToggleMenuItem,okMenuItem,NULL);
    mn->setPosition(Vec2::ZERO);
    this->addChild(mn);

    
    
    
    return true;
}

void SettingScene::menuOkCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
    if(isEffect){
        SimpleAudioEngine::getInstance()->playEffect("button.wav");
    }
}

void SettingScene::menuSoundToggleCallback(Ref* pSender)
{
    auto soundToggleMenuItem = (MenuItemToggle*)pSender;
    if(isEffect){
        SimpleAudioEngine::getInstance()->playEffect("button.wav");
    }
    
    if(soundToggleMenuItem->getSelectedIndex() == 1){//选中状态 off->on
        isEffect = false;
    }else{
        isEffect = true;
        SimpleAudioEngine::getInstance()->playEffect("button.wav");
    }
}

void SettingScene::menuMusicToggleCallback(Ref* pSender)
{
    auto musicToggleMenuItem = (MenuItemToggle*)pSender;
    if(musicToggleMenuItem->getSelectedIndex() == 1){//选中状态 off->on
        SimpleAudioEngine::getInstance()->stopBackgroundMusic("background.mp3");
    }else{
        SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3");
    }
    if(isEffect){
        SimpleAudioEngine::getInstance()->playEffect("button.wav");
    }
}

void SettingScene::onEnter()
{
    Layer::onEnter();
    log("Setting onEnter");
}

void SettingScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    log("Setting onEnterTransitonDidFinsh");
    isEffect = true;
    //播放
    SimpleAudioEngine::getInstance()->playBackgroundMusic("background1.mp3");
}

void SettingScene::onExit()
{
    Layer::onExit();
    log("Setting onExit");
}

void SettingScene::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
    log("Setting onExitTransitionDidStart");
}

void SettingScene::cleanup()
{
    Layer::cleanup();
    log("Setting cleanup");
    //停止
    SimpleAudioEngine::getInstance()->stopBackgroundMusic("background1.mp3");
}

