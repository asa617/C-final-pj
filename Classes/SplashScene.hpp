//
//  SplashScene.hpp
//  test
//
//  Created by -T.c on 2017/6/17.
//
//

#ifndef SplashScene_hpp
#define SplashScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class SplashScene : public Layer
{
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(SplashScene);
    
private:
    Sprite* logoSprite;
    // 场景切换
    void nextScene(float dt);
    void loadingAudio();
    void onExit();
    std::thread* _loadingAudioThread;
};
#endif /* SplashScene_hpp */
