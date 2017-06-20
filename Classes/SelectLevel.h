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
	//��Ӳ˵���
	void updatePosition();
	//����λ��
	void updatePositionWithAnimation();
	//����λ���Լ�����
	void rectify(bool forward);
	virtual bool init();
	//��ʼ��
	void reset();
	//����
	cocos2d::MenuItem * getCurrentItem();

private:
	//���õ�ǰ����
	void setIndex(int index);
	//���õ�ǰ������
	float getIndex();
	//��ѧ����ʽwidth*index/(abs(index)+CALC_A) ,����CALC_AΪ����
	float calcFunction(float index, float width);
	//�˵��˵����������
	float _index;
	//��һ�β˵���������
	float _lastIndex;
	//�˵���ϣ��½����鱣������˳��
	cocos2d::Vector<cocos2d::MenuItem *> _items;
	//��������
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	//�����������ú���
	void actionEndCallBack(float dx);
	//��ǰ��ѡ���item
	cocos2d::MenuItem *_selectedItem;
};


#endif /* SelectLevel_hpp */