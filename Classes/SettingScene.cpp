//
//  SettingScene.cpp
//  mygame
//
//  Created by -T.c on 2017/5/31.
//
//

#include "SettingScene.hpp"

Scene* SettingScene::createScene(){
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
    
    //sound button
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
    
    //music button
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
    
    //back to menu
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
}

void SettingScene::menuSoundToggleCallback(Ref* pSender)
{
    
}

void SettingScene::menuMusicToggleCallback(Ref* pSender)
{
    
}

