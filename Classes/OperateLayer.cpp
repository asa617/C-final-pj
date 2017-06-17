//Created by loahao
#include "Hero.h"
#include "OperateLayer.h"
#include "cocos2d.h"
#include "HeroControl.h"

USING_NS_CC;

OperateLayer::OperateLayer()
{
	m_szWinSize = Director::sharedDirector()->getWinSize();
	m_ptCenter = ccp(m_szWinSize.width / 2, m_szWinSize.height / 2);
}
OperateLayer::~OperateLayer()
{

}



bool OperateLayer::init()
{
	bool ret = false;
	// 添加攻击按钮
	m_pAttackButton = CAttackButton::create("Attack.png");
	m_pAttackButton->setPosition(ccp(m_szWinSize.width - 80, 80));
	m_pAttackButton->SetOperateLayer(this);
	m_pAttackButton->SetAttackType(abtAttack);
	addChild(m_pAttackButton);

	// 其他攻击
	m_pAttackButtonA = CAttackEffect::create("AttackA.png");
	m_pAttackButtonA->setPosition(ccp(m_szWinSize.width - 200, 60));
	m_pAttackButtonA->SetOperateLayer(this);
	m_pAttackButtonA->SetAttackType(abtAttackA);
	addChild(m_pAttackButtonA);

	m_pAttackButtonB = CAttackEffect::create("AttackB.png");
	m_pAttackButtonB->setPosition(ccp(m_szWinSize.width - 165, 165));
	m_pAttackButtonB->SetOperateLayer(this);
	m_pAttackButtonB->SetAttackType(abtAttackB);
	addChild(m_pAttackButtonB);
	ret = true;
	return ret;
}

void OperateLayer::attackButtonClick(int nAttackType)
{
	//CCLog("  attackButtonClick");
	if (m_pImageScene)
		m_pImageScene->attackButtonClick(nAttackType);
}



void OperateLayer::keyAttack(int nButtonType)
{
	if (nButtonType == abtAttack && m_pAttackButton->IsCanClick())
	{
		//CCLog("abtAttack");
		m_pAttackButton->click();
	}
	else if (nButtonType == abtAttackA && m_pAttackButtonA->IsCanClick())
	{
		//CCLog("abtAttack a");
		m_pAttackButtonA->click();
	}
	else if (nButtonType == abtAttackB && m_pAttackButtonB->IsCanClick())
	{
		//CCLog("abtAttack b");
		m_pAttackButtonB->click();
	}
}

void OperateLayer::keyAttackUp(int nButtonType)
{
	if (nButtonType == abtAttack)
	{
		m_pAttackButton->clickUp();
	}
}

void OperateLayer::setDelegate(ImageScene *pImageScene)
{
	m_pImageScene = pImageScene;
//	m_pJoypad->setGameLayer(pGameLayer);
}


