#pragma once
#ifndef __UPGRADE_LAYER_H__
#define __UPGRADE_LAYER_H__

#include "cocos2d.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "GameScene.h"
#include "GameData.h"
#include "Sword.h"
#include "Shield.h"
#include "GaugeLockChecker.h"
#include "UpgradeController.h"
#include "UpgradeCompleteLayer.h"
#include "ResourcePath.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace std;

class UpgradeLayer : public Layer
{
public:
	enum ZOrder {SMELTING_IMAGE, HAMMERING_IMAGE, QUENCHING_IMAGE, UPGRADE_IMAGE, REPAIR_IMAGE, COMPLETE_UPGRADE_BUTTON, COMPLETE_REPAIR_BUTTON, DIMENSION_GATE_IMAGE, ITEM_IMAGE, ITEM_NAME,UPGRADE_COMPLETE_LAYER, MINI_POPUP_LAYER, GRAY_LAYER, PAUSE_BUTTON};
	enum UpgradePhase { NONE, UPGRADE, REPAIR };
	enum GaugeType {SMELTING, HAMMERING, QUENCHING};
	virtual bool init();
	virtual void update(float delta);

	void initPauseButton();
	void initPhase();
	void initSmithAndBackground();
	void initButtonUi();
	void initGaugeBar();
	void initUpgradeCompleteLayer();
	void initLabelInfo();
	void initItemImage();
	void initMiniPopup(string);
	void initPercentageLabel();
	void setListener();

	void showSoundEffect(GaugeType);
	void updatePercentLabel();
	void redrawUpgradeGoldLabel();
	void increaseGauge(CCProgressTimer* gauge);
	void increaseGaugeCallback(Ref*, ui::Widget::TouchEventType, CCProgressTimer* gauge, GaugeType gaugeType);
	void gaugeChecker();
	void upgradeClicked(Ref*, ui::Widget::TouchEventType);
	void repairClicked(Ref*, ui::Widget::TouchEventType);
	void pauseCallback(cocos2d::Ref*, ui::Widget::TouchEventType);
	void hideBeforeUpgradeResources();
	void showCompleteButton();
	void checkComplete();
	void upgradeResult();
	void completeClicked(Ref*, ui::Widget::TouchEventType);
	void showUiButton(UpgradePhase);
	void showUpgradeCompleteLayer(bool);
	
	void setUpgradeButtonOpacity(UpgradePhase);
	void clearGauge();
	void checkGaugeLock();
	void keyPressed(cocos2d::EventKeyboard::KeyCode key_code_, cocos2d::Event *event_);
	void keyReleased(cocos2d::EventKeyboard::KeyCode key_code_, cocos2d::Event *event_);
	CREATE_FUNC(UpgradeLayer);
private:
	int cheatCount;
	Size visibleSize;
	Vec2 origin;
	Label* itemName;
	Label* upgradeLabel;
	Label* repairLabel;
	Label *repairPercentLabel, *upgradePercentLabel;
	Sprite* itemImage;
	Sprite *strongFire, *weakFire, *middleFire;
	Sword getSword;
	int upgradeGold;
	int repairGold;
	int gaugeStatus[3];
	Item::Grade upgradeCoefficient;
	bool lockBeforeHammering = false;
	bool lockBeforeQuenching = false;
	bool isUpgrade = true;
	char attribute;	
	UpgradePhase currentUpgradePhase;

	ProgressTimer *smeltingBarGauge, *hammeringBarGauge, *quenchingBarGauge;
	Sprite* smeltingTimeOutLine, *hammeringTimeOutLine, *quenchingTimeOutLine;
	float smeltingGaugeDownSpeed, hammeringGaugeDownSpeed, quenchingGaugeDownSpeed;
	cocos2d::ui::Button *smeltingButton, *hammeringButton, *quenchingButton, *completeUpgradeButton, *completeRepairButton, *upgradeButton, *repairButton;


};


#endif // __UPGRADE_LAYER_H___

