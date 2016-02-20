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
#include "Monster.h"
USING_NS_CC;

class FightLayer : public Layer
{
public:
	virtual bool init();

	enum ZOrder { SMELTING_IMAGE, HAMMERING_IMAGE, QUENCHING_IMAGE, UPGRADE_IMAGE, REPAIR_IMAGE, COMPLETE_UPGRADE_BUTTON, COMPLETE_REPAIR_BUTTON, DIMENSION_GATE_IMAGE, ITEM_IMAGE, ITEM_NAME, UPGRADE_COMPLETE_LAYER, MINI_POPUP_LAYER };
	void createBackgound(EnumBackground::OBJECT object);
	void monsterDead();
	CREATE_FUNC(FightLayer);
	
	void monsterSpawnUpdate(float delta);

	Monster* getMonster();
	Hero* getDaughter();

	void disappearHeartImage();
private : 
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
	void showGameover();
	void initGameoverPopup(string);

	float movingDistanceReal = 0;		//int 형으로 변환할 때 소수값을 잃지 않기 위해 선언.
	float movingVelocity = 50;			//단위 : 거리/초
	float* backgroundSpeed;
	Label* currentGoldLabel;
	BattleOperator* operator_;		//기존에 오퍼레이터 라는 예약어가 있기 때문에 언더바를 붙임.
	Hero* daughter;
	Monster* monster;
	Sprite* itemImage;
	Label* itemName;
	
	virtual void update(float delta);
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	BackgroundSpawnScheduler backgroundSpawnScheduler;

	void stageClear();
	void dimensionCallback(cocos2d::Ref* pSender);
	void attackCallback(cocos2d::Ref* pSender);
	void jumpCallback(cocos2d::Ref* pSender);
	void sitCallback(cocos2d::Ref* pSender);
	void reduceDurability();
	
	void setTouchListener();

	int lifeCount = 3;
	int fullLifeCount = lifeCount;
	int damage = 20;
	int temp;
};

#endif