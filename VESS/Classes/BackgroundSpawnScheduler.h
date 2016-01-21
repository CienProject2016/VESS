#pragma once
#include <vector>
#include "EVENT.h"
#include "BackgroundObject.h"
#include <stdlib.h>
#ifndef __BACKGROUND_SPAWN_SCHEDULER_H__
#define __BACKGROUND_SPAWN_SCHEDULER_H__

using namespace std;

class BackgroundSpawnSchedulerTimer : public EventSender{
private:
	EVENT::All ev;
	float timer;
	float targetTimer;
	float targetTimerScale;
public:
	void update(float dt);
	BackgroundSpawnSchedulerTimer();
	BackgroundSpawnSchedulerTimer(EVENT::All ev, EventReciever* reciever, float scale);
};

class BackgroundSpawnScheduler : public EventSender{
private:

	BackgroundSpawnSchedulerTimer mountain;
	BackgroundSpawnSchedulerTimer tree;

public:
	BackgroundSpawnScheduler();
	BackgroundSpawnScheduler(EventReciever* reciever);
	void update(float dt);
};



#endif