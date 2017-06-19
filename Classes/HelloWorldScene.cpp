#include "HelloWorldScene.h"
#include "ImageScene.hpp"
#include "SettingScene.hpp"
#include "LevelScene.hpp"
#include "GlobalDefine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //右下角退出游戏按键
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    //标题
    auto label = Label::createWithTTF("-W A R R I O R-", "fonts/Marker Felt.ttf", 65);
    
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2 + label->getContentSize().height*3));

    this->addChild(label, 1);

    auto sprite = Sprite::create("home.jpeg");
    
    //强行适配窗体
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    auto size = sprite->getContentSize();
    float scaleX = (float)visibleSize.width/(float)size.width;
    float scaleY = (float)visibleSize.height/(float)size.height;
    sprite->setScale(scaleX, scaleY);

    this->addChild(sprite, 0);
    
    //添加菜单选项
    //开始游戏图片菜单
    auto startMenuItem = MenuItemImage::create(
                                               "playgameA.png",
                                               "playgameB.png",
                                               CC_CALLBACK_1(HelloWorld::menuItemStartCallback, this));
    startMenuItem->setPosition(450,390);
    //设置图片菜单
    auto settingMenuItem = MenuItemImage::create(
                                               "optionA.png",
                                               "optionB.png",
                                               CC_CALLBACK_1(HelloWorld::menuItemSettingCallback, this));
    settingMenuItem->setPosition(450,190);
    //选关图片菜单
    auto levelMenuItem = MenuItemImage::create(
                                                 "levelA.png",
                                                 "levelB.png",
                                                 CC_CALLBACK_1(HelloWorld::menuItemLevelCallback, this));
    levelMenuItem->setPosition(450,290);
    
    auto mu = Menu::create(startMenuItem,settingMenuItem,levelMenuItem,nullptr);
    mu->setPosition(Vec2::ZERO);
    this->addChild(mu);
    
    //添加火焰粒子效果
    ParticleSystem* particleSystem1 = ParticleFire::create();
    particleSystem1->setPosition(220, 395);
    this->addChild(particleSystem1);
    
    ParticleSystem* particleSystem2 = ParticleFire::create();
    particleSystem2->setPosition(700, 395);
    this->addChild(particleSystem2);
    
        return true;
}

//退出回调函数
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //退出游戏
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//设置回调函数
void HelloWorld::menuItemSettingCallback(Ref* pSender)
{
    auto sc = SettingScene::createScene();
    auto tsc = TransitionSlideInL::create(1.0f, sc);
    Director::getInstance()->pushScene(tsc);
    
    if(getBoolFromXML(SOUND_KEY)){
        PLAYEFFECT;
    }
}

//开始游戏回调函数
void HelloWorld::menuItemStartCallback(Ref* pSender)
{
    auto sc = ImageScene::createScene();
    auto tsc = TransitionTurnOffTiles::create(1.0f, sc);
    Director::getInstance()->pushScene(tsc);
    
    if(getBoolFromXML(SOUND_KEY)){
        PLAYEFFECT;
    }
}

//选关回调函数
void HelloWorld::menuItemLevelCallback(Ref* pSender)
{
    auto sc = LevelScene::createScene();
    auto tsc = TransitionSlideInL::create(1.0f, sc);
    Director::getInstance()->pushScene(tsc);
    
    if(getBoolFromXML(SOUND_KEY)){
        PLAYEFFECT;
    }
}

void HelloWorld::onEnter()
{
    Layer::onEnter();
    log("HelloWorld onEnter");
}

void HelloWorld::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    log("HelloWorld onEnterTransitionDidFinish");
    //播放
    if(getBoolFromXML(MUSIC_KEY)){
        SimpleAudioEngine::getInstance()->playBackgroundMusic("background1.mp3",true);
    }
}

void HelloWorld::onExit()
{
    Layer::onExit();
    log("HelloWorld onExit");
}

void HelloWorld::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
    log("HelloWorld onExitTransitionDidStart");
}

void HelloWorld::cleanup()
{
    Layer::cleanup();
    log("HelloWorld cleanup");
    //停止
    SimpleAudioEngine::getInstance()->stopBackgroundMusic("background1.mp3");
}
