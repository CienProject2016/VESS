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


	void createBackgound(EnumBackground::OBJECT object);
	void monsterDead();
	CREATE_FUNC(FightLayer);
	
	void monsterSpawnUpdate(float delta);

	Monster* getMonster();
	Hero* getDaughter();

	void disappearHeartImage();
private : 
	const string DURABILITY_NAME = "������";
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

	float movingDistanceReal = 0;		//int ?�으�?변?�할 ???�수값을 ?��? ?�기 ?�해 ?�언.
	float movingVelocity = 50;			//?�위 : 거리/�?
	float* backgroundSpeed;
	Label* currentGoldLabel;
	BattleOperator* operator_;		//기존???�퍼?�이???�는 ?�약?��? ?�기 ?�문???�더바�? 붙임.
	Hero* daughter;
	Monster* monster;
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