//��ͣ����
//�������
//

#ifndef _PauseLayer_H_
#define _PauseLayer_H_
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;

//��ͣ��
class PauseLayer :public Layer	
{
public:
	static Scene* createScene(char* name);
	virtual bool init();
	CREATE_FUNC(PauseLayer);

	Sprite* spriteOn;
	Sprite* spriteDown;

	void musicSet(Ref* pSender);

	void GameOver(float delta);
	void GameWin(float delta);
private:
};

#endif // !_PauseLayer_H_
