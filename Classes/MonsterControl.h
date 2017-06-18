//
// \file MonsterControl
// 
// Created by Xuan_32 6_12
//
//
// brief:生成和管理怪物


#ifndef _MonsterControl_H_
#define _MonsterControl_H_

#include"cocos2d.h"
#include "Monster.h"
#include "Hero.h"


USING_NS_CC;

class Monster;
class Hero;


class MonsterControl : public Node {
public:
	MonsterControl();
	~MonsterControl();
	void updateMonster(float delta);
	void showSecMon(float delta);
	void showThrMon(float delta);
	static MonsterControl* createWithHeroAndMap(Hero* hero, Sprite* map);
	bool initMonster(Hero* hero, Sprite* map);
private:
	Sprite* m_map;
	Hero* m_pHero;
	bool IsMonsterClear;

};

#endif // !1

