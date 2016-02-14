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
public:
	enum UpgradePhase { UPGRADE, REPAIR, NONE };
	enum CompleteButtonPhase { CAN_CLICK , CANNOT_CLICK};
	virtual bool init();
	virtual void update(float delta);
	void increaseGauge(CCProgressTimer* gauge);
	void upgradeClicked();
	void repairClicked();
	void hideBeforeUpgradeResources();
	void showCompleteButton();
	void checkComplete();
	void checkLock();
	void completeClicked();
	void showUiButton(UpgradePhase);

	Sword getSword;
	CREATE_FUNC(UpgradeLayer);

private:
	Sprite* itemImage;
	int upgradeGold;
	int repairGold;
	bool lockBeforeHammering = false;
	bool lockBeforeQuenching = false;
	bool isUpgrade = true;
	bool isComplete = false;
	char attribute;
	UpgradePhase currentUpgradePhase;
	CompleteButtonPhase completeButtonPhase;
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void keyPressed(cocos2d::EventKeyboard::KeyCode key_code_, cocos2d::Event *event_);
	void keyReleased(cocos2d::EventKeyboard::KeyCode key_code_, cocos2d::Event *event_);

	CCProgressTimer *smeltingBarGauge, *hammeringBarGauge, *quenchingBarGauge;
	CCSprite* smeltingTimeOutLine, *hammeringTimeOutLine, *quenchingTimeOutLine;
	float smeltingGaugeDownSpeed, hammeringGaugeDownSpeed, quenchingGaugeDownSpeed;
	Sprite *smeltingImage, *hammeringImage, *quenchingImage;
	Sprite *upgradeImage, *repairImage;
	Sprite* completeUpgradeButton, completeRepairButton;
	void setTouchListener();
	
};


#endif

