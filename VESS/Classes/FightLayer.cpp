#pragma once
#include "FightLayer.h"
#include "Monster.h"
#include "Hero.h"
#include "MonsterSpawnScheduler.h"
#include "GameData.h"
#include "Stage.h"

bool FightLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	log("fightLayer visibleWidthSize : %f", visibleSize.width);
	log("fightLayer visibleHeightSize : %f", visibleSize.height);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	log("fightLayer origin.x : %f, origin.y : %f", origin.x, origin.y);

	// µþÀÌ »ý¼ºµÊ
	auto daughter = Hero::create();
	//¸ó½ºÅÍ°¡ »ý¼ºµÊ
	

	// add the unit as a child to this layer
	this->addChild(daughter, 0);
	
	this->schedule(schedule_selector(FightLayer::spawnMonster));
	return true;
}

void FightLayer::spawnMonster(float delta)
{
	int moving_distance = GameData::getInstance()->getMovingDistance();
	Stage stage_data = GameData::getInstance()->getStage();
	vector<int> distance_data = stage_data.getMonsterLengthInfo();
	if (MonsterSpawnScheduler::isMonsterSpawnTime(moving_distance, distance_data)) {
		auto monster = Monster::create("slime");
		this->addChild(monster, 1);
	}
	GameData::getInstance()->setMovingDistance(moving_distance + 1);
}