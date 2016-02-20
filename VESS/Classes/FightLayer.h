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
#include "Slime.h"
USING_NS_CC;

class FightLayer : public Layer
{
public:
	virtual bool init();


	void createBackgound(EnumBackground::OBJECT object);
	void monsterDead();
	void chestDead();
	CREATE_FUNC(FightLayer);
	
	void monsterSpawnUpdate(float delta);

	Monster* getMonster();
	Hero* getDaughter();
	Chest* getChest();
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

	void redrawDurabiltyButton();
	void redrawGold();
	void redrawTexture();

	float movingDistanceReal = 0;		//int ������ ��ȯ�� �� �Ҽ����� ���� �ʱ� ���� ����.
	float movingVelocity = 50;			//���� : �Ÿ�/��
	float* backgroundSpeed;
	Label* currentGoldLabel;
	BattleOperator* operator_;		//������ ���۷����� ��� ���� �ֱ� ������ ����ٸ� ����.
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
	BackgroundSpawnScheduler backgroundSpawnScheduler;

	void stageClear();
	void dimensionCallback(cocos2d::Ref* pSender);
	void attackCallback(cocos2d::Ref* pSender);
	void jumpCallback(cocos2d::Ref* pSender);
	void sitCallback(cocos2d::Ref* pSender);
	void reduceDurability();
	
	void setTouchListener();

	int damage = 20;

};

#endif