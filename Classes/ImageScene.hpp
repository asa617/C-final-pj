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
    static Scene* createScene();//��������
    virtual bool init();
	Hero *m_pHero;//Ӣ��

	void attackButtonClick(int nAttackType); //���������������
	//virtual void update(float Delta);

<<<<<<< HEAD
=======
	// ��ͣ
	void gamePause(Ref* pSender);
>>>>>>> ca930c86c5af48f1d3a0f552598f0ac9c1234fca

    CREATE_FUNC(ImageScene);
private:
	Sprite* HpAndMpBg; //Ѫ������������
	ProgressTimer* HpBar; //Ѫ��
	ProgressTimer* MpBar; //������
	bool IsRunning;    //�Ƿ���
	bool DirectionX;   //x�᷽��
	bool DirectionY;   //y�᷽��
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;  //�洢keycode״̬
};





#endif //ImageScene_hpp
