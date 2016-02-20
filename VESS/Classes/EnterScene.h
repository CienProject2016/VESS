#ifndef __ENTER_SCENE_H__
#define __ENTER_SCENE_H__

#include "cocos2d.h"
#include "DialogScene.h"
#include "ui/CocosGUI.h"

class EnterScene : public cocos2d::Layer
{
private:
	void enterCallback(Ref*, ui::Widget::TouchEventType, int);
	const static int stageDoor = 1;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();


	// implement the "static create()" method manually
	CREATE_FUNC(EnterScene);
};

#endif // __ENTER_SCENE_H__