//
// \file MonsterControl
// 
// Created by Xuan_32 6_12
//
//
// brief:���ɺ͹������


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
	bool areMonstersAllDie(Vector<Monster*> Monsterlist);
	static MonsterControl* createWithHeroAndMap(Hero* hero, Sprite* map);
	bool initMonster(Hero* hero, Sprite* map);
private:
	Sprite* m_map;
	Hero* m_pHero;
	bool IsMonsterClear;
	bool clearFlag;


};

#endif // !1

