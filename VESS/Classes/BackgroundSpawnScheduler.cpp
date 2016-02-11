#include "BackgroundSpawnScheduler.h"
#include "FightLayer.h"

void BackgroundSpawnScheduler::update(float deltaTime) {
	mountain.update(deltaTime);
	tree.update(deltaTime);
}

BackgroundSpawnScheduler::BackgroundSpawnScheduler() {
}

BackgroundSpawnScheduler::BackgroundSpawnScheduler(FightLayer* reciever) {
	mountain = BackgroundSpawnSchedulerTimer(EnumBackground::MOUNTAIN, reciever, 3);
	tree = BackgroundSpawnSchedulerTimer(EnumBackground::TREE, reciever, 1);
}

void BackgroundSpawnSchedulerTimer::update(float deltaTime) {
	timer += deltaTime;
	if (timer > monsterSpawnInterval) {
		timer = 0;
		monsterSpawnInterval = (((float)(rand() % 150)) / 100) * monsterSpawnIntervalScaling;
		field->createBackgound(object);
	}
}

BackgroundSpawnSchedulerTimer::BackgroundSpawnSchedulerTimer(EnumBackground::OBJECT object, FightLayer* layer, float scale) {
	this->object = object;
	field = layer;
	timer = 0;
	monsterSpawnInterval = 1;
	monsterSpawnIntervalScaling = scale;
}

BackgroundSpawnSchedulerTimer::BackgroundSpawnSchedulerTimer() {
	this->object = EnumBackground::MOUNTAIN;
	timer = 0;
	monsterSpawnInterval = 1;
}
