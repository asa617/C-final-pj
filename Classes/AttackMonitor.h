// Created by Xuan_32 on 6_15
// biref�����ڼ��Ӣ�������֮��ļ��

#include"Hero.h"
#include"Monster.h"
#include"GlobalData.h"

class Hero;
class Monster;

class AttackMonitor 
{
public:
	//�����ж�Ӣ�۵Ĺ����Ƿ����
	static void HeroAttackMonitor(Hero* m_hero, int attackType, int attackRange);
	//�����жϹ���Ĺ����Ƿ����
	static bool MonsterAttackMonitor(Hero* m_hero);
	//�����жϹ��﹥�������Ƿ�����ȷ����˺�
	static bool IsMonsterAttackTrue(Hero* m_hero, Monster* m_monster);
	//�����ж�Ӣ�۹��������Ƿ�����ȷ����˺�
	static bool IsHeroAttackTrue(Hero* m_hero, Monster* m_monster, int attackRange);

};