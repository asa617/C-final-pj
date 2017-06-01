//
//  ImageScene.cpp
//  mygame
//
//  Created by -T.c on 2017/5/26.
//
//

#include "ImageScene.hpp"

Scene* ImageScene::createScene(){
    auto scene = Scene::create();
    auto layer = ImageScene::create();
    scene->addChild(layer);
    return scene;
}

bool ImageScene::init(){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create("level_1_bg.png");
    sprite->setPosition(visibleSize.width/2,visibleSize.height/2);
    auto size = sprite->getContentSize();
    float scaleX = (float)visibleSize.width/(float)size.width;
    float scaleY = (float)visibleSize.height/(float)size.height;
    sprite->setScale(scaleX, scaleY);

    this->addChild(sprite);
    

    return true;
}
