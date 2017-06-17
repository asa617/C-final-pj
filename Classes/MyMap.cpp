//Created by loahao
#include "cocos2d.h"
#include "MyMap.h"
#include "Hero.h"

USING_NS_CC;

MyMap::MyMap()
{
	Map1 = NULL;
}
MyMap::~MyMap()
{
}

void MyMap::Init(const char* MapName1)
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Map1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(MapName1));
	Map1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	auto size = Map1->getContentSize();
	float scaleX = (float)visibleSize.width / (float)size.width;
	float scaleY = (float)visibleSize.height / (float)size.height;
	Map1->setScale(scaleX, scaleY);
	this->addChild(Map1, 1);
}
