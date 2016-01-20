#pragma once
#include "FightLayer.h"

bool FightLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// µþÀÌ »ý¼ºµÊ
	daughter = Hero::create();
	daughter->setReciever(this);
	//¸ó½ºÅÍ°¡ »ý¼ºµÊ
	

	// add the unit as a child to this layer
	this->addChild(daughter, 0);
	//ÀÎÇ²À» ¹ÞÀ» controller »ý¼º
	controller = new BattleOperator();
	this->addChild(controller, 1000000);
	
	setTouchListener();
	
	this->schedule(schedule_selector(FightLayer::spawnMonster));
	return true;
}

void FightLayer::spawnMonster(float delta)
{
	int moving_distance = GameData::getInstance()->getMovingDistance();
	Stage stage_data = GameData::getInstance()->getStage();
	vector<int> distance_data = stage_data.getMonsterLengthInfo();
	if (MonsterSpawnScheduler::isMonsterSpawnTime(moving_distance, distance_data) && this->monster == NULL) {
		monster = Monster::create();
		monster->setReciever(this);
		this->addChild(monster, 1);
		GameData::getInstance()->setMovingDistance(moving_distance + 1);
	}
	if (monster == NULL) {
		moving_distance_real += delta * moving_velocity;
	}
	if (1 <= moving_distance_real) {
		GameData::getInstance()->setMovingDistance(moving_distance + (int)moving_distance_real);
		moving_distance_real -= (int)moving_distance_real;
	}
}

void FightLayer::setTouchListener()
{
	// make touch listener

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(FightLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(FightLayer::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(FightLayer::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(FightLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

bool FightLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	if (this->getBoundingBox().containsPoint(touch->getLocation())) {
		int min_x = this->boundingBox().getMinX();
		Vec2 pos = touch->getLocation();
		pos.x -= min_x;
		controller->startController(pos);
		return true;
	}
	return false;
}

void FightLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	if (this->getBoundingBox().containsPoint(touch->getLocation())) {
		int min_x = this->boundingBox().getMinX();
		Vec2 pos = touch->getLocation();
		pos.x -= min_x;
		controller->setTouchPos(pos);
	}
}

void FightLayer::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void FightLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	switch (controller->getState()) {
	case 0:		//CANCEL
		break;
	case 1:		//ATTACK
		daughter->attack();
		break;
	case 2:		//JUMP
		daughter->jump();
		break;
	case 3:		//AVOID
		daughter->avoid();
		break;
	case 4:		//SIT
		daughter->sitDown();
		break;
	}
	controller->endController();
}

void FightLayer::send(EVENT::All e) {
	if (e == EVENT::HeroAttack) {
		log("fightlayerAttack");
		monster->damage(30);
	}
	if (e == EVENT::MonsterDead) {
		log("fightlayerDead");
		this->removeChild(monster);
		monster = NULL;
	}
}