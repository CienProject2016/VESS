#include "BackgroundSpawnScheduler.h"

void BackgroundSpawnScheduler::update(float dt) {
	mountain.update(dt);
	tree.update(dt);
}

BackgroundSpawnScheduler::BackgroundSpawnScheduler() {
}

BackgroundSpawnScheduler::BackgroundSpawnScheduler(EventReciever* reciever) {
	this->setReciever(reciever);
	mountain = BackgroundSpawnSchedulerTimer(EVENT::CreateMountain, reciever, 3);
	tree = BackgroundSpawnSchedulerTimer(EVENT::CreateTree, reciever, 1);
}

void BackgroundSpawnSchedulerTimer::update(float dt) {
	timer += dt;
	if (timer > targetTimer) {
		timer = 0;
		targetTimer = (((float)(rand() % 150)) / 100) * targetTimerScale;
		reciever->send(ev);
	}
}

BackgroundSpawnSchedulerTimer::BackgroundSpawnSchedulerTimer(EVENT::All ev, EventReciever* reciever, float scale) {
	this->ev = ev;
	this->setReciever(reciever);
	timer = 0;
	targetTimer = 1;
	targetTimerScale = scale;
}
BackgroundSpawnSchedulerTimer::BackgroundSpawnSchedulerTimer() {
	this->ev = EVENT::CreateMountain;
	timer = 0;
	targetTimer = 1;
}