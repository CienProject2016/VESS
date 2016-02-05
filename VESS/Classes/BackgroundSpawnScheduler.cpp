#include "BackgroundSpawnScheduler.h"
#include "FightLayer.h"

void BackgroundSpawnScheduler::update(float dt) {
	mountain.update(dt);
	tree.update(dt);
}

BackgroundSpawnScheduler::BackgroundSpawnScheduler() {
}

BackgroundSpawnScheduler::BackgroundSpawnScheduler(FightLayer* reciever) {
	mountain = BackgroundSpawnSchedulerTimer(EnumBackground::mountain, reciever, 3);
	tree = BackgroundSpawnSchedulerTimer(EnumBackground::tree, reciever, 1);
}

void BackgroundSpawnSchedulerTimer::update(float dt) {
	timer += dt;
	if (timer > targetTimer) {
		timer = 0;
		targetTimer = (((float)(rand() % 150)) / 100) * targetTimerScale;
		field->createBackgound(obj);
	}
}

BackgroundSpawnSchedulerTimer::BackgroundSpawnSchedulerTimer(EnumBackground::Obj obj, FightLayer* layer, float scale) {
	this->obj = obj;
	field = layer;
	timer = 0;
	targetTimer = 1;
	targetTimerScale = scale;
}
BackgroundSpawnSchedulerTimer::BackgroundSpawnSchedulerTimer() {
	this->obj = EnumBackground::mountain;
	timer = 0;
	targetTimer = 1;
}