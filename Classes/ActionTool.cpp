// Created by loahao on 2017/6/10


#include "ActionTool.h"
#include "cocos2d.h"

USING_NS_CC;

Animate* ActionTool::animationWithFrameName(const char *frameName, int iloops, float delay)
{
	int index = 1;
	SpriteFrame* frame = NULL;
	Animation* animation = Animation::create();
	// 遍历图片帧  
	do
	{
		String* name = String::createWithFormat("%s%d.png", frameName, index++);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name->getCString());

		if (frame == NULL)
		{
			break;
		}
		animation->addSpriteFrame(frame);
	} while (true);
	animation->setDelayPerUnit(delay);
	animation->setRestoreOriginalFrame(true);
	Animate *animate = Animate::create(animation);
	return animate;
}
Animate* ActionTool::animationWithFrameAndNum(const char *frameName,int framecount,float delay)
{		
	SpriteFrame* frame = NULL;
	Animation* animation = Animation::create();
	// 遍历图片帧  
	for (int index = 1; index <= framecount; index++)
	{
		String* name = String::createWithFormat("%s%d.png", frameName, index++);
		animation->addSpriteFrameWithFile(name->getCString());
	}
	animation->setDelayPerUnit(delay);
	animation->setRestoreOriginalFrame(true);
	Animate *animate = Animate::create(animation);
	return animate;
}