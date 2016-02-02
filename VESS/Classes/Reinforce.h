#pragma once
#ifndef __Reinforce_H__
#define __Reinforce_H__
#include "cocos2d.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


class Reinforce : public cocos2d::Layer 
{
private:
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	int counter;
	void setTouchListener();

	
public:
	Reinforce();
	~Reinforce();
	static cocos2d::Scene* createScene();
	virtual bool init();
	void gazeCreate();
	void gazeIncrease();
	CREATE_FUNC(Reinforce);
};
#endif