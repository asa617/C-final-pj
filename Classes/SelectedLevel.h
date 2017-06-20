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
	//����λ��
	void updatePosition();
	//����λ�ã��ж���
	void updatePositionWithAnimation();
	//λ�ý��� �޸�λ�� forwardΪ�ƶ����� ����1/3��1 trueΪ����
	void rectify(bool forward);
	virtual bool init();
	//����
	void reset();
	//���ر�ѡ�е�item
	cocos2d::MenuItem * getCurrentItem();

private:
	//���õ�ǰ����
	void setIndex(int index);
	//���õ�ǰ�˵����������
	float getIndex();
	//�������㹫ʽ
	float calcFunction(float index, float width);
	//�˵����������
	float _index;
	//��һ���˵����������
	float _lastIndex;
	//�˵����
	cocos2d::Vector<cocos2d::MenuItem *> _items;
	//��������
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	//�����������ú�����ȷ����һ���˵�����ǰ��
	void actionEndCallBack(float dx);
	//��ǰ��ѡ���item
	cocos2d::MenuItem *_selectedItem;
};


#endif /* SelectLevel_hpp */
