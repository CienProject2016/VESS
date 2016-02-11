#pragma once
#include <vector>
#include "BackgroundObject.h"
#include <stdlib.h>
#ifndef __BACKGROUND_SPAWN_SCHEDULER_H__
#define __BACKGROUND_SPAWN_SCHEDULER_H__

using namespace std;

class FightLayer;

class EnumBackground {
public:
	enum Object {tree, mountain};
};

class BackgroundSpawnSchedulerTimer{
private:
	EnumBackground::Object object;
	float timer; //진짜 타이머
	float monsterSpawnInterval; //timeWhenObjectSpawn    오브젝트 생성시 얼마 후에 다음 오브젝트를 생성할 지 결정하는 것//기본 연산 로직에 targetTImerScale을 곱해 간격 범위를 조절 
	float monsterSpawnIntervalScaling; //0~1까지 얼마나 벌릴지.->크기 커질수록 오브젝트가 생성되는 간격이 커짐
	FightLayer* field;
public:
	void update(float deltaTime);//deltaTimeTime->프레임 사이 간격
	BackgroundSpawnSchedulerTimer();
	BackgroundSpawnSchedulerTimer(EnumBackground::Object object, FightLayer* layer, float scale);// 어떤오브젝트 생성할지, 생성한 걸 어떤레이어에 addchild 할지, 오브젝트 생성 간격 
};




class BackgroundSpawnScheduler{ //fightlayer에서 딱 하나 생성. 각각의 오브젝트들을 따로따로 생성,운용(같이 움직이지 않는다)
private:

	BackgroundSpawnSchedulerTimer mountain;
	BackgroundSpawnSchedulerTimer tree;
	FightLayer* field;
public:
	BackgroundSpawnScheduler();
	BackgroundSpawnScheduler(FightLayer* layer);
	void update(float deltaTime); 
};



#endif