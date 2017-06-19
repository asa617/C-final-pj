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

	auto m_pMonster1 = Monster::create();
	m_pMonster1->InitMonsterSprite("Robot3.png", "RobotAttack","Robothurt", "monsterDie", "RobotRun", "monsterDie5.png", 1);
	m_pMonster1->setVisible(true);
	m_pMonster1->setPosition(500, 300);
	m_map->addChild(m_pMonster1);
	m_pMonster1->StartListen(m_pHero);
	monsterShowList.pushBack(m_pMonster1);
	m_bFlag1 = false;
	//第二波
	auto m_pMonster2 = Monster::create();
	m_pMonster2->InitMonsterSprite("Robot3.png", "RobotAttack","Robothurt", "monsterDie", "RobotRun", "monsterDie5.png", 1);
	m_pMonster2->setVisible(true);
	m_pMonster2->setPosition(600, 365);
	m_pMonster2->StartListen(m_pHero);
	monsterTwoList.pushBack(m_pMonster2);

	auto m_pMonster3 = Monster::create();
	m_pMonster3->InitMonsterSprite("Robot3.png", "RobotAttack", "Robothurt","monsterDie", "RobotRun", "monsterDie5.png", 1);
	m_pMonster3->setVisible(true);
	m_pMonster3->setPosition(400, 200);
	m_pMonster3->StartListen(m_pHero);
	monsterThreeList.pushBack(m_pMonster3);
	// 第三波
	for (int i = 0; i < 3; i++)
	{
		auto m_pMonster = Monster::create();
		m_pMonster->InitMonsterSprite("Robot3.png", "RobotAttack", "Robothurt","monsterDie", "RobotRun", "monsterDie5.png", 1);
		if (i == 0 || i == 1)
		{
			m_pMonster->setPosition(-100 * i, 250);
		}
		else
		{
			m_pMonster->setPosition(900, 365);
		}
		m_pMonster->setVisible(false);
		monsterThreeList.pushBack(m_pMonster);
	}

	this->schedule(schedule_selector(MonsterControl::updateMonster));

	return true;

}

void MonsterControl::updateMonster(float delta)
{
	// 第二波
	if (m_bFlag1 == false && m_bFlag2 == true)
	{
		bool noMonster = true;
		for (auto monster : monsterShowList)
		{
			if (!monster->IsDead)
			{
				noMonster = false;
			}
		}
		if (noMonster)
		{
			this->scheduleOnce(schedule_selector(MonsterControl::showSecMon), 4.0f);
		}
	}

	// 第三波
	if (m_bFlag2 == false && m_bFlag3 == true)
	{
		bool noMonster = true;
		for (auto monster : monsterShowList)
		{
			if (!monster->IsDead)
			{
				noMonster = false;
			}
		}
		if (noMonster)
		{
			this->scheduleOnce(schedule_selector(MonsterControl::showThrMon), 3.0f);
		}
	}
}

void MonsterControl::showSecMon(float delta)
{
	for (auto monster : monsterTwoList)
	{
		monster->setVisible(true);
		m_map->addChild(monster);
		monster->StartListen(m_pHero);
		monsterShowList.pushBack(monster);
		m_bFlag2 = false;
	}
}

void MonsterControl::showThrMon(float delta)
{
	for (auto monster : monsterThreeList)
	{
		monster->setVisible(true);
		m_map->addChild(monster);
		monster->StartListen(m_pHero);
		monsterShowList.pushBack(monster);
		m_bFlag3 = false;
	}
}