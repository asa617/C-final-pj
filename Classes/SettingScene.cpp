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
    
    //设置开关菜单状态
    UserDefault* defaults = UserDefault::getInstance();
    if(defaults->getBoolForKey(MUSIC_KEY)){
        musicToggleMenuItem->setSelectedIndex(0);
    }else{
        musicToggleMenuItem->setSelectedIndex(1);
    }
    
    if(defaults->getBoolForKey(SOUND_KEY)){
        soundToggleMenuItem->setSelectedIndex(0);
    }else{
        soundToggleMenuItem->setSelectedIndex(1);
    }
    
    
    return true;
}

void SettingScene::menuOkCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
    
    if(getBoolFromXML(SOUND_KEY)){
        PLAYEFFECT;
    }
}

void SettingScene::menuSoundToggleCallback(Ref* pSender)
{
    auto soundToggleMenuItem = (MenuItemToggle*)pSender;
    log("soundToggleMenuItem %d",soundToggleMenuItem->getSelectedIndex());
    
    if(getBoolFromXML(SOUND_KEY)){
        setBoolToXML(SOUND_KEY,false);
    }else{
        setBoolToXML(SOUND_KEY,true);
        PLAYEFFECT;
    }
}

void SettingScene::menuMusicToggleCallback(Ref* pSender)
{
    auto musicToggleMenuItem = (MenuItemToggle*)pSender;
    log("musicToggleMenuItem %d",musicToggleMenuItem->getSelectedIndex());
    
    if(getBoolFromXML(MUSIC_KEY)){
        setBoolToXML(MUSIC_KEY,false);
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }else{
        setBoolToXML(MUSIC_KEY,true);
        PLAYEFFECT;
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
    
    if(getBoolFromXML(MUSIC_KEY)){
        //播放
        SimpleAudioEngine::getInstance()->playBackgroundMusic("background1.mp3",true);
    }
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

