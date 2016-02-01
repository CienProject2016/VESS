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
	enum Obj {tree, mountain};
};

class BackgroundSpawnSchedulerTimer{
private:
	EnumBackground::Obj obj;
	float timer;
	float targetTimer;
	float targetTimerScale;
	FightLayer* field;
public:
	void update(float dt);
	BackgroundSpawnSchedulerTimer();
	BackgroundSpawnSchedulerTimer(EnumBackground::Obj obj, FightLayer* layer, float scale);
};

class BackgroundSpawnScheduler{
private:

	BackgroundSpawnSchedulerTimer mountain;
	BackgroundSpawnSchedulerTimer tree;
	FightLayer* field;
public:
	BackgroundSpawnScheduler();
	BackgroundSpawnScheduler(FightLayer* layer);
	void update(float dt);
};



#endif