// Created by Xuan_32 on 6_15
// biref：用于监测英雄与怪物之间的监测

#include"Hero.h"
#include"Monster.h"
#include"GlobalData.h"

class Hero;
class Monster;

class AttackMonitor 
{
public:
	//用于判断英雄的攻击是否成立
	static void HeroAttackMonitor(Hero* m_hero, int attackType, int attackRange);
	//用于判断怪物的攻击是否成立
	static bool MonsterAttackMonitor(Hero* m_hero);
	//用于判断怪物攻击方向是否能正确造成伤害
	static bool IsMonsterAttackTrue(Hero* m_hero, Monster* m_monster);
	//用于判断英雄攻击方向是否能正确造成伤害
	static bool IsHeroAttackTrue(Hero* m_hero, Monster* m_monster, int attackRange);

};