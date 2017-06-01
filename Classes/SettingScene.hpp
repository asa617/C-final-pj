//
//  SettingScene.hpp
//  mygame
//
//  Created by -T.c on 2017/5/31.
//
//

#ifndef SettingScene_hpp
#define SettingScene_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class SettingScene:public Layer{
public:
    static Scene* createScene();
    virtual bool init();
    void menuSoundToggleCallback(Ref* pSender);
    void menuMusicToggleCallback(Ref* pSender);
    void menuOkCallback(Ref* pSender);
    CREATE_FUNC(SettingScene);
};

#endif /* SettingScene_hpp */
