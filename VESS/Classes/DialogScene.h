#ifndef __DIALOG_SCENE_H__
#define __DIALOG_SCENE_H__

#include "cocos2d.h"
#include "Dialog.h"
#include "GameScene.h"
#include "GameData.h"
#include <vector>

class DialogScene : public cocos2d::Layer
{
private:
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void setTouchListener();
	vector<Dialog> *dialogData;
	vector<Dialog>::iterator dialogIterator;

public:
	void showNextDialog();
	bool hasNextDialog();
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(DialogScene);
};

#endif // __DIALOG_SCENE_H__