//Created by Xuan_32  6.11



#ifndef __GlobalData__H__
#define __GlobalData__H__

#include <iostream>
#include "cocos2d.h"

class Monster;

USING_NS_CC;

extern Vector<Monster*> monsterOneList;
extern Vector<Monster*> monsterTwoList;
extern Vector<Monster*> monsterThreeList;
extern Vector<Monster*> monsterShowList;
extern int m_iSelectGate;
//����ѡ��Ĺؿ�
extern bool m_bFlag1;
extern bool m_bFlag2;
extern bool m_bFlag3;
// ����ͼ����
#define MAPMAX 3
// ��ǰѡ��Ĺؿ�
extern int iLevel;

#endif
