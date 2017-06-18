//‘›Õ£ΩÁ√Ê
// \file PauseLayer.h
//
//
// \created by Xuan_32
// \date 06_13
//

#ifndef _PauseLayer_H_
#define _PauseLayer_H_
#include "cocos2d.h"
#include "extensions\cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;

//‘›Õ£≤„
class PauseLayer :public Layer {
public:
	static Scene* createScene(RenderTexture* rt);
	virtual bool init();
	CREATE_FUNC(PauseLayer);

	Sprite* spriteOn;
	Sprite* spriteDown;

	void musicSet(Ref* pSender);

private:
};


#endif // !_PauseLayer_H_
