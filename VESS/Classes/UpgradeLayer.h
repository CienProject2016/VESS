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
#include "GaugeLockChecker.h"

USING_NS_CC;
using namespace std;


class UpgradeLayer : public Layer
{
private:
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	class State *current;

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
	void checkLock();



	

	bool lock_01 = false;
	bool lock_02 = false;
	bool isUpgrade = true;
	bool isComplete = false;

	bool pressed_smelting = false;
	bool pressed_hammering = false;
	bool pressed_quenching = false;

	void setCurrent(State *state_) 
	{
		current = state_;
	}

	void doingUpgrade();
	void doingRepair();
	Sword getSword;
	CREATE_FUNC(UpgradeLayer);
};

//class State
//{
//public:
//	virtual void doingUpgrade(UpgradeLayer *layer);
//	virtual void doingRepair(UpgradeLayer *layer);
//};
//void UpgradeLayer::doingUpgrade() 
//{
//	current->doingUpgrade(this);
//}
//
//void UpgradeLayer::doingRepair()
//{
//	current->doingRepair(this);
//}




//class doingUpgrade : public State
//{
//public:
//
//};


#endif

