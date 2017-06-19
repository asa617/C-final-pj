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
#include  "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class SelectLevel;

class LevelScene:public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LevelScene);

    Sprite *bgPic;
    Sprite *closeBtn;
    Sprite *tips;
    
    SelectLevel* selectGateMenu;
    
    void gateOneCallBack(Ref* pSender);
    void gateTwoCallBack(Ref* pSender);
    void gateThreeCallBack(Ref* pSender);
    
    void closeFunc(Ref* pSender);
    void challengeFunc(Ref* pSender);
    
};

#endif /* LevelScene_hpp */
