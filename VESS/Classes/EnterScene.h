#ifndef __ENTER_SCENE_H__
#define __ENTER_SCENE_H__

#include "cocos2d.h"
#include "DialogScene.h"
#include "ui/CocosGUI.h"
#define stageDoor 1

class EnterScene : public cocos2d::Layer
{
private:
	void enterCallback(int);

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(EnterScene);
};

#endif // __ENTER_SCENE_H__

