#include "BackgroundSpawnScheduler.h"
#include "FightLayer.h"

void BackgroundSpawnScheduler::update(float deltaTime) {
	mountain.update(deltaTime);
	tree.update(deltaTime);
}

BackgroundSpawnScheduler::BackgroundSpawnScheduler() {
}

BackgroundSpawnScheduler::BackgroundSpawnScheduler(FightLayer* reciever) {
	mountain = BackgroundSpawnSchedulerTimer(EnumBackground::mountain, reciever, 3);
	tree = BackgroundSpawnSchedulerTimer(EnumBackground::tree, reciever, 1);
}

void BackgroundSpawnSchedulerTimer::update(float deltaTime) {
	timer += deltaTime;
	if (timer > monsterSpawnInterval) {
		timer = 0;
		monsterSpawnInterval = (((float)(rand() % 150)) / 100) * monsterSpawnIntervalScaling;
		field->createBackgound(object);
	}
}

BackgroundSpawnSchedulerTimer::BackgroundSpawnSchedulerTimer(EnumBackground::Object object, FightLayer* layer, float Scale) {
	this->object = object;
	field = layer;
	timer = 0;
	monsterSpawnInterval = 1;
	monsterSpawnIntervalScaling = Scale;
}
BackgroundSpawnSchedulerTimer::BackgroundSpawnSchedulerTimer() {
	this->object = EnumBackground::mountain;
	timer = 0;
	monsterSpawnInterval = 1;
}
