#pragma once

#ifndef __BACKGROUND_SPAWN_SCHEDULER_H__
#define __BACKGROUND_SPAWN_SCHEDULER_H__
#include <vector>
#include "BackgroundObject.h"
#include <stdlib.h>
using namespace std;

class FightLayer;
class BackgroundSpawnScheduler;

class EnumBackground {
public:
	enum OBJECT {CAVE_1_0, CAVE_1_1, CAVE_1_2, CAVE_1_3, CAVE_2_0, CAVE_2_1, CAVE_2_2, CAVE_2_3, CAVE_2_4, POLE, TILE};
	enum ArrangePosition {FIXED, RANDOM};
};

class BackgroundSpawnSchedulerTimer{
private:
	EnumBackground::OBJECT object;
	float timer; //진짜 타이머
	float spawnInterval; //timeWhenObjectSpawn    오브젝트 생성시 얼마 후에 다음 오브젝트를 생성할 지 결정하는 것//기본 연산 로직에 targetTImerScale을 곱해 간격 범위를 조절
	float spawnIntervalScaling; //0~1까지 얼마나 벌릴지.->크기 커질수록 오브젝트가 생성되는 간격이 커짐
	EnumBackground::ArrangePosition arrangePosition;
	BackgroundSpawnScheduler* mother;
	FightLayer* field;
public:
	void setTimer(float);
	void update(float deltaTime);//deltaTimeTime->프레임 사이 간격
	BackgroundSpawnSchedulerTimer();
	BackgroundSpawnSchedulerTimer(EnumBackground::OBJECT object, FightLayer* field, BackgroundSpawnScheduler* mother, float spawnIntervalScaling, EnumBackground::ArrangePosition arrangePosition);// 어떤오브젝트 생성할지, 생성한 걸 어떤레이어에 addchild 할지, 오브젝트 생성 간격
};

class BackgroundSpawnScheduler{ //fightlayer에서 딱 하나 생성. 각각의 오브젝트들을 따로따로 생성,운용(같이 움직이지 않는다)
private:
	BackgroundSpawnSchedulerTimer* cave;
	BackgroundSpawnSchedulerTimer pole;
	BackgroundSpawnSchedulerTimer tile;
	FightLayer* field;
public:
	void initBackground();	//미리 깔아둔다.
	float* backgroundSpeed;
	void createBackgound(EnumBackground::OBJECT object);
	BackgroundSpawnScheduler();
	BackgroundSpawnScheduler(FightLayer* layer);
	void update(float deltaTime); 
	void setBackgroundSpeed(float speed);
};



#endif