#include "BackgroundSpawnScheduler.h"
#include "FightLayer.h"
#include "ResourcePath.h"

void BackgroundSpawnScheduler::update(float deltaTime) {
	cave[0].update(deltaTime);
	cave[1].update(deltaTime);
	cave[2].update(deltaTime);
	cave[3].update(deltaTime);
	cave[4].update(deltaTime);
	cave[5].update(deltaTime);
	cave[6].update(deltaTime);
	cave[7].update(deltaTime);
	cave[8].update(deltaTime);
	pole.update(deltaTime);
	tile.update(deltaTime);
}

BackgroundSpawnScheduler::BackgroundSpawnScheduler() {
}

void BackgroundSpawnScheduler::initBackground() {
	float fwidth = 1;
	
	while (0 < fwidth) {
		BackgroundObject* obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_1_0, Vec2(1.2f, 1.05f), 1.5f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::TOP);
		obj->setSpeed(backgroundSpeed, 500, 0.8f);
		fwidth = obj->initBackgroundObject(fwidth, 1);
		obj->setNoAccelSpeed();
		field->addChild(obj, -105);
	}
	fwidth = 1;
	while (0 < fwidth) {
		BackgroundObject* obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_1_1, Vec2(1.1f, 1.1f), 1.2f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::TOP);
		obj->setSpeed(backgroundSpeed, 500, 0.8f);
		fwidth = obj->initBackgroundObject(fwidth, 1) - 0.1f;
		obj->setNoAccelSpeed();
		field->addChild(obj, -105);
	}
	fwidth = 1;
	while (0 < fwidth) {
		BackgroundObject* obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_1_2, Vec2(1.1f, 0.7f), 1, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::BOTTOM);
		obj->setSpeed(backgroundSpeed, 500, 0.8f);
		fwidth = obj->initBackgroundObject(fwidth, 1) - 0.2f;
		obj->setNoAccelSpeed();
		field->addChild(obj, -105);
	}
	fwidth = 1;
	while (0 < fwidth) {
		BackgroundObject* obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_1_3, Vec2(1.1f, 1), 1, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::BOTTOM);
		obj->setSpeed(backgroundSpeed, 500, 0.8f);
		fwidth = obj->initBackgroundObject(fwidth, 1) - 0.3f;
		obj->setNoAccelSpeed();
		field->addChild(obj, -105);
	}
	fwidth = 1;
	while (0 < fwidth) {
		BackgroundObject* obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_2_0, Vec2(1.2f, 1), 2, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::TOP);
		obj->setSpeed(backgroundSpeed, 500, 1.2f);
		fwidth = obj->initBackgroundObject(fwidth, 1)+0.05f;
		obj->setNoAccelSpeed();
		field->addChild(obj, -105);
	}
	fwidth = 1;
	while (0 < fwidth) {
		BackgroundObject* obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_2_1, Vec2(1.2f, 1), 2, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::TOP);
		obj->setSpeed(backgroundSpeed, 500, 1.2f);
		fwidth = obj->initBackgroundObject(fwidth, 1) - 0.2f;
		obj->setNoAccelSpeed();
		field->addChild(obj, -105);
	}
	fwidth = 1;
	while (0 < fwidth) {
		BackgroundObject* obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_2_2, Vec2(1.2f, 0.5f), 2, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::BOTTOM);
		obj->setSpeed(backgroundSpeed, 500, 1.2f);
		fwidth = obj->initBackgroundObject(fwidth, 1) - 0.3f;
		obj->setNoAccelSpeed();
		field->addChild(obj, -105);
	}
	fwidth = 1;
	while (0 < fwidth) {
		BackgroundObject* obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_2_3, Vec2(1.2f, 1.0f), 2.5f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::BOTTOM);
		obj->setSpeed(backgroundSpeed, 500, 1.2f);
		fwidth = obj->initBackgroundObject(fwidth, 1) - 0.3f;
		obj->setNoAccelSpeed();
		field->addChild(obj, -105);
	}
	fwidth = 1;
	while (0 < fwidth) {
		BackgroundObject* obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_2_4, Vec2(1.2f, 1.0f), 2.5f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::BOTTOM);
		obj->setSpeed(backgroundSpeed, 500, 1.2f);
		fwidth = obj->initBackgroundObject(fwidth, 1) - 0.3f;
		obj->setNoAccelSpeed();
		field->addChild(obj, -105);
	}
	fwidth = 1;
	while (0 < fwidth) {
		BackgroundObject* pole = BackgroundObject::create();
		pole->setImage(ImagePath::POLE_IMAGE, Vec2(1, 0.7f), 0.6f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::TOP);
		pole->setSpeed(backgroundSpeed, 500, 3);
		fwidth = pole->initBackgroundObject(fwidth, 3);
		pole->setNoAccelSpeed();
		field->addChild(pole, -99);
	}
	fwidth = 1;
	while (0 < fwidth) {
		BackgroundObject *tile = BackgroundObject::create();
		tile->setImage(ImagePath::TILE_BACKGROUND, Vec2(1.3f, 0.38f), 1.0f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::BOTTOM);
		tile->setSpeed(backgroundSpeed, 500, 3);
		fwidth = tile->initBackgroundObject(fwidth, 1);
		tile->setNoAccelSpeed();
		field->addChild(tile, -101);
	}
}

BackgroundSpawnScheduler::BackgroundSpawnScheduler(FightLayer* field) {
	this->field = field;
	cave = (BackgroundSpawnSchedulerTimer*)malloc(sizeof(BackgroundSpawnSchedulerTimer) * 9);
	cave[0] = BackgroundSpawnSchedulerTimer(EnumBackground::CAVE_1_0, field, this, 5, EnumBackground::ArrangePosition::FIXED);
	cave[1] = BackgroundSpawnSchedulerTimer(EnumBackground::CAVE_1_1, field, this, 3, EnumBackground::ArrangePosition::RANDOM);
	cave[2] = BackgroundSpawnSchedulerTimer(EnumBackground::CAVE_1_2, field, this, 3, EnumBackground::ArrangePosition::RANDOM);
	cave[3] = BackgroundSpawnSchedulerTimer(EnumBackground::CAVE_1_3, field, this, 3, EnumBackground::ArrangePosition::RANDOM);
	cave[4] = BackgroundSpawnSchedulerTimer(EnumBackground::CAVE_2_0, field, this, 5, EnumBackground::ArrangePosition::FIXED);
	cave[5] = BackgroundSpawnSchedulerTimer(EnumBackground::CAVE_2_1, field, this, 3, EnumBackground::ArrangePosition::RANDOM);
	cave[6] = BackgroundSpawnSchedulerTimer(EnumBackground::CAVE_2_2, field, this, 3, EnumBackground::ArrangePosition::RANDOM);
	cave[7] = BackgroundSpawnSchedulerTimer(EnumBackground::CAVE_2_3, field, this, 3, EnumBackground::ArrangePosition::RANDOM);
	cave[8] = BackgroundSpawnSchedulerTimer(EnumBackground::CAVE_2_4, field, this, 5, EnumBackground::ArrangePosition::RANDOM);
	pole = BackgroundSpawnSchedulerTimer(EnumBackground::POLE, field, this, 2, EnumBackground::ArrangePosition::RANDOM);
	tile = BackgroundSpawnSchedulerTimer(EnumBackground::TILE, field, this, 0.5f, EnumBackground::ArrangePosition::FIXED);
	tile.setTimer(1.5);
	backgroundSpeed = new float(-100);
	initBackground();
}

void BackgroundSpawnScheduler::createBackgound(EnumBackground::OBJECT object) {
	BackgroundObject* obj;
	switch (object) {
	case EnumBackground::POLE:
		obj = BackgroundObject::create();
		obj->setImage(ImagePath::POLE_IMAGE, Vec2(1, 0.7f), 0.6f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::TOP);
		obj->setSpeed(backgroundSpeed, 500, 3);
		obj->setNoAccelSpeed();
		field->addChild(obj, -99);
		break;
	case EnumBackground::TILE:
		obj = BackgroundObject::create();
		obj->setImage(ImagePath::TILE_BACKGROUND, Vec2(1.3f, 0.38f), 1.0f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::BOTTOM);
		obj->setSpeed(backgroundSpeed, 500, 3);
		obj->setNoAccelSpeed();
		field->addChild(obj, -101);
		break;
	case EnumBackground::CAVE_1_0:
		obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_1_0, Vec2(1.2f, 1.05f), 1.5f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::TOP);
		obj->setSpeed(backgroundSpeed, 500, 0.8f);
		obj->setNoAccelSpeed();
		field->addChild(obj, -105);
		break;
	case EnumBackground::CAVE_1_1:
		obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_1_1, Vec2(1.1f, 1.1f), 1.2f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::TOP);
		obj->setSpeed(backgroundSpeed, 500, 0.8f);
		obj->setNoAccelSpeed();
		field->addChild(obj, -105);
		break;
	case EnumBackground::CAVE_1_2:
		obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_1_2, Vec2(1.1f, 0.7f), 1, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::BOTTOM);
		obj->setSpeed(backgroundSpeed, 500, 0.8f);
		obj->setNoAccelSpeed();
		field->addChild(obj, -105);
		break;
	case EnumBackground::CAVE_1_3:
		obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_1_3, Vec2(1.1f, 1), 1, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::BOTTOM);
		obj->setSpeed(backgroundSpeed, 500, 0.8f);
		obj->setNoAccelSpeed();
		field->addChild(obj, -105);
		break;
	case EnumBackground::CAVE_2_0:
		obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_2_0, Vec2(1.2f, 1), 2, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::TOP);
		obj->setSpeed(backgroundSpeed, 500, 1.2f);
		obj->setNoAccelSpeed();
		field->addChild(obj, -104);
		break;
	case EnumBackground::CAVE_2_1:
		obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_2_1, Vec2(1.2f, 1), 2, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::TOP);
		obj->setSpeed(backgroundSpeed, 500, 1.2f);
		obj->setNoAccelSpeed();
		field->addChild(obj, -104);
		break;
	case EnumBackground::CAVE_2_2:
		obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_2_2, Vec2(1.2f, 0.5f), 2, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::BOTTOM);
		obj->setSpeed(backgroundSpeed, 500, 1.2f);
		obj->setNoAccelSpeed();
		field->addChild(obj, -104);
		break;
	case EnumBackground::CAVE_2_3:
		obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_2_3, Vec2(1.2f, 1.0f), 2.5f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::BOTTOM);
		obj->setSpeed(backgroundSpeed, 500, 1.2f);
		obj->setNoAccelSpeed();
		field->addChild(obj, -104);
		break;
	case EnumBackground::CAVE_2_4:
		obj = BackgroundObject::create();
		obj->setImage(ImagePath::BACKGROUND_CAVE_2_4, Vec2(1.2f, 1.0f), 2.5f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::BOTTOM);
		obj->setSpeed(backgroundSpeed, 500, 1.2f);
		obj->setNoAccelSpeed();
		field->addChild(obj, -104);
		break;
	}

}

void BackgroundSpawnScheduler::setBackgroundSpeed(float speed) {
	*backgroundSpeed = speed;
}

void BackgroundSpawnSchedulerTimer::setTimer(float timer) {
	this->timer = timer;
}

void BackgroundSpawnSchedulerTimer::update(float deltaTime) {
	timer += deltaTime;
	if (arrangePosition == EnumBackground::ArrangePosition::RANDOM) {
		if (timer > spawnInterval) {
			timer = 0;
			spawnInterval = (((float)(rand() % 150)) / 100) * spawnIntervalScaling;
			mother->createBackgound(object);
		}
	}
	else if (arrangePosition == EnumBackground::ArrangePosition::FIXED) {
		if (timer > spawnIntervalScaling) {
			timer = 0;
			mother->createBackgound(object);
		}
	}
	
}

BackgroundSpawnSchedulerTimer::BackgroundSpawnSchedulerTimer(EnumBackground::OBJECT object, FightLayer* field, BackgroundSpawnScheduler* mother, float spawnIntervalScaling, EnumBackground::ArrangePosition arrangePosition) {
	this->object = object;
	this->mother = mother;
	this->field = field;
	timer = 0;
	this->arrangePosition = arrangePosition;
	spawnInterval = 1;
	this->spawnIntervalScaling = spawnIntervalScaling;
}

BackgroundSpawnSchedulerTimer::BackgroundSpawnSchedulerTimer() {
	this->object = EnumBackground::CAVE_1_0;
	timer = 0;
	spawnInterval = 1;
}

