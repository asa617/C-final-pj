//
//  LevelScene.hpp
//  mygame
//
//  Created by -T.c on 2017/5/31.
//
//

#ifndef LevelScene_hpp
#define LevelScene_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class LevelScene:public Layer{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LevelScene);
};

#endif /* LevelScene_hpp */
