#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuPrintCallback();
    void menuItemToggle(Ref* pSender);
    void menuItemStartCallback(Ref* pSender);
    void menuItemSettingCallback(Ref* pSender);
    void menuItemLevelCallback(Ref* pSender);
    void menuItemAboutCallback(Ref* pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
