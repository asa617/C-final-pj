//
//  ImageScene.hpp
//  mygame
//
//  Created by -T.c on 2017/5/26.
//  Added by loahao on 2017/6/9
//  Added by Xuan_32 on 2017/6/11
//  The main layer 

#ifndef ImageScene_hpp
#define ImageScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Hero.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace CocosDenshion;
using namespace cocos2d::extension;

class Hero;
class HpAndMp;
class ImageScene:public Layer
{
public:
    static Scene* createScene();//创建场景
    virtual bool init();
	Hero *m_pHero;//英雄

	void attackButtonClick(int nAttackType); //按键点击触发动作
	//virtual void update(float Delta);

	// 暂停
	void gamePauseCallback(Ref* pSender);

	void update(float Delta);

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
