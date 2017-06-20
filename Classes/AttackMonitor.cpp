#include "AttackMonitor.h"

bool AttackMonitor::MonsterAttackMonitor(Hero* m_hero) {
	for (auto monster : monsterShowList) 
	{
		if (!monster->IsDead) 
		{
			if (monster->IsAttack && m_hero->IsDead == false && m_hero->IsHurt == false)
			{
				if (IsMonsterAttackTrue(m_hero, monster))
				{
					//如果受伤成真，则进行受伤动画并返回真到主场景，使对应血条扣血
					m_hero->HurtByMonsterAnimation("hurt", 0.2f, !(monster->MonsterDirection));
					return true;
				}
			}
		}	
	}
	return false;
}

bool AttackMonitor::IsMonsterAttackTrue(Hero* m_hero, Monster* monster)
{
	//得到两点x的距离
	float x = (m_hero->getPositionX() + m_hero->m_HeroSprite->getPositionX()) - (monster->getPositionX());
	float y = (m_hero->getPositionY() + m_hero->m_HeroSprite->getPositionY()) - (monster->getPositionY());
	if (y >= -60 && y <= 60)
	{
		if (monster->MonsterDirection && x >= -45 && x < 0)
		{
			return true;
		}
		if ((!monster->MonsterDirection) && x <= 45 && x > 0)
		{
			return true;
		}
		return false;
	}
	else
		return false;
}

void AttackMonitor::HeroAttackMonitor(Hero* m_hero, int attackType,int attackRange)
{
	for (auto monster : monsterShowList)
	{
		if (monster->IsDead == false && monster->IsHurt == false)
		{

			if (IsHeroAttackTrue(m_hero, monster, attackRange))
			{
			
				monster->stopAllActions();
				monster->HurtAnimation(monster->getMonsterName(), !m_hero->HeroPath, 0.2f, 1,attackType);
			}
		}
	}
}

bool AttackMonitor::IsHeroAttackTrue(Hero* m_hero, Monster* monster, int attackRange)
{
	float x = (m_hero->getPositionX() + m_hero->m_HeroSprite->getPositionX()) - (monster->getPositionX());
	float y = (m_hero->getPositionY() + m_hero->m_HeroSprite->getPositionY()) - (monster->getPositionY());

	if (m_hero->HeroPath == true && x <= 0)
	{
		if (fabs(x) <= attackRange && fabs(y)<=50)
		{
			return 1;
		}
		else
			return 0;
	}
	if (m_hero->HeroPath == false && x >= 0)
	{
		if (fabs(x) <= attackRange && fabs(y) <= 50)
		{
			return 1;
		}
		else
			return 0;
	}
	return 0;
}
