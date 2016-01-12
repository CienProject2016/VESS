#ifndef __HelloWorldScene_SCENE_H__
#define __HelloWorldScene_SCENE_H__

#include "cocos2d.h"
#define locationx  5001


class HelloWorldScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	
	int number[4];                    
	int count = 0;
	int life = 3;
	
	void sprite();
	void showNum(int number[]);
	void score();
	void setLife();
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuCallBack(Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorldScene);
	

};

#endif // __HELLOWORLD_SCENE_H__
