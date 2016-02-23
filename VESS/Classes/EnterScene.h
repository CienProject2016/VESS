#ifndef __ENTER_SCENE_H__
#define __ENTER_SCENE_H__

#include "cocos2d.h"
#include "DialogScene.h"
#include "ui/CocosGUI.h"
#include "GameData.h"

class EnterScene : public cocos2d::Layer
{
private:
	void enterCallback(Ref*, ui::Widget::TouchEventType, int);
	void restartCallback(Ref*, ui::Widget::TouchEventType);
	
	void initGoldLabel();
	void redrawGold();
	Label* currentGoldLabel;
	Label* itemNameLabel;




	Size visibleSize;
	Vec2 origin;

	const static int STAGE_DOOR = 1;
	
	const static int STAGE_LABEL = 100;


public:
	static cocos2d::Scene* createScene();
	virtual void update(float delta);
	virtual bool init();
	

	// implement the "static create()" method manually
	CREATE_FUNC(EnterScene);
};




#endif // __ENTER_SCENE_H__