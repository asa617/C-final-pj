// Created by loahao on 2017/6/10
// Added by Xuan on 2017/6/18

#include"Hero.h"
#include"ActionTool.h"
#include "OperateLayer.h"
#include"AttackMonitor.h"

USING_NS_CC;

void Hero::InitHeroSprite(char *hero_name, int ilevel)
{
	m_HeroSprite = NULL;
	m_Crazy = false;
	Hero_Name = NULL;
	IsRunning = false;
	IsAttack = false;
	IsHurt = false;
	IsDead = false;
	HeroPath = false;
	m_CurrentMp = 0.0f;
	m_TotalMp = 100.0f;
	m_CurrentHp = m_TotalHp = 100.0f * ilevel;
	percentage = 100.0f;
	m_Speed = 5;
	Hero_Name = hero_name;

	//this->m_HeroSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hero_name));
	this->m_HeroSprite = Sprite::create(hero_name);
	this->addChild(m_HeroSprite);
	


	initKey();
	InitAction();
	scheduleUpdate();
}

void Hero::InitAction()
{
	//普通攻击
	Animate* AttackNormal = ActionTool::animationWithFrameAndNum("HeroAttack", 5, 0.15);
	m_AttackNormal = AttackNormal;
	m_AttackNormal->retain();
	//跳击
	Animate* AttackJump = ActionTool::animationWithFrameAndNum("HeroAttackJ", 8, 0.1);
	m_AttackJump = AttackJump;
	m_AttackJump->retain();
	//暴击
	Animate* AttackTerror = ActionTool::animationWithFrameAndNum("HeroAttackT", 3, 0.1);
	m_AttackTerror = AttackTerror;
	m_AttackTerror->retain();

}

void Hero::Attack(int AttackType)
{
	FiniteTimeAction *pAction = NULL;
	switch (AttackType)
	{
	case abtAttack:
	{
		pAction = m_AttackNormal;
		m_AttackRange = 150;
		AttackMonitor::HeroAttackMonitor(this, abtAttack, m_AttackRange);
	}
	break;
	case abtAttackA:
	{
		pAction = m_AttackJump;
		// 当前位置跳跃
		Action *jump = JumpTo::create(0.6, ccpSub(m_HeroSprite->getPosition(), ccp(m_HeroSprite->isFlippedX() ? 200 : -200, 0)), 120, 1);
		m_HeroSprite->runAction(jump);
		m_AttackRange = 300;
		AttackMonitor::HeroAttackMonitor(this, abtAttackA, m_AttackRange);

	}
	break;
	case abtAttackB:
	{
		pAction = m_AttackTerror;
		// 当前位置移动
		Action *move = MoveTo::create(0.3, ccpSub(m_HeroSprite->getPosition(), ccp(m_HeroSprite->isFlippedX() ? 200 : -200, 0)));
		m_HeroSprite->runAction(move);
		m_AttackRange = 300;
		AttackMonitor::HeroAttackMonitor(this, abtAttackB, m_AttackRange);
	}
	break;
	}

	if (pAction)
	{
		m_HeroSprite->stopAllActions();
		Action *pActions = Sequence::create(pAction, CallFunc::create(this, callfunc_selector(Hero::AttackEnd)), NULL);
		m_HeroSprite->runAction(pActions);
		IsAttack=true;
		PostAttack();
	}
}

void Hero::SetAttackRange()
{
	Point point = getPosition();
	float fAttackWidth = 100;
	Point newPoint = (m_HeroSprite->isFlippedX()) ? ccpSub(point, ccp(100, 0)) : point;
}

void Hero::PostAttack()
{
	SetAttackRange();
	//NotificationCenter::sharedNotificationCenter()->postNotification("attack", this);
}

Sprite * Hero::GetSprite()
{
	return m_HeroSprite;
}

void Hero::CheckLocation()
{
	Size WinSize = Director::getInstance()->getVisibleSize();
		Point CurPoint = m_HeroSprite->getPosition();
		Point NewPoint = m_HeroSprite->getPosition();
		if (CurPoint.x < 0)
			NewPoint.x = 0;
		if (CurPoint.y < -160)
			NewPoint.y = -160;
		if (CurPoint.x > WinSize.width /2 +250)
			NewPoint.x = WinSize.width /2 +250;
		if (CurPoint.y > WinSize.height /2 -230)
			NewPoint.y = WinSize.height /2 -230;
		m_HeroSprite->setPosition(NewPoint);
		//log("x=%d,y=%d", NewPoint.x,NewPoint.y);
	
}

void Hero::AttackEnd()//攻击结束
{
	m_HeroSprite->stopAllActions();
	IsStand = true;
	IsAttack = false;

}
// 受伤  
void Hero::HurtByMonsterAnimation(const char *name_each, float delay, bool run_directon)
{
	if (IsHurt || IsDead)
		return;
	//受伤优先  
	if (IsRunning || IsAttack)
	{
		m_HeroSprite->stopAllActions();//当前精灵停止所有动画  
									   //恢复精灵原来的初始化贴图   
		this->removeChild(m_HeroSprite, true);//把原来的精灵删除掉  
		m_HeroSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Hero_Name));//恢复精灵原来的贴图样子  
		m_HeroSprite ->setFlippedX(HeroPath);
		this->addChild(m_HeroSprite);
		IsRunning = false;
		IsAttack = false;
	}

	Animate* action = ActionTool::animationWithFrameAndNum(name_each, 3, delay);
	//创建回调动作，受伤动画结束调用HurtEnd()  
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Hero::HurtByMonsterEnd));
	//创建连续动作  
	ActionInterval* hurtackact = Sequence::create(action, callFunc, NULL);

	m_HeroSprite->runAction(hurtackact);
	IsHurt = true;
}

