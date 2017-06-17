//Created by loahao
#ifndef MyMap_H__
#define MyMap_H__
#include "cocos2d.h"
USING_NS_CC;

class Hero;

class MyMap :public Node
{
public:
	MyMap();
	~MyMap();

	void Init(const char* MapName1);
	CREATE_FUNC(MyMap);
private:
	Sprite* Map1;
};

#endif

