#pragma once
#include "FightLayer.h"

#define Print 2000

bool FightLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 딸이 생성됨
	daughter = Hero::create();
	daughter->setReciever(this);
	//몬스터가 생성됨
	
	//공격버튼
	auto attack_Button = MenuItemImage::create("Images/AttackButton.png", "Images/AttackButton.png", "Images/DisabledButton.png", CC_CALLBACK_1(FightLayer::attackCallback, this));
	auto dodge_Button = MenuItemImage::create("Images/DodgeButton.png", "Images/DodgeButton.png", "Images/DisabledButton.png", CC_CALLBACK_1(FightLayer::dodgeCallback, this));
	attack_Button->setScale(2.0f);
	dodge_Button->setScale(2.0f);

	auto battle_Menu = Menu::create(attack_Button, dodge_Button, NULL);
	battle_Menu->setPosition(Vec2(origin.x + visibleSize.width*0.2f, origin.y + visibleSize.height*0.15f));
	battle_Menu->alignItemsHorizontally();
	battle_Menu->alignItemsHorizontallyWithPadding(visibleSize.width*0.1f);


	//attackButton->setEnabled(false);
	//dodgeButton->setEnabled(false);

	auto attackMessage = Label::createWithTTF("Attack!", "fonts/Marker Felt.ttf", 100);
	attackMessage->setPosition(Vec2(origin.x + visibleSize.width *0.25f, origin.y + visibleSize.height - attackMessage->getContentSize().height));
	attackMessage->enableOutline(Color4B::WHITE, 1);
	attackMessage->setVisible(false);

	auto dodgeMessage = Label::createWithTTF("Dodge!", "fonts/Marker Felt.ttf", 100);
	dodgeMessage->setPosition(Vec2(origin.x + visibleSize.width *0.25f, origin.y + visibleSize.height - dodgeMessage->getContentSize().height));
	dodgeMessage->enableOutline(Color4B::WHITE, 1);
	dodgeMessage->setVisible(false);

	attackMessage->setTag(Print);
	dodgeMessage->setTag(Print);


	this->schedule(schedule_selector(FightLayer::spawnMonster));

	// add the sprite as a child to this layer
	this->addChild(battle_Menu, 2);
	this->addChild(attackMessage, 3);


	// add the unit as a child to this layer
	this->addChild(daughter, 0);
	//인풋을 받을 controller 생성
	controller = new BattleOperator();
	this->addChild(controller, 1000000);
	
	setTouchListener();
	
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


void FightLayer::attackCallback(cocos2d::Ref* pSender)
{
	auto attackMessage  = (Label*)this->getChildByTag(Print);
	attackMessage->setVisible(true);
	auto fadeIn = FadeIn::create(0);
	auto delayTime = CCDelayTime::create(3.0f);
	auto fadeOut = FadeOut::create(0);;
	auto seq = CCSequence::create(fadeIn, delayTime, fadeOut, NULL);
	attackMessage->runAction(seq);
	CCLOG("attackCallback");
}

void FightLayer::dodgeCallback(cocos2d::Ref* pSender)
{
	auto dodgeMessage = (Label*)this->getChildByTag(Print);
	dodgeMessage->setVisible(true);
	auto fadeIn = FadeIn::create(0);
	auto delayTime = CCDelayTime::create(3.0f);
	auto fadeOut = FadeOut::create(0);;
	auto seq = CCSequence::create(fadeIn, delayTime, fadeOut, NULL);
	dodgeMessage->runAction(seq);
	CCLOG("dodgeCallback");
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
		if(monster != NULL)
			monster->damage(30);
	}
	if (e == EVENT::MonsterDead) {
		log("fightlayerDead");
		this->removeChild(monster);
		monster = NULL;
	}
}