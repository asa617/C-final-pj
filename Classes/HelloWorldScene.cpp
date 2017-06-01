#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ImageScene.hpp"
#include "SettingScene.hpp"
#include "LevelScene.hpp"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("-W A R R I O R-", "fonts/Marker Felt.ttf", 65);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2 + label->getContentSize().height*3));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("home.jpeg");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    auto size = sprite->getContentSize();
    float scaleX = (float)visibleSize.width/(float)size.width;
    float scaleY = (float)visibleSize.height/(float)size.height;
    sprite->setScale(scaleX, scaleY);

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    auto startMenuItem = MenuItemImage::create(
                                               "playgameA.png",
                                               "playgameB.png",
                                               CC_CALLBACK_1(HelloWorld::menuItemStartCallback, this));
    startMenuItem->setPosition(450,390);
    
    auto settingMenuItem = MenuItemImage::create(
                                               "optionA.png",
                                               "optionB.png",
                                               CC_CALLBACK_1(HelloWorld::menuItemSettingCallback, this));
    settingMenuItem->setPosition(450,190);
    
    auto levelMenuItem = MenuItemImage::create(
                                                 "levelA.png",
                                                 "levelB.png",
                                                 CC_CALLBACK_1(HelloWorld::menuItemLevelCallback, this));
    levelMenuItem->setPosition(450,290);
    
    auto mu = Menu::create(startMenuItem,settingMenuItem,levelMenuItem,nullptr);
    mu->setPosition(Vec2::ZERO);
    this->addChild(mu);
    
    /*auto label1 = Label::createWithTTF("show next scene", "fonts/arial.ttf", 36);
    addChild(label1);
    label1->setPosition(visibleSize.width/2, visibleSize.height/2);
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [label1](Touch* t,Event* e){
        if(label1->getBoundingBox().containsPoint(t->getLocation())){
            Director::getInstance()->replaceScene(TransitionFadeBL::create(1, ImageScene::createScene()));
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label1);
    */
       
        return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::menuItemSettingCallback(Ref* pSender)
{
    auto sc = SettingScene::createScene();
    Director::getInstance()->pushScene(sc);
}

void HelloWorld::menuItemStartCallback(Ref* pSender)
{
    auto sc = ImageScene::createScene();
    Director::getInstance()->pushScene(sc);
}

void HelloWorld::menuItemLevelCallback(Ref* pSender)
{
    auto sc = LevelScene::createScene();
    Director::getInstance()->pushScene(sc);
}
