#pragma once
#ifndef __FIGHT_LAYER_H__
#define __FIGHT_LAYER_H__

#include "WindowSize.h"
#include "BattleOperator.h"
#include "MonsterSpawnScheduler.h"
#include "BackgroundSpawnScheduler.h"
#include "GameData.h"
#include "Stage.h"
#include "Hero.h"
#include "Chest.h"
#include "Monster.h"
USING_NS_CC;

class FightLayer : public Layer
{
public:
	virtual bool init();
	enum ZOrder { SMELTING_IMAGE, HAMMERING_IMAGE, QUENCHING_IMAGE, UPGRADE_IMAGE, REPAIR_IMAGE, COMPLETE_UPGRADE_BUTTON, COMPLETE_REPAIR_BUTTON, DIMENSION_GATE_IMAGE, ITEM_IMAGE, ITEM_NAME, UPGRADE_COMPLETE_LAYER, MINI_POPUP_LAYER };

	void monsterDead();
	void chestDead();
	CREATE_FUNC(FightLayer);

	void monsterSpawnUpdate(float delta);
	void initGameoverPopup(string);
	void showGameover();

	Monster* getMonster();
	Hero* getDaughter();
	Chest* getChest();
private: 
	Size visibleSize;
	Vec2 origin;

	Sprite ** heart;

	void initButton();
	void initGoldLabel();
	void initBackground();
	void initWeaponLabel();
	void initOperator();
	void initDaughter();
	void initHeart();
	void initDurabilityLabel();

	void redrawDurabilityButton();
	void redrawGold();
	void redrawTexture();
	void redrawHeart();
	void redrawDimensionGate();

	float movingDistanceReal = 0;		
	float movingVelocity = 50;
	Label* currentGoldLabel;
	BattleOperator* operator_;		
	Hero* daughter;
	Monster* monster;
	Chest* chest;
	Sprite* itemImage;
	Label* itemName;

	virtual void update(float delta);
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	BackgroundSpawnScheduler* backgroundSpawnScheduler;

	void stageClear();
	void dimensionCallback(cocos2d::Ref*, ui::Widget::TouchEventType);
	void attackCallback(cocos2d::Ref* pSender);
	void jumpCallback(cocos2d::Ref* pSender);
	void sitCallback(cocos2d::Ref* pSender);
	void reduceDurability();
	void setTouchListener();

	const int LIFE_COUNT = 3;
	int fullLifeCount = LIFE_COUNT;
	int damage = 20;
	int temp;
};

#endif