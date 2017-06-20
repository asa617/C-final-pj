// Created by loahao on 2017/6/10

#ifndef Hero_H__
#define Hero_H__

#include"cocos2d.h"
USING_NS_CC;

class Hero :public Node
{
public:
	// 根据图片名创建英雄  
	void InitHeroSprite(char *hero_name,int iLevel);
	// 返回当前英雄  
	Sprite* GetSprite();
	Sprite* m_HeroSprite; //英雄
	// 设置动画，run_directon为精灵脸朝向，false朝右,frameName为图片帧名字  
	void SetAnimation(const char *frameName,float delay, bool run_directon);
	// 停止动画  
	void StopAnimation();
	// 攻击动画  
	void AttackAnimation(const char *name_each, float delay,bool run_directon);
	// 攻击动画结束  
	void PostAttack();
	void AttackEnd();
	// 死亡动画  
	void DeadAnimation(const char *name_each, float delay, bool run_directon);
	// 死亡动画结束  
	void DeadEnd();
	// 受伤动画  
	void HurtByMonsterAnimation(const char *name_each, float delay, bool run_directon);
	// 受伤动画结束  
	void HurtByMonsterEnd();
	// 判断英雄是否运动到了窗口的中间位置,visibleSize为当前窗口的大小    
	void SetAttackRange();

	// HP & MP 值  
	float m_CurrentHp;//当前血量
	float m_TotalHp;//总血量
	float m_CurrentMp;//当前能量
	float m_TotalMp;//总能量
	float percentage;//血量比

	float m_Speed; //移动速度
	bool m_IsAction;// 查看当前是否有动作
	bool IsStand;
	bool IsRunning; //判断是否在跑动画  
	bool IsAttack;// 判断是否在攻击动画 
	bool IsDead; //判断是否死亡
	bool IsHurt;  //判断是否受伤  
	bool HeroPath;  //英雄方向
	bool m_Crazy; //判断是否处于狂暴状态
	float m_AttackRange;//攻击范围

	void Attack(int AttackType);

	bool JudgePosition();
	void CheckLocation();
	//方向移动
	void initKey();
	void KeyPressDo(EventKeyboard::KeyCode key);

	void MoveAndRun(float Direction);

	virtual void update(float Delta);
	CREATE_FUNC(Hero);


private:
	FiniteTimeAction *m_pActionRunning;
	FiniteTimeAction *m_AttackNormal;
	FiniteTimeAction *m_AttackJump;
	FiniteTimeAction *m_AttackTerror;
	void InitAction();

	char* Hero_Name; //用来保存初始状态的精灵图片名称
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;//保存键盘状态
};


#endif