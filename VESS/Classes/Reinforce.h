#pragma once
#ifndef __Reinforce_H__
#define __Reinforce_H__
#include "cocos2d.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "GameScene.h"
#include "UpgradeLayer.h"
USING_NS_CC;
using namespace std;

class Reinforce : public cocos2d::Layer 
{
private:
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void setTouchListener();
	CCProgressTimer *gazing1, *gazing2, *gazing3;
	float gazingSpeed1, gazingSpeed2, gazingSpeed3;


	
public:
	Reinforce();
	~Reinforce();
	static cocos2d::Scene* createScene();
	virtual bool init();
	void gazeIncrease(CCProgressTimer* gazing);
	CREATE_FUNC(Reinforce);
	virtual void update(float delta);
};
#endif