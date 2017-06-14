//Created by loahao
#ifndef HeroControl_H__
#define HeroControl_H__

#include "cocos2d.h"
#include "ImageScene.hpp"

USING_NS_CC;

class OperateLayer;		
					
class CActionButton : public Node, public DirectorDelegate //攻击按钮
{
public:
	CActionButton();
	virtual ~CActionButton();

	virtual bool init(const char *szImage);//初始化
	void click();
	void clickUp();
	virtual bool IsCanClick() { return true; }

	Rect GetRect();
	int GetAttackType() { return m_nAttackType; }

	void SetAttackType(int nAttackType) { m_nAttackType = nAttackType; }
	void SetOperateLayer(OperateLayer *pOperateLayer) { m_pOperateLayer = pOperateLayer; }

	void initTouch();
	void updateProjection(void);

protected:
	virtual void onEnter();
	virtual void onExit();
	bool containsLocation(Touch* touch);
	virtual bool ccTouchBegan(Touch* touch, Event* event);
	virtual void ccTouchMoved(Touch* touch, Event* event);
	virtual void ccTouchEnded(Touch* touch, Event* event);

	virtual void beganAnimation() {}
	virtual void endedAnimation() {}

	Sprite *m_pSprite;
	int m_nAttackType;
	OperateLayer *m_pOperateLayer;

};



// 普通攻击初始化
class CAttackButton : public CActionButton
{
public:
	~CAttackButton();
 	virtual bool init(const char *szImage);
	static CAttackButton* create(const char *szImage);
	virtual bool IsCanClick();

private:
	CAttackButton();
	virtual void beganAnimation();
	virtual void endedAnimation();

	Sprite *m_pNormal;

	float m_fDefaultScale;
	float m_fMaxScale;
	Action *m_pInAction;
	Action *m_pOutAction;

	float m_fClickTime;
};

// 攻击特效
// 特效攻击需要冷却效果，不能在一定时间范围内连续攻击，使用一个旋转的Progresstimer来达到这样的效果
class CAttackEffect : public CActionButton
{
public:
	~CAttackEffect();
	static CAttackEffect* create(const char *szImage);
	virtual bool IsCanClick();
private:
	CAttackEffect();
	virtual void beganAnimation();
	virtual void endedAnimation();
	void endColdTime();

	ProgressTimer *m_pNormal;
	Action *m_pInAction;
	bool m_bCanClick;
};

#endif  // _ACTION_BUTTON_H_