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

class FightLayer : public Layer, public EventReciever
{
private : 
	float moving_distance_real = 0;		//int 형으로 변환할 때 소수값을 잃지 않기 위해 선언.
	float moving_velocity = 50;			//단위 : 거리/초
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
	float* background_speed;
	void setTouchListener();

public :
	void send(EVENT::All e);
	virtual bool init();
	void spawnMonster(float);
	CREATE_FUNC(FightLayer);
	

};

#endif