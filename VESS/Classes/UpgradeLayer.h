#pragma once
#ifndef __UPGRADE_LAYER_H__
#define __UPGRADE_LAYER_H__

#include "cocos2d.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "GameScene.h"
#include "GameData.h"
#include "Item.h"
#include "GaugeLockChecker.h"
#include "UpgradeController.h"
#include "UpgradeCompleteLayer.h"
#include "Resources.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace std;

class UpgradeLayer : public Layer
{
public:
	enum ZOrder {SMELTING_IMAGE, HAMMERING_IMAGE, QUENCHING_IMAGE, UPGRADE_IMAGE, REPAIR_IMAGE, COMPLETE_UPGRADE_BUTTON, DIMENSION_GATE_IMAGE, ITEM_IMAGE, ITEM_NAME,UPGRADE_COMPLETE_LAYER};
	enum UpgradePhase { NONE, UPGRADE, REPAIR };
	enum CompleteButtonPhase { CAN_CLICK , CANNOT_CLICK};
	enum Gauge {SMELTING_GAUGE, HAMMERING_GAUGE, QUENCHING_GAUGE};
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
	void makeUpgradeCompleteLayer();
	void setUpgradeButtonOpacity(UpgradePhase);
	void clearGauge();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void keyPressed(cocos2d::EventKeyboard::KeyCode key_code_, cocos2d::Event *event_);
	void keyReleased(cocos2d::EventKeyboard::KeyCode key_code_, cocos2d::Event *event_);
	CREATE_FUNC(UpgradeLayer);
private:
	Label* itemName;
	Sprite* itemImage;	
	Sword getSword;
	int upgradeGold;
	int repairGold;
	bool lockBeforeHammering = false;
	bool lockBeforeQuenching = false;
	bool isUpgrade = true;
	char attribute;	
	UpgradePhase currentUpgradePhase;
	CompleteButtonPhase completeButtonPhase;

	ProgressTimer *smeltingBarGauge, *hammeringBarGauge, *quenchingBarGauge;
	Sprite* smeltingTimeOutLine, *hammeringTimeOutLine, *quenchingTimeOutLine;
	float smeltingGaugeDownSpeed, hammeringGaugeDownSpeed, quenchingGaugeDownSpeed;
	cocos2d::ui::Button *smeltingButton, *hammeringButton, *quenchingButton;

	Sprite *upgradeImage, *repairImage;
	Sprite* completeUpgradeButton, completeRepairButton;
	void setTouchListener();

};


#endif // __UPGRADE_LAYER_H___

