//
//  LevelScene.hpp
//  mygame
//
//  Created by -T.c on 2017/5/31.
//  Added by loahao on 2017/6/11.
//

#ifndef LevelScene_hpp
#define LevelScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include  "extensions/cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class LevelScene:public Layer{
public:
    static Scene* createScene();
	//≥ı ºªØ
    virtual bool init();
    CREATE_FUNC(LevelScene);

private:

};

#endif /* LevelScene_hpp */
