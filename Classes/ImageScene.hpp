//
//  ImageScene.hpp
//  mygame
//
//  Created by -T.c on 2017/5/26.
//  Added by loahao on 2017/6/9
<<<<<<< HEAD
=======
//  Added by Xuan_32 on 2017/6/11
>>>>>>> ca930c86c5af48f1d3a0f552598f0ac9c1234fca
//  The main layer 

#ifndef ImageScene_hpp
#define ImageScene_hpp

#include <stdio.h>
#include "cocos2d.h"
<<<<<<< HEAD
#include "extensions/cocos-ext.h"
#include "Hero.h"
#include "ImageScene.hpp"
#include "editor-support/cocostudio/CocoStudio.h"
=======
#include "extensions\cocos-ext.h"
#include "Hero.h"
#include "ImageScene.hpp"
#include "cocostudio/CocoStudio.h"
>>>>>>> ca930c86c5af48f1d3a0f552598f0ac9c1234fca


USING_NS_CC;
USING_NS_CC_EXT;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

using namespace cocos2d::extension;

class Hero;
class HpAndMp;
class ImageScene:public Layer{
public:
    static Scene* createScene();//创建场景
    virtual bool init();
	Hero *m_pHero;//英雄

	void attackButtonClick(int nAttackType); //按键点击触发动作
	//virtual void update(float Delta);

<<<<<<< HEAD
=======
	// 暂停
	void gamePause(Ref* pSender);
>>>>>>> ca930c86c5af48f1d3a0f552598f0ac9c1234fca

    CREATE_FUNC(ImageScene);
private:
	Sprite* HpAndMpBg; //血条能量条背景
	ProgressTimer* HpBar; //血条
	ProgressTimer* MpBar; //能量条
	bool IsRunning;    //是否奔跑
	bool DirectionX;   //x轴方向
	bool DirectionY;   //y轴方向
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;  //存储keycode状态
};





#endif //ImageScene_hpp
