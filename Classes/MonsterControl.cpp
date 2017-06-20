#include "cocos2d.h"
#include "MonsterControl.h"
#include "GlobalData.h"
#include "GlobalDefine.h"
#include "Monster.h"
#include "Hero.h"

MonsterControl::MonsterControl()
{

}
MonsterControl::~MonsterControl()
{

}

MonsterControl* MonsterControl::createWithHeroAndMap(Hero* hero,Sprite *map)
{
	MonsterControl* monsterControl = new MonsterControl();

	if (monsterControl && monsterControl->initMonster(hero,map))
	{
		monsterControl->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(monsterControl);
	}

	return monsterControl;


}

bool MonsterControl::initMonster(Hero* hero, Sprite* map) {
	this->m_pHero = hero;
	this->m_map = map;

	monsterOneList.clear();
	monsterTwoList.clear();
	monsterThreeList.clear();
	monsterShowList.clear();

	int count;//怪物计数
	if (iLevel == 1)
		count = 3;

	if (iLevel == 2)
		count = 6;

	if (iLevel == 3)
		count = 9;
		for (int i = 0; i < count ; i++)
		{
			auto m_pMonster1 = Monster::create();
			m_pMonster1->InitMonsterSprite("Robot3.png", "RobotAttack", "Robothurt", "monsterDie", "RobotRun", "monsterDie5.png", 1);
			m_pMonster1->setVisible(true);
			m_pMonster1->setPosition(500-30*i, 300 - 40 * i);
			monsterOneList.pushBack(m_pMonster1);
		}
		//第二波
		for (int i = 0; i < (count+2); i++)
		{
			
			auto m_pMonster2 = Monster::create();
			m_pMonster2->InitMonsterSprite("Robot3.png", "RobotAttack", "Robothurt", "monsterDie", "RobotRun", "monsterDie5.png", 1);
			m_pMonster2->setVisible(true);
			m_pMonster2->setPosition(600-20*i, 300-40*i);
			monsterTwoList.pushBack(m_pMonster2);

			auto Boss = Monster::create();
			Boss->InitMonsterSprite("Boss.png", "BossAttack", "BossHurt", "BossDie", "Bossrun", "BossDie5.png",10);
			Boss->setVisible(true);
			Boss->setPosition(Vec2(500,200));
			Boss->setAnchorPoint(Point(0,0));
			monsterTwoList.pushBack(Boss);
			
			m_bFlag2 = true;
		}

		monsterShowList = monsterOneList;
		for (auto monster : monsterShowList) {
			m_map->addChild(monster);
			monster->StartListen(m_pHero);
		}
	
	




	return true;

}