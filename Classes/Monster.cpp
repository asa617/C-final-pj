/*
* \file Monster.h
* \date 2016_06_10
*
* \author Xuan_32
*
* \brief ����ʵ����
*/

#include"Monster.h"
#include "ActionTool.h"
#include "Hero.h"
#include "ImageScene.hpp"
#include "GlobalDefine.h"
USING_NS_CC;


Monster::Monster() {
	IsRunning = false;        // �����ܶ�
	MonsterDirection = true;   // �����˶�
	Monster_name = nullptr;
	IsAttack = false;
	my_hero = nullptr;           // ��ǰӢ��     
	dis_x = 10000;
	dis_y = 10000;
	IsHurt = false;
	IsDead = false;
}

Monster::~Monster(){}

Sprite* Monster::GetSprite() {
	return m_MonsterSprite;
}

//��ʼ�����޵ĸ�������
void Monster::InitMonsterSprite(char *name, char*attack, char* die, char *walk, char* dieLast, int m_iLevel) {
	Monster_name = name;
	Monster_attack = attack;
	Monster_walk = walk;
	Monster_die = die;
	Die_name = dieLast;

	m_iHP = 100 * (1 + 0.3*m_iLevel);
	//this->m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	this->m_MonsterSprite = Sprite::create(name);
	this->addChild(m_MonsterSprite);
}

//���ö���
void Monster::SetAnimation(const char *name_each, bool run_directon, float delay, int iLoops)
{
	// ���ù��﷽��
	if (MonsterDirection != run_directon)
	{
		MonsterDirection = run_directon;
		m_MonsterSprite->setFlippedX(run_directon);
	}
	// �������߶������ˣ�����������������
	if (IsRunning || IsAttack || IsHurt || IsDead)
		return;
	// �������� 
	Animate* action = ActionTool::animationWithFrameAndNum(name_each,6, delay);
	m_MonsterSprite->runAction(RepeatForever::create(action));
	//Log("walk~!!!");
	IsRunning = true;
}

// ֹͣ�߶���
void  Monster::StopAnimation()
{
	if (!IsRunning)
		return;

	m_MonsterSprite->stopAllActions();// ��ǰ����ֹͣ���ж���
									  // �ָ�����ԭ���ĳ�ʼ����ͼ 
	this->removeChild(m_MonsterSprite, true);// ��ԭ���ľ���ɾ����
	m_MonsterSprite = Sprite::create(Monster_name);//�ָ�����ԭ������ͼ����
	m_MonsterSprite->setFlipX(MonsterDirection);
	this->addChild(m_MonsterSprite);
	IsRunning = false;
}

// ����
void  Monster::AttackAnimation(const char *name_each, bool run_directon, float delay, int iLoops)
{
	// �����߶������������˻����������ͷ���
	if (IsRunning || IsAttack || IsHurt || IsDead)
		return;
	// ��������
	Animate* action = ActionTool::animationWithFrameAndNum(name_each, 5, delay);
	//�����ص��������������������AttackEnd()
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::AttackEnd));
	//������������

	m_MonsterSprite->runAction(Sequence::create(action, callFunc, NULL));
	IsAttack = true;

}
void Monster::AttackEnd()
{
	// �ָ�����ԭ���ĳ�ʼ����ͼ 
	this->removeChild(m_MonsterSprite, true); // ��ԭ���ľ���ɾ����
	//m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Monster_name)); // �ָ�����ԭ������ͼ����
	m_MonsterSprite->Sprite::create(Monster_name);
	m_MonsterSprite->setFlipX(MonsterDirection);
	this->addChild(m_MonsterSprite);
	IsAttack = false;
}

// ����
void Monster::HurtAnimation(const char *name_each, bool run_directon, float delay, int iLoops)
{
	if (IsHurt || IsDead)
		return;
	//��������
	if (IsRunning || IsAttack)
	{
		m_MonsterSprite->stopAllActions();// ��ǰ����ֹͣ���ж���
										  // �ָ�����ԭ���ĳ�ʼ����ͼ 
		this->removeChild(m_MonsterSprite, true);// ��ԭ���ľ���ɾ����
		//m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Monster_name));//�ָ�����ԭ������ͼ����
		m_MonsterSprite->Sprite::create(Monster_name);
		m_MonsterSprite->setFlipX(MonsterDirection);
		this->addChild(m_MonsterSprite);
		IsRunning = false;
		IsAttack = false;
	}

	Animate* action = ActionTool::animationWithFrameName(name_each, 1, delay);
	// �����ص����������˶�����������HurtEnd()
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::HurtEnd));
	// ������������
	ActionInterval* hurtackact = Sequence::create(action, callFunc, NULL);

	m_MonsterSprite->runAction(hurtackact);
	IsHurt = true;
}
// ���˽���
void Monster::HurtEnd()
{
	IsHurt = false;

	/*��״̬Ч������
	if (my_hero->m_Crazy)
	{
		m_iHP -= 100;
	}
	else*/ 
		m_iHP -= 30;

	if (m_iHP <= 0)
	{
		//���Ź�������
		DeadAnimation(Monster_die, MonsterDirection, 0.1f, 1.0f);
	}
	log("Monster Hurt");
}
// ����
void Monster::DeadAnimation(const char *name_each, bool run_directon, float delay, int iLoops)
{
	IsDead = true;
	// ��������
	Animate* action = ActionTool::animationWithFrameName(name_each, 1, delay);
	// �����ص��������������������deadact()
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Monster::DeadEnd));
	// ������������
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
// ��������
void Monster::DeadEnd()
{
	// �ָ�����������
	this->removeChild(m_MonsterSprite, true);  // ��ԭ���ľ���ɾ����
	//m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Die_name); // �ָ�����������
	m_MonsterSprite = Sprite::create(Die_name);
	m_MonsterSprite->setFlipX(MonsterDirection);
	this->addChild(m_MonsterSprite);

	// ��������������
	Blink* blinkact = Blink::create(2, 3);//3�ǳ���ʱ�䣬6�����Ĵ���

										  // �����ص���������˸���������BlinkEnd()
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Monster::BlinkEnd));
	// ������������
	CCActionInterval* deadact = Sequence::create(blinkact, callFunc, NULL);
	m_MonsterSprite->runAction(deadact);

}
// ��˸����
void Monster::BlinkEnd()
{
	this->removeAllChildren();//�ѹ����Ѫ����ɾ����;
}

void Monster::FollowRun(Hero* m_hero)
{

	// �õ�����x�ľ���
	float x = (my_hero->m_HeroSprite->getPositionX()+my_hero->getPositionX()) - this->getPositionX();
	float y = (my_hero->m_HeroSprite->getPositionY()+my_hero->getPositionY()) - this->getPositionY();

	// �ȼ�������Ӣ�۵ľ���
	dis_x = fabs(x);
	dis_y = fabs(y);

	if (x >= 1280)// ��������Ӣ�۾��볬��1280
		return;
	if (dis_x <= 30)// �ڹ��﹥����Χ�ڣ�����ֹͣ�ƶ�
	{
		this->StopAnimation();// ֹͣ�ܶ�
		scheduleOnce(schedule_selector(Monster::JudegeAttack), 2.5f); //��һ���ĸ����ж����Ƿ��������
		return;
	}

	if (x < -30 && y <= 0)// �жϹ��������Ӣ�۵ľ���
	{
		MonsterDirection = false;
		m_MonsterSprite->setFlippedX(MonsterDirection);// ���÷���
		if (IsAttack)
			return;
		this->SetAnimation(Monster_walk, MonsterDirection, 0.1f, -1);// ���Ŷ���
		this->setPosition(this->getPositionX() - 1.5, this->getPositionY() - 1.5);// ������Ӣ���ƶ�
	}
	else if (x > 30 && y <= 0)
	{

		MonsterDirection = true;
		m_MonsterSprite->setFlippedX(MonsterDirection);// ���÷���
		if (IsAttack)
			return;
		this->SetAnimation(Monster_walk, MonsterDirection, 0.1f, -1);// ���Ŷ���
		this->setPosition(this->getPositionX() + 1.5, this->getPositionY() - 1.5);
	}
	else if (x > 30 && y >= 0)
	{

		MonsterDirection = true;
		m_MonsterSprite->setFlippedX(MonsterDirection);// ���÷���
		if (IsAttack)
			return;
		this->SetAnimation(Monster_walk, MonsterDirection, 0.1f, -1);// ���Ŷ���
		this->setPosition(this->getPositionX() + 1.5, this->getPositionY() + 1.5);
	}
	else if (x < -30 && y >= 0)
	{

		MonsterDirection = false;
		m_MonsterSprite->setFlippedX(MonsterDirection);// ���÷���
		if (IsAttack)
			return;
		this->SetAnimation(Monster_walk, MonsterDirection, 0.1f, -1);// ���Ŷ���
		this->setPosition(this->getPositionX() - 1.5, this->getPositionY() + 1.5);
	}

}

void Monster::JudegeAttack(float dt)
{

	this->AttackAnimation(Monster_attack, MonsterDirection, 0.08f, 0);
}

// ��������
void Monster::StartListen(Hero* m_hero)
{
	my_hero = m_hero;
	this->schedule(schedule_selector(Monster::updateMonster), 1.0f);// ÿ��1��������
	this->scheduleUpdate();// Ӣ��һ��������ӷ�Χ������׷��Ӣ�۴�
}

// ��������,ÿ��1������
void Monster::updateMonster(float delta)
{
	// ���������ͷ���
	if (IsDead || my_hero->IsDead)
		return;
	// �õ�����x�ľ���
	float x = (my_hero->m_HeroSprite->getPositionX()+my_hero->getPositionX()) - this->getPositionX();
	float y = (my_hero->m_HeroSprite->getPositionY()+my_hero->getPositionY()) - this->getPositionY();
	// �ȼ�������Ӣ�۵ľ���
	dis_x = fabs(x);
	dis_y = fabs(y);

}
void Monster::update(float delta)
{
	// ���������ͷ���
	if (IsDead || my_hero->IsDead)
		return;
	if (dis_x < 2000 && my_hero->IsDead == false)// ��Ӣ�������Ŀ��ӷ�Χ�ڣ�����׷��Ӣ��
		FollowRun(my_hero);
};