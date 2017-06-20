/*
* \file Monster.h
* \date 2016_06_10
*
* \author Xuan_32
*
* \brief 怪物实体类
*/

#include"Monster.h"
#include "ActionTool.h"
#include "Hero.h"
#include "ImageScene.hpp"
#include "GlobalDefine.h"
#include "GlobalData.h"
USING_NS_CC;


Monster::Monster() {
	IsRunning = false;        // 不在跑动
	MonsterDirection = true;   // 向右运动
	Monster_name = nullptr;
	IsAttack = false;
	my_hero = nullptr;           // 当前英雄     
	dis_x = 10000;
	dis_y = 10000;
	IsHurt = false;
	IsDead = false;
}

Monster::~Monster(){}

Sprite* Monster::GetSprite() {
	return m_MonsterSprite;
}

const char* Monster::getMonsterName() {
	return Monster_name;
}

//初始化怪兽的各种属性
void Monster::InitMonsterSprite(char *name, char*attack, char* hurt,char* die, char *walk, char* dieLast, int m_iLevel) {
	Monster_name = name;
	Monster_attack = attack;
	Monster_walk = walk;
	Monster_hurt = hurt;
	Monster_die = die;
	Die_name = dieLast;

	m_iHP = 100 * (1 + 0.3*m_iLevel);
	//this->m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	this->m_MonsterSprite = Sprite::create(name);
	this->addChild(m_MonsterSprite);
}

//设置动作
void Monster::SetAnimation(const char *name_each, bool run_directon, float delay, int iLoops)
{
	// 设置怪物方向
	if (MonsterDirection != run_directon)
	{
		MonsterDirection = run_directon;
		m_MonsterSprite->setFlippedX(run_directon);
	}
	// 怪物在走动或，受伤，攻击，死亡，返回
	if (IsRunning || IsAttack || IsHurt || IsDead)
		return;
	// 创建动作 
	Animate* action = ActionTool::animationWithFrameAndNum(name_each,6, delay);
	m_MonsterSprite->runAction(RepeatForever::create(action));
	//Log("walk~!!!");
	IsRunning = true;
}

// 停止走动后
void  Monster::StopAnimation()
{
	if (!IsRunning)
		return;

	m_MonsterSprite->stopAllActions();// 当前精灵停止所有动画
									  // 恢复精灵原来的初始化贴图 
	this->removeChild(m_MonsterSprite, true);// 把原来的精灵删除掉
	m_MonsterSprite = Sprite::create(Monster_name);//恢复精灵原来的贴图样子
	m_MonsterSprite->setFlipX(MonsterDirection);
	this->addChild(m_MonsterSprite);
	IsRunning = false;
}

// 攻击
void  Monster::AttackAnimation(const char *name_each, bool run_directon, float delay, int iLoops)
{
	// 正在走动、攻击、受伤或已死亡，就返回
	if (IsRunning || IsAttack || IsHurt || IsDead)
		return;
	// 创建动作
	Animate* action = ActionTool::animationWithFrameAndNum(name_each, 5, delay);
	//创建回调动作，攻击结束后调用AttackEnd()
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::AttackEnd));
	//创建连续动作

	m_MonsterSprite->runAction(Sequence::create(action, callFunc, NULL));
	IsAttack = true;

}
void Monster::AttackEnd()
{
	// 恢复精灵原来的初始化贴图 
	this->removeChild(m_MonsterSprite, true); // 把原来的精灵删除掉
	//m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Monster_name)); // 恢复精灵原来的贴图样子
	m_MonsterSprite->Sprite::create(Monster_name);
	m_MonsterSprite->setFlipX(MonsterDirection);
	this->addChild(m_MonsterSprite);
	IsAttack = false;
}

// 受伤
void Monster::HurtAnimation(const char *name_each, bool run_directon, float delay, int iLoops, int hurt_Type )
{
	if (IsHurt || IsDead)
		return;
	//受伤优先
	if (IsRunning || IsAttack)
	{
		m_MonsterSprite->stopAllActions();// 当前精灵停止所有动画
										  // 恢复精灵原来的初始化贴图 
		this->removeChild(m_MonsterSprite, true);// 把原来的精灵删除掉
		//m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Monster_name));//恢复精灵原来的贴图样子
		m_MonsterSprite = Sprite::create(Monster_name);
		m_MonsterSprite->setFlipX(MonsterDirection);
		IsRunning = false;
		IsAttack = false;
		this->addChild(m_MonsterSprite);
	}
	
	
	hurtType = hurt_Type;


	Animate* action = ActionTool::animationWithFrameAndNum(Monster_hurt, 3, 0.3f);
	// 创建回调动作，受伤动画结束调用HurtEnd()
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::HurtEnd));
	// 创建连续动作
	ActionInterval* hurtackact = Sequence::create(action, callFunc, NULL);

	m_MonsterSprite->runAction(hurtackact);
	IsHurt = true;
}
// 受伤结束
void Monster::HurtEnd()
{
	IsHurt = false;

	if (my_hero->m_Crazy)
	{
		m_iHP -= 100;
	}
	else
		m_iHP -= 30*(1 + 0.2*iLevel + 0.1*(hurtType-1));

	if (m_iHP <= 0)
	{
		//播放怪物死亡
		DeadAnimation(Monster_die, MonsterDirection, 0.5f, 1.0f);
	}
	log("Monster Hurt");
}
// 死亡
void Monster::DeadAnimation(const char *name_each, bool run_directon, float delay, int iLoops)
{
	IsDead = true;
	// 创建动作
	Animate* action = ActionTool::animationWithFrameAndNum(name_each, 5, delay);
	// 创建回调动作，死亡结束后调用deadact()
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Monster::DeadEnd));
	// 创建连续动作
	CCActionInterval* deadact = Sequence::create(action, callFunc, NULL);
	m_MonsterSprite->runAction(deadact);
	if (my_hero->m_CurrentMp < 100)
	{
		my_hero->m_CurrentMp = (my_hero->m_CurrentMp + 20);
		if (my_hero->m_CurrentMp > 100)
		{
			my_hero->m_CurrentMp = 100;
		}
	}
}
// 死亡结束
void Monster::DeadEnd()
{
	// 恢复死亡的样子
	this->removeChild(m_MonsterSprite, true);  // 把原来的精灵删除掉
	//m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Die_name); // 恢复死亡的样子
	m_MonsterSprite = Sprite::create(Die_name);
	m_MonsterSprite->setFlipX(MonsterDirection);
	m_MonsterSprite->setPosition(Vec2(m_MonsterSprite->getPositionX(), m_MonsterSprite->getPositionY() - 50));
	this->addChild(m_MonsterSprite);

	// 怪物闪下再死亡
	Blink* blinkact = Blink::create(2, 3);//3是持续时间，6是闪的次数

										  // 创建回调动作，闪烁结束后调用BlinkEnd()
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Monster::BlinkEnd));
	// 创建连续动作
	CCActionInterval* deadact = Sequence::create(blinkact, callFunc, NULL);
	m_MonsterSprite->runAction(deadact);

}
// 闪烁结束
void Monster::BlinkEnd()
{
	this->removeAllChildren();//把怪物和血条都删除掉;
}

void Monster::FollowRun(Hero* m_hero)
{

	// 得到两点x的距离
	float x = (my_hero->m_HeroSprite->getPositionX() + my_hero->getPositionX()) - this->getPositionX();//图片节点差异;
	float y = (my_hero->m_HeroSprite->getPositionY()+my_hero->getPositionY()) - this->getPositionY();

	// 先计算怪物和英雄的距离
	dis_x = fabs(x);
	dis_y = fabs(y);

	if (x >= 450)// 当怪物与英雄距离超过450
		return;
	if (dis_x <= 30 && dis_y <=5)// 在怪物攻击范围内，怪物停止移动
	{
		this->StopAnimation();// 停止跑动
		//攻击时判断是否面对英雄
		if(MonsterDirection == my_hero->HeroPath)
		{
			MonsterDirection = !MonsterDirection;
			m_MonsterSprite->setFlippedX(MonsterDirection);//设置方向

		}
		scheduleOnce(schedule_selector(Monster::JudegeAttack), 2.5f); 
		return;
	}

	if (x < -5 )// 判断怪物坐标和英雄的距离
	{
		MonsterDirection = false;
		m_MonsterSprite->setFlippedX(MonsterDirection);// 设置方向
		if (IsAttack)
			return;
		this->SetAnimation(Monster_walk, MonsterDirection, 0.1f, -1);// 播放动画
		this->setPosition(this->getPositionX() -1, this->getPositionY());// 怪物向英雄移动
	}
	if (y > 5)
	{
		if (IsAttack)
			return;
		this->SetAnimation(Monster_walk, MonsterDirection, 0.1f, -1);// 播放动画
		this->setPosition(this->getPositionX(), this->getPositionY() +1);// 怪物向英雄移动
	}
	if (x > 5)
	{

		MonsterDirection = true;
		m_MonsterSprite->setFlippedX(MonsterDirection);// 设置方向
		if (IsAttack)
			return;
		this->SetAnimation(Monster_walk, MonsterDirection, 0.1f, -1);// 播放动画
		this->setPosition(this->getPositionX() + 1, this->getPositionY());
	}
	if (y < -5)
	{
		if (IsAttack)
			return;
		this->SetAnimation(Monster_walk, MonsterDirection, 0.1f, -1);// 播放动画
		this->setPosition(this->getPositionX(), this->getPositionY() -1);
	}

}

void Monster::JudegeAttack(float dt)
{

	this->AttackAnimation(Monster_attack, MonsterDirection, 0.08f, 0);
}

// 启动监听
void Monster::StartListen(Hero* m_hero)
{
	my_hero = m_hero;
	this->schedule(schedule_selector(Monster::updateMonster), 1.0f);// 每隔1秒计算距离
	this->scheduleUpdate();// 英雄一旦进入可视范围，怪物追着英雄打
}

// 监听函数,每隔1秒检测下
void Monster::updateMonster(float delta)
{
	// 已死亡，就返回
	if (IsDead || my_hero->IsDead)
		return;
	// 得到两点x的距离
	float x = (my_hero->m_HeroSprite->getPositionX()+my_hero->getPositionX()) - this->getPositionX();
	float y = (my_hero->m_HeroSprite->getPositionY()+my_hero->getPositionY()) - this->getPositionY();
	// 先计算怪物和英雄的距离
	dis_x = fabs(x);
	dis_y = fabs(y);

}
void Monster::update(float delta)
{
	// 已死亡，就返回
	if (IsDead || my_hero->IsDead)
		return;
	if (dis_x < 2000 && my_hero->IsDead == false)// 当英雄在它的可视范围内，不断追着英雄
		FollowRun(my_hero);
};