// 受伤结束  
void Hero::HurtByMonsterEnd()
{
	m_CurrentHp -= 20.0f;
	IsHurt = false;
	percentage = m_CurrentHp / m_TotalHp * 100.0f;
	if (m_CurrentHp<0.0f)
	{
		DeadAnimation("dead", 0, HeroPath);
	}
}

// 死亡  
void Hero::DeadAnimation(const char *name_each, float delay, bool run_directon)
{
	m_HeroSprite->stopAllActions();
	// 调整方向  
	if(HeroPath != run_directon)
	{
		HeroPath = run_directon;
		m_HeroSprite->setFlippedX(run_directon);
	}
	// 创建动作  
	Animate* Act = ActionTool::animationWithFrameAndNum(name_each, 5, 0.3f);
	//创建回调动作，死亡结束后调用DeadEnd()  
	CallFunc* callAttackEnd = CallFunc::create(this, callfunc_selector(Hero::DeadEnd));
	//创建连续动作  
	ActionInterval* AttackAct = Sequence::create(Act, callAttackEnd, NULL);
	m_HeroSprite->runAction(AttackAct);
	Director::getInstance()->getScheduler()->setTimeScale(0.5);
}

// 死亡结束  
void Hero::DeadEnd()
{
	IsDead = true;
	//恢复死亡的样子  
	//记录死亡的位置
	float x = m_HeroSprite->getPositionX();
	float y = m_HeroSprite->getPositionY();
	this->removeChild(m_HeroSprite, true);//把原来的精灵删除掉
	m_HeroSprite = Sprite::create("dead5.png");//恢复死亡的样子
	m_HeroSprite->setFlippedX(!HeroPath);
	m_HeroSprite->setPosition(Vec2(x, y));
	this->addChild(m_HeroSprite);

}

// 判断位置  
bool Hero::JudgePosition()
{
	if((this->getPositionX() < 50) || this->getPositionX() > 600||(this->getPositionY()<50)||(this->getPositionY()>500))// 精灵到达mid
		return false;
	else
	{
		return true;//在框内
	}
}

void Hero::initKey()
{
	auto KeyListener = EventListenerKeyboard::create();
	KeyListener->onKeyPressed = [=](EventKeyboard::KeyCode key, Event* event)
	{
		log("keyint");
		keys[key] = true;
	};

	KeyListener->onKeyReleased = [=](EventKeyboard::KeyCode key, Event* event)
	{
		keys[key] = false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(KeyListener, this);

}



/*bool Hero::isKeyPressed(EventKeyboard::KeyCode key)
{		

}*/

void Hero::KeyPressDo(EventKeyboard::KeyCode key)
{
	log("Keyboard");
	int ChangeX = 0, ChangeY = 0;
	bool RunningAction=false;
	ActionInterval *moveTo;
	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		ChangeX = -10;
		HeroPath = false;
		RunningAction = true;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		ChangeX = 10;
		HeroPath = true;
		RunningAction = true;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		ChangeY = 5;
		RunningAction = true;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		ChangeY = -5;

		RunningAction = true;
		break;

	default:
		break;
	}
	if (!HeroPath)
	{
		m_HeroSprite->setFlippedX(true);
	}
	else
	{
		m_HeroSprite->setFlippedX(false);
	}
	if (JudgePosition())
	{
		moveTo = MoveTo::create(0.5, Vec2(m_HeroSprite->getPositionX() + ChangeX, m_HeroSprite->getPositionY() + ChangeY));
		Animate* Run = ActionTool::animationWithFrameAndNum("HeroRun", 11, 0.1);
		Action *action = Spawn::create(moveTo, Run, NULL);
		m_HeroSprite->runAction(action);
	}
	else if(RunningAction)
	{
		Animate* Run = ActionTool::animationWithFrameAndNum("HeroRun", 11, 0.1);
		RepeatForever *aRun = RepeatForever::create(Run);
		m_HeroSprite->runAction(aRun);
	}
	CheckLocation();
}


void Hero::update(float delta)
{
	
	Node::update(delta);

//	log("update");
	auto LeftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
	auto RightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	auto UpArrow = EventKeyboard::KeyCode::KEY_UP_ARROW;
	auto DownArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	auto Attack = EventKeyboard::KeyCode::KEY_A;
	auto AttackA = EventKeyboard::KeyCode::KEY_S;
	auto AttackB = EventKeyboard::KeyCode::KEY_D;
	auto _Exit = EventKeyboard::KeyCode::KEY_ESCAPE;
	auto _Pause = EventKeyboard::KeyCode::KEY_SPACE;

	if (keys[LeftArrow])
	{
		KeyPressDo(LeftArrow);
		log("LeftIsPressed");
	}
	else if (keys[RightArrow])
	{
		KeyPressDo(RightArrow);
		log("RightIsPressed");
	}
	else if (keys[UpArrow])
	{
		KeyPressDo(UpArrow);
		log("UpIsPressed");
	}
	else if (keys[DownArrow])
	{
		KeyPressDo(DownArrow);
		log("DownIsPressed");
	}

	
}

