// Created by loahao on 2017/6/10


#ifndef ActionTool_H__
#define ActionTool_H__

#include "cocos2d.h"  

USING_NS_CC;

class ActionTool{
public:     
	static Animate* animationWithFrameName(const char *frameName, int iloops, float delay);
	static Animate* animationWithFrameAndNum(const char *frameName, int num, float delay);
};

#endif 