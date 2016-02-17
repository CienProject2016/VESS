#pragma once

#ifndef __BACKGROUND_SPAWN_SCHEDULER_H__
#define __BACKGROUND_SPAWN_SCHEDULER_H__
#include <vector>
#include "BackgroundObject.h"
#include <stdlib.h>
using namespace std;

class FightLayer;

class EnumBackground {
public:
	enum OBJECT {TREE, MOUNTAIN};
};

class BackgroundSpawnSchedulerTimer{
private:
	EnumBackground::OBJECT object;
	float timer; //진짜 ?�?�머
	float monsterSpawnInterval; //timeWhenObjectSpawn    ?�브?�트 ?�성???�마 ?�에 ?�음 ?�브?�트�??�성??지 결정?�는 �?/기본 ?�산 로직??targetTImerScale??곱해 간격 범위�?조절 
	float monsterSpawnIntervalScaling; //0~1까�? ?�마??벌릴지.->?�기 커질?�록 ?�브?�트가 ?�성?�는 간격??커짐
	FightLayer* field;
public:
	void update(float deltaTime);//deltaTimeTime->?�레???�이 간격
	BackgroundSpawnSchedulerTimer();
	BackgroundSpawnSchedulerTimer(EnumBackground::OBJECT object, FightLayer* layer, float scale);// ?�떤?�브?�트 ?�성?��?, ?�성??�??�떤?�이?�에 addchild ?��?, ?�브?�트 ?�성 간격 
};

class BackgroundSpawnScheduler{ //fightlayer?�서 ???�나 ?�성. 각각???�브?�트?�을 ?�로?�로 ?�성,?�용(같이 ?�직이지 ?�는??
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