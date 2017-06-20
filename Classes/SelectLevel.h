//
//  SelectLevel.hpp
//  test
//
//  Created by -T.c on 2017/6/18.
//
//

#ifndef SelectLevel_hpp
#define SelectLevel_hpp

#include <stdio.h>
#include <cocos2d.h>

class SelectLevel :public cocos2d::Layer
{
public:
	CREATE_FUNC(SelectLevel);

	void addMenuItem(cocos2d::MenuItem *item);
	//添加菜单项
	void updatePosition();
	//更新位置
	void updatePositionWithAnimation();
	//更新位置以及动画
	void rectify(bool forward);
	virtual bool init();
	//初始化
	void reset();
	//重置
	cocos2d::MenuItem * getCurrentItem();

private:
	//设置当前索引
	void setIndex(int index);
	//设置当前索引号
	float getIndex();
	//数学计算式width*index/(abs(index)+CALC_A) ,其中CALC_A为常数
	float calcFunction(float index, float width);
	//菜单菜单项的索引号
	float _index;
	//上一次菜单的索引号
	float _lastIndex;
	//菜单项集合，新建数组保存它的顺序
	cocos2d::Vector<cocos2d::MenuItem *> _items;
	//监听函数
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	//动画结束调用函数
	void actionEndCallBack(float dx);
	//当前被选择的item
	cocos2d::MenuItem *_selectedItem;
};


#endif /* SelectLevel_hpp */