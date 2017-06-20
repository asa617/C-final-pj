//Created by loahao
//Ö÷Òª²Ù×÷
#ifndef OperateLayer_H__
#define OperateLayer_H__

#include "cocos2d.h"
#include "ImageScene.hpp"
#include "HeroControl.h"

USING_NS_CC;

class ImageScene;
class CAttackButton;
class CAttackEffect;

enum AttackButtonType
{
	abtNone,
	abtAttack,
	abtAttackA,
	abtAttackB,
	abtAttackMax,
 };

class OperateLayer : public Layer
{
public:
	~OperateLayer();

	virtual bool init();
	CREATE_FUNC(OperateLayer);

	void attackButtonClick(int nAttackType);
	void keyAttack(int nButtonType);
	void keyAttackUp(int nButtonType);

	void setDelegate(ImageScene *pImageScene);

private:
	OperateLayer();
	Size m_szWinSize;
	Point m_ptCenter;

	Joypad *m_pJoypad;
	ImageScene *m_pImageScene;
	CAttackButton *m_pAttackButton;
	CAttackEffect *m_pAttackButtonA;
	CAttackEffect *m_pAttackButtonB;
};
#endif