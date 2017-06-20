//
//  SplashScene.cpp
//  test
//
//  Created by -T.c on 2017/6/17.
//
//

#include "SplashScene.hpp"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* SplashScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SplashScene::create();
    scene->addChild(layer);
    return scene;
}

bool SplashScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //  初始化logo精灵
    auto visibleSize = Director::getInstance()->getVisibleSize();
    logoSprite = Sprite::create("splash.jpeg");
    logoSprite->setPosition(visibleSize.width/2, visibleSize.height/2);
    auto size = logoSprite->getContentSize();
    float scaleX = (float)visibleSize.width/(float)size.width;
    float scaleY = (float)visibleSize.height/(float)size.height;
    logoSprite->setScale(scaleX, scaleY);
    this->addChild(logoSprite);
    
    //音乐线程 异步处理
    _loadingAudioThread = new std::thread(&SplashScene::loadingAudio, this);
    
    this->schedule(schedule_selector(SplashScene::nextScene), 1, 1, 1);
    
    return true;
}

void SplashScene::loadingAudio()
{
    log("loadAudio");
    //初始化 音乐
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background1.mp3");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background2.mp3");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("gameBGM.wav");

    //初始化音效
    SimpleAudioEngine::getInstance()->preloadEffect("button.wav");
}

void SplashScene::nextScene(float dt)
{
    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, HelloWorld::createScene()));
}

void SplashScene::onExit()
{
    Layer::onExit();
    _loadingAudioThread->join();
    CC_SAFE_DELETE(_loadingAudioThread);
    this->unschedule(schedule_selector(SplashScene::nextScene));
}

