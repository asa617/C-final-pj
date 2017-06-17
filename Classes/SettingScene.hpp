//
//  SettingScene.hpp
//  mygame
//
//  Created by -T.c on 2017/5/31.
//
//

#ifndef SettingScene_hpp
#define SettingScene_hpp

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
USING_NS_CC;

class SettingScene:public Layer
{
    bool isEffect;
public:
    static Scene* createScene();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void cleanup();
    
    void menuSoundToggleCallback(Ref* pSender);
    void menuMusicToggleCallback(Ref* pSender);
    void menuOkCallback(Ref* pSender);
    
    CREATE_FUNC(SettingScene);
};

#endif /* SettingScene_hpp */
