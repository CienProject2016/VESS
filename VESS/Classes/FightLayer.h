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
private : 
	float movingDistanceReal = 0;		//int ������ ��ȯ�� �� �Ҽ����� ���� �ʱ� ���� ����.
	float movingVelocity = 50;			//���� : �Ÿ�/��
	float* backgroundSpeed;
	BattleOperator* controller;
	Hero* daughter;
	Monster* monster;
	

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	BackgroundSpawnScheduler backgroundSpawnScheduler;

	void initBackground();
	void updateBackground(float dt);
	
	void stageClear();
	void dimensionCallback(cocos2d::Ref* pSender);
	void attackCallback(cocos2d::Ref* pSender);
	void jumpCallback(cocos2d::Ref* pSender);
	void sitCallback(cocos2d::Ref* pSender);
	void setTouchListener();
	

public :
	virtual bool init();
	void spawnMonster(float);
	void monsterDead();

	void createBackgound(EnumBackground::Obj obj);
	CREATE_FUNC(FightLayer);
	
	

	Monster* getMonster();
	Hero* getDaughter();
};

#endif