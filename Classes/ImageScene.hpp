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
#include "Monster.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace CocosDenshion;
using namespace cocos2d::extension;

class Hero;
class HpAndMp;
class ImageScene:public Layer
{
public:
    static Scene* createScene();//��������
    virtual bool init();
	Hero *m_pHero;//Ӣ��

	void attackButtonClick(int nAttackType); //���������������
	//virtual void update(float Delta);
	void actionJoypadStart(float degrees);
	void actionJoypadUpdate(float degrees);
	void actionJoypadEnded(float degrees);
	// ��ͣ
	void gamePauseCallback(Ref* pSender);

	void update(float Delta);

    CREATE_FUNC(ImageScene);
private:
	Sprite* HpAndMpBg; //Ѫ������������
	ProgressTimer* HpBar; //Ѫ��
	ProgressTimer* MpBar; //������
	bool IsRunning;    //�Ƿ���
	bool DirectionX;   //x�᷽��
	bool DirectionY;   //y�᷽��
	bool monsterFlag;//�ж��Ƿ��Ѿ������¹���
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;  //�洢keycode״̬

	Sprite* BgMap;

	bool areMonstersAllDie(Vector<Monster*> Monsterlist);
	void updateMonster(float delta);
};





#endif //ImageScene_hpp
