#pragma once
#ifndef __Upgrade_LAYER_H__
#define __Upgrade_LAYER_H__

#include "cocos2d.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "GameScene.h"
#include "GameData.h"
#include "Item.h"

USING_NS_CC;
using namespace std;

class UpgradeLayer : public Layer
{
private:
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	CCProgressTimer *gauge_1, *gauge_2, *gauge_3;
	CCSprite* timeOutline1, *timeOutline2, *timeOutline3;
	float gauge_speed_1, gauge_speed_2, gauge_speed_3;
	Sprite *smelting_image, *hammering_image, *quenching_image;
	Sprite *upgrade_image, *repair_image;
	void setTouchListener();

	char attribute;
public :
	virtual bool init();
	virtual void update(float delta);
	void gaugeIncrease(CCProgressTimer* gauge);
	void upgradeClicked();
	void repairClicked();
	void hideGauge();
	void completeButton();

	bool isUpgrade = true;
	bool isComplete = false;
	Sword getSword;
	CREATE_FUNC(UpgradeLayer);
	

};

#endif