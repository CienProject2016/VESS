#pragma once
#ifndef __FIGHT_LAYER_H__
#define __FIGHT_LAYER_H__

#include "WindowSize.h"
#include "BattleOperator.h"
#include "MonsterSpawnScheduler.h"
#include "GameData.h"
#include "Stage.h"
#include "Hero.h"
#include "Monster.h"


USING_NS_CC;

class FightLayer : public Layer, public EventReciever
{
private : 
	float moving_distance_real = 0;		//int ������ ��ȯ�� �� �Ҽ����� ���� �ʱ� ���� ����.
	float moving_velocity = 10;			//���� : �Ÿ�/��
	BattleOperator* controller;
	Hero* daughter;
	Monster* monster;
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);



	void setTouchListener();
public :
	void send(EVENT::All e);
	virtual bool init();
	void spawnMonster(float);
	CREATE_FUNC(FightLayer);
	void attackCallback(cocos2d::Ref* pSender);
	void dodgeCallback(cocos2d::Ref* pSender);

};

#endif