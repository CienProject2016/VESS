#include "BackgroundSpawnScheduler.h"
#include "FightLayer.h"

void BackgroundSpawnScheduler::update(float deltaTime) {
	mountain.update(deltaTime);
	pole.update(deltaTime);
	tile.update(deltaTime);
}

BackgroundSpawnScheduler::BackgroundSpawnScheduler() {
}


BackgroundSpawnScheduler::BackgroundSpawnScheduler(FightLayer* receiver) {
	mountain = BackgroundSpawnSchedulerTimer(EnumBackground::MOUNTAIN, receiver, 3, EnumBackground::ArrangePosition::RANDOM);
	pole = BackgroundSpawnSchedulerTimer(EnumBackground::POLE, receiver, 10, EnumBackground::ArrangePosition::RANDOM);
	tile = BackgroundSpawnSchedulerTimer(EnumBackground::TILE, receiver, 1.5, EnumBackground::ArrangePosition::FIXED);
	tile.setTimer(1.5);
}

void BackgroundSpawnSchedulerTimer::setTimer(float timer) {
	this->timer = timer;
}

void BackgroundSpawnSchedulerTimer::update(float deltaTime) {
	timer += deltaTime;
	if (arrangePosition == EnumBackground::ArrangePosition::RANDOM) {
		if (timer > monsterSpawnInterval) {
			timer = 0;
			monsterSpawnInterval = (((float)(rand() % 150)) / 100) * monsterSpawnIntervalScaling;
			field->createBackgound(object);
		}
	}
	else if (arrangePosition == EnumBackground::ArrangePosition::FIXED) {
		if (timer > monsterSpawnInterval) {
			timer = 0;
			monsterSpawnInterval = monsterSpawnIntervalScaling;
			field->createBackgound(object);
		}
	}
	
}

BackgroundSpawnSchedulerTimer::BackgroundSpawnSchedulerTimer(EnumBackground::OBJECT object, FightLayer* layer, float scale, EnumBackground::ArrangePosition arrangePosition) {
	this->object = object;
	field = layer;
	timer = 0;
	this->arrangePosition = arrangePosition;
	monsterSpawnInterval = 1;
	monsterSpawnIntervalScaling = scale;
}

BackgroundSpawnSchedulerTimer::BackgroundSpawnSchedulerTimer() {
	this->object = EnumBackground::MOUNTAIN;
	timer = 0;
	monsterSpawnInterval = 1;
}