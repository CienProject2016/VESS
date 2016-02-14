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

	void keyPressed(cocos2d::EventKeyboard::KeyCode key_code_, cocos2d::Event *event_);
	void keyReleased(cocos2d::EventKeyboard::KeyCode key_code_, cocos2d::Event *event_);

	ProgressTimer *smeltingBarGauge, *hammeringBarGauge, *quenchingBarGauge;
	Sprite* smeltingTimeOutLine, *hammeringTimeOutLine, *quenchingTimeOutLine;
	float smeltingGaugeDownSpeed, hammeringGaugeDownSpeed, quenchingGaugeDownSpeed;
	Sprite *smeltingImage, *hammeringImage, *quenchingImage;
	Sprite *upgradeImage, *repairImage;
	void setTouchListener();
	

	char attribute;
public :
	virtual bool init();
	virtual void update(float delta);
	void gaugeIncrease(ProgressTimer* gauge);
	void upgradeClicked();
	void repairClicked();
	void hideGauge();
	void completeButton();
	void checkRepairComplete();
	void checkLock();


	bool lock_01 = false;
	bool lock_02 = false;
	bool isUpgrade = true;
	bool isComplete = false;
	Sword getSword;
	CREATE_FUNC(UpgradeLayer);
};


#endif

