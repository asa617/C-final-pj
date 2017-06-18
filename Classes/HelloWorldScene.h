#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "SettingScene.hpp"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void cleanup();
    
    void menuItemStartCallback(Ref* pSender);
    void menuItemSettingCallback(Ref* pSender);
    void menuItemLevelCallback(Ref* pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
