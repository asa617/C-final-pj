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

class SelectLevel:public cocos2d::Layer
{
public:
    CREATE_FUNC(SelectLevel);

    void addMenuItem(cocos2d::MenuItem *item);
    //更新位置
    void updatePosition();
    //更新位置，有动画
    void updatePositionWithAnimation();
    //位置矫正 修改位置 forward为移动方向 超过1/3进1 true为正向
    void rectify(bool forward);
    virtual bool init();
    //重置
    void reset();
    //返回被选中的item
    cocos2d::MenuItem * getCurrentItem();
    
private:
    //设置当前索引
    void setIndex(int index);
    //设置当前菜单项的索引号
    float getIndex();
    //动作计算公式
    float calcFunction(float index, float width);
    //菜单项的索引号
    float _index;
    //上一个菜单项的索引号
    float _lastIndex;
    //菜单项集合
    cocos2d::Vector<cocos2d::MenuItem *> _items;
    //监听函数
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    //动画结束调用函数，确定哪一个菜单项在前面
    void actionEndCallBack(float dx);
    //当前被选择的item
    cocos2d::MenuItem *_selectedItem;
};


#endif /* SelectLevel_hpp */
