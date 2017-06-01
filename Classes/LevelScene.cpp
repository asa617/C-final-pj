//
//  LevelScene.cpp
//  mygame
//
//  Created by -T.c on 2017/5/31.
//
//

#include "LevelScene.hpp"

Scene* LevelScene::createScene(){
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
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto s = Sprite::create("game_bg.jpg");
    s->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(s);
    
    return true;
}

