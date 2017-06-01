//
//  ImageScene.hpp
//  mygame
//
//  Created by -T.c on 2017/5/26.
//
//

#ifndef ImageScene_hpp
#define ImageScene_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class ImageScene:public Layer{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ImageScene);
};

#endif /* ImageScene_hpp */
