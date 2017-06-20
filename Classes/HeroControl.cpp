//Created by loahao

#include "HeroControl.h"
#include "OperateLayer.h"
#include "ImageScene.hpp"

CActionButton::CActionButton()
{
	m_pSprite = NULL;
	m_pOperateLayer = NULL;
}

CActionButton::~CActionButton()
{

}

bool CActionButton::init(const char *szImage)//按钮初始化
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());

		m_pSprite = Sprite::create(szImage);
		addChild(m_pSprite);

		initTouch();

		bRet = true;
	} while (0);
	return bRet;
}

void CActionButton::updateProjection(void)
{

}

void CActionButton::click()
{
	if (IsCanClick() && m_pOperateLayer)
	{
		m_pOperateLayer->attackButtonClick(GetAttackType());
		beganAnimation();
	}
}

void CActionButton::clickUp()
{
	endedAnimation();
}

cocos2d::Rect CActionButton::GetRect()
{
	Size size = m_pSprite->getContentSize();
	return  Rect(-size.width / 2, -size.height / 2, size.width, size.height);
}

void CActionButton::onEnter()
{
	Node::onEnter();
}

void CActionButton::onExit()
{
	Node::onExit();
}

bool CActionButton::containsLocation(Touch* touch)
{
	return GetRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool CActionButton::ccTouchBegan(Touch* touch, Event* event)
{
	// 区域判断
	if (!this->containsLocation(touch))
		return false;

	// 播放点击动画
	click();

	return true;
}

void CActionButton::ccTouchMoved(Touch* touch, Event* event)
{
}

void CActionButton::ccTouchEnded(Touch* touch, Event* event)
{
	endedAnimation();
}

CAttackButton::CAttackButton() //按钮主函数
{
	m_fDefaultScale = 0.35;
	m_fMaxScale = 0.5;

	m_pNormal = Sprite::create("AttackO.png");
	m_pNormal->retain();

	FiniteTimeAction *pScale = ScaleTo::create(0.1, m_fDefaultScale);
	FiniteTimeAction *pFadeIn = FadeIn::create(0.1);
	m_pInAction = Spawn::create(pScale, pFadeIn, NULL);
	m_pInAction->retain();

	pScale = ScaleTo::create(0.2f, m_fMaxScale);
	FiniteTimeAction *pFade = FadeOut::create(0.2);
	m_pOutAction = Spawn::create(pScale, pFade, NULL);
	m_pOutAction->retain();

	m_fClickTime = 0.0f;
}

CAttackButton::~CAttackButton()
{
	CC_SAFE_RELEASE(m_pNormal);
	CC_SAFE_RELEASE(m_pInAction);
	CC_SAFE_RELEASE(m_pOutAction);
}

bool CAttackButton::init(const char *szImage)
{
	bool bRet = CActionButton::init(szImage);
	if (m_pNormal)
		m_pNormal->setScale(m_fMaxScale);
	return bRet;
}

CAttackButton* CAttackButton::create(const char *szImage)
{
	CAttackButton *pAttackButton = new CAttackButton();
	if (pAttackButton && pAttackButton->init(szImage))
	{
		pAttackButton->autorelease();
		return pAttackButton;
	}
	else
	{
		delete pAttackButton;
		return NULL;
	}
}

void CAttackButton::beganAnimation()
{
	removeChild(m_pNormal);
	addChild(m_pNormal);
	m_pNormal->runAction((Action*)m_pInAction->clone());

	timeval timeVal;
	gettimeofday(&timeVal, 0);
	m_fClickTime = timeVal.tv_sec * 1000 + timeVal.tv_usec / 1000;
}

void CAttackButton::endedAnimation()
{
	m_pNormal->stopAllActions();
	m_pNormal->runAction((Action*)m_pOutAction->clone());
}

bool CAttackButton::IsCanClick()
{
	timeval timeVal;
	gettimeofday(&timeVal, 0);
	float curTime = timeVal.tv_sec * 1000 + timeVal.tv_usec / 1000;
	return (curTime - m_fClickTime > 600);
}

CAttackEffect::CAttackEffect()
{
	Sprite *pCold = Sprite::create("AttackFreeze.png");
	m_pNormal = ProgressTimer::create(pCold);
	m_pNormal->setType(kCCProgressTimerTypeRadial);
	m_pNormal->setReverseDirection(true);
	m_pNormal->setScale(0.43);
	m_pNormal->retain();

	FiniteTimeAction *to = ProgressTo::create(0, 99.999);
	FiniteTimeAction *to1 = ProgressTo::create(2, 0);
	FiniteTimeAction *callback = CCCallFunc::create(this, callfunc_selector(CAttackEffect::endColdTime));
	m_pInAction = Sequence::create(to, to1, callback, NULL);
	m_pInAction->retain();
	m_bCanClick = true;
}

CAttackEffect::~CAttackEffect()
{
	CC_SAFE_RELEASE(m_pNormal);
	CC_SAFE_RELEASE(m_pInAction);
}


CAttackEffect* CAttackEffect::create(const char *szImage)
{
	CAttackEffect *pAttackEffect = new CAttackEffect();
	if (pAttackEffect && pAttackEffect->init(szImage))
	{
		pAttackEffect->autorelease();
		return pAttackEffect;
	}
	else
	{
		delete pAttackEffect;
		return NULL;
	}
}

void CAttackEffect::beganAnimation()
{
	removeChild(m_pNormal);
	addChild(m_pNormal);
	m_pNormal->runAction((Action*)m_pInAction->clone());
	m_bCanClick = false;
}

void CAttackEffect::endedAnimation()
{

}

bool CAttackEffect::IsCanClick()
{
	return m_bCanClick;
}

void CAttackEffect::endColdTime()
{
	m_bCanClick = true;
}

void CActionButton::initTouch()
{
//	CCLog("initTouch");
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(CActionButton::ccTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(CActionButton::ccTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(CActionButton::ccTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
Joypad::Joypad()
{
	m_szWinSize = Director::sharedDirector()->getWinSize();
	m_ptCenter = ccp(m_szWinSize.width / 2, m_szWinSize.height / 2);
	m_pControlSprite = NULL;
	m_fDefaultRotation = m_fRotation = 0.0f;

	m_pImageScene = NULL;
	m_bKeydown = false;
}

Joypad::~Joypad()
{

}

bool Joypad::init()
{
	bool Ret = false;
	//CC_BREAK_IF(!Layer::init());
	if (!Layer::init())
		return false;
	// 控制杆所在位置
	m_ptDefaultPoint = ccp(110, 110);
	// 默认旋转角度，以使开口正对右侧
	m_fDefaultRotation = 26;
	// 实际旋转角度
	m_fRotation = 0;

	setPosition(m_ptDefaultPoint);

	// 添加显示精灵
	addChild(Sprite::create("Joypad1.png"));
	addChild(Sprite::create("Joypad2.png"));
	m_pControlSprite = Sprite::create("Joypad3.png");
	addChild(m_pControlSprite);
	addChild(Sprite::create("Joypad4.png"));

	UpdateRotation();

	// 事件处理
	initTouch();

	Ret = true;

	return Ret;
}

void Joypad::KeyStart(float degrees)
{
	if (m_pImageScene)
		m_pImageScene->actionJoypadStart(m_fRotation);
}

void Joypad::KeyUpdate(float degrees)
{
	m_fRotation = degrees;
	UpdateRotation();
	if (m_pImageScene)
		m_pImageScene->actionJoypadUpdate(m_fRotation);
}

void Joypad::KeyEnded(float degrees)
{
	if (m_pImageScene)
		m_pImageScene->actionJoypadEnded(m_fRotation);
}

void Joypad::onEnter()
{
	Layer::onEnter();
}

void Joypad::onExit()
{
	Layer::onExit();
}

bool Joypad::onTouchBegan(Touch* touch, Event* event)
{

	Point location = touch->getLocation();

	// 点击点的范围判断
	Point curPoint = touch->getLocation();
	if (curPoint.x > m_szWinSize.width / 2 || curPoint.y > m_szWinSize.height / 2)
		return false;

	UpdateTouchRotation(touch, event);
	UpdateRotation();

	if (m_pImageScene)
		m_pImageScene->actionJoypadStart(m_fRotation);
	return true;
}

void Joypad::onTouchMoved(Touch* touch, Event* event)
{
	Point location = touch->getLocation();

	UpdateTouchRotation(touch, event);
	UpdateRotation();

	if (m_pImageScene)
		m_pImageScene->actionJoypadUpdate(m_fRotation);
}

void Joypad::onTouchEnded(Touch* touch, Event* event)
{
	Point location = touch->getLocation();

	UpdateTouchRotation(touch, event);
	UpdateRotation();

	if (m_pImageScene)
		m_pImageScene->actionJoypadEnded(m_fRotation);
}

void Joypad::UpdateRotation()
{
	m_pControlSprite->setRotation(m_fDefaultRotation + m_fRotation);
}

void Joypad::UpdateTouchRotation(Touch* touch, Event* event)
{
	Point curPoint = touch->getLocation();
	Point sp = ccpSub(curPoint, m_ptDefaultPoint);
	float angle = ccpToAngle(sp);
	angle *= -57.29577951;			// ...
	angle = (angle < 0) ? 360 + angle : angle;
	m_fRotation = angle;
}

void Joypad::initTouch()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(Joypad::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Joypad::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Joypad::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

