#pragma once
#include "FightLayer.h"
#include "StageClearLayer.h"

#define attackTag 2001
#define jumpTag 2002
#define sitTag 2003
#define kFinalDistance 4001


bool FightLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Create Background
	initBackground();
	backgroundSpawnScheduler = BackgroundSpawnScheduler(this);
	background_speed = new float(-100);

	//딸이 생성됨
	daughter = Hero::create();
	daughter->setReciever(this);
	//몬스터가 생성됨
	
	
	//버튼
	auto dimension_Button = MenuItemImage::create("Images/dimension_Gate.png", "Images/dimensionButton.png", "Images/DisabledButton.png", CC_CALLBACK_1(FightLayer::dimensionCallback, this));
	auto attack_Button = MenuItemImage::create("Images/AttackButton.png", "Images/AttackButton.png", "Images/DisabledButton.png", CC_CALLBACK_1(FightLayer::attackCallback, this));
	auto jump_Button = MenuItemImage::create("Images/JumpButton.png", "Images/JumpButton.png", "Images/DisabledButton.png", CC_CALLBACK_1(FightLayer::jumpCallback, this));
	auto sit_Button = MenuItemImage::create("Images/SitButton.png", "Images/SitButton.png", "Images/DisabledButton.png", CC_CALLBACK_1(FightLayer::sitCallback, this));
	
	dimension_Button->setScale(1.0f);
	attack_Button->setScale(2.0f);
	jump_Button->setScale(1.5f);
	sit_Button->setScale(1.5f);

	auto battle_Menu = Menu::create(dimension_Button, attack_Button, jump_Button, sit_Button, NULL);
	battle_Menu->setPosition(Vec2(origin.x + visibleSize.width*0.325f, origin.y + visibleSize.height*0.15f));
	battle_Menu->alignItemsHorizontally();
	battle_Menu->alignItemsHorizontallyWithPadding(visibleSize.width*0.05f);


	auto attackMessage = Label::createWithTTF("Attack!", "fonts/Marker Felt.ttf", 100);
	attackMessage->setPosition(Vec2(origin.x + visibleSize.width *0.325f, origin.y + visibleSize.height - attackMessage->getContentSize().height));
	attackMessage->enableOutline(Color4B::WHITE, 1);
	attackMessage->setVisible(false);

	auto jumpMessage = Label::createWithTTF("Jump!", "fonts/Marker Felt.ttf", 100);
	jumpMessage->setPosition(Vec2(origin.x + visibleSize.width *0.325f, origin.y + visibleSize.height - jumpMessage->getContentSize().height));
	jumpMessage->enableOutline(Color4B::WHITE, 1);
	jumpMessage->setVisible(false);

	auto sitMessage = Label::createWithTTF("sit!", "fonts/Marker Felt.ttf", 100);
	sitMessage->setPosition(Vec2(origin.x + visibleSize.width *0.325f, origin.y + visibleSize.height - sitMessage->getContentSize().height));
	sitMessage->enableOutline(Color4B::WHITE, 1);
	sitMessage->setVisible(false);

	//dimensionMessage->setTag(dimensionTag);
	attackMessage->setTag(attackTag);
	jumpMessage->setTag(jumpTag);
	sitMessage->setTag(sitTag);


	this->schedule(schedule_selector(FightLayer::spawnMonster));

	// add the sprite as a child to this layer
	this->addChild(battle_Menu, 2);
	this->addChild(attackMessage, 3);
	this->addChild(jumpMessage, 4);
	this->addChild(sitMessage, 5);


	// add the unit as a child to this layer
	this->addChild(daughter, 0);
	//인풋을 받을 controller 생성
	controller = new BattleOperator();
	this->addChild(controller, 1000000);
	
	setTouchListener();
	
	return true;
}

void FightLayer::initBackground() {
	auto ground = Sprite::create("Images/ground_basic.png");
	int ground_width = ground->getTexture()->getPixelsWide();
	float ground_rate = fightLayerSize.width / ground_width;
	ground->setScale(ground_rate);
	ground->setPosition(Vec2(fightLayerSize.width / 2, fightLayerSize.height * 0.22f));
	this->addChild(ground, -100);
	
	auto sky = Sprite::create("Images/sky_basic.png");
	int sky_width = sky->getTexture()->getPixelsWide();
	float sky_height = sky->getTexture()->getPixelsHigh();
	float sky_rate = fightLayerSize.width / sky_width;
	sky_height = sky_height * sky_rate;
	sky->setScale(sky_rate);
	sky->setPosition(Vec2(fightLayerSize.width / 2, fightLayerSize.height - (sky_height / 2)));
	this->addChild(sky, -200);
}

void FightLayer::updateBackground(float dt) {

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
		*background_speed = 0;
		
	}

	if (monster == NULL) {
		moving_distance_real += delta * moving_velocity;
		if (moving_distance == kFinalDistance) {
			this->stageClear();
			CCLOG("stageClear");
		}
	}
	if (1 <= moving_distance_real) {
		GameData::getInstance()->setMovingDistance(moving_distance + (int)moving_distance_real);
		moving_distance_real -= (int)moving_distance_real;
	}

	backgroundSpawnScheduler.update(delta);
}

void FightLayer::stageClear() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto stageClearLayer = StageClearLayer::create();
	stageClearLayer->setContentSize(Size(100, 100));
	stageClearLayer->setPosition(Vec2(origin.x + visibleSize.width *0.325f, origin.y + visibleSize.height*0.5f));

	this->addChild(stageClearLayer, 10000);

}


void FightLayer::dimensionCallback(cocos2d::Ref* pSender)
{
	/*
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto stageClearLayer = StageClearLayer::create();
	stageClearLayer->setContentSize(Size(100, 100));
	stageClearLayer->setPosition(Vec2(origin.x + visibleSize.width *0.325f, origin.y + visibleSize.height*0.5f));
	
	this->addChild(stageClearLayer, 10000);
	*/
		CCLOG("dimensionCallback");
}


void FightLayer::attackCallback(cocos2d::Ref* pSender)
{
	auto attackMessage  = (Label*)this->getChildByTag(attackTag);
	attackMessage->setVisible(true);
	auto fadeIn = FadeIn::create(0);
	auto delayTime = CCDelayTime::create(0.5f);
	auto fadeOut = FadeOut::create(0);;
	auto seq = CCSequence::create(fadeIn, delayTime, fadeOut, NULL);
	attackMessage->runAction(seq);
	daughter->attack();
	CCLOG("attackCallback");
}


void FightLayer::jumpCallback(cocos2d::Ref* pSender)
{
	auto jumpMessage = (Label*)this->getChildByTag(jumpTag);
	jumpMessage->setVisible(true);
	auto fadeIn = FadeIn::create(0);
	auto delayTime = CCDelayTime::create(0.5f);
	auto fadeOut = FadeOut::create(0);;
	auto seq = CCSequence::create(fadeIn, delayTime, fadeOut, NULL);
	jumpMessage->runAction(seq);
	daughter->jump();
	CCLOG("jumpCallback");
}

void FightLayer::sitCallback(cocos2d::Ref* pSender)
{
	auto sitMessage = (Label*)this->getChildByTag(sitTag);
	sitMessage->setVisible(true);
	auto fadeIn = FadeIn::create(0);
	auto delayTime = CCDelayTime::create(0.5f);
	auto fadeOut = FadeOut::create(0);;
	auto seq = CCSequence::create(fadeIn, delayTime, fadeOut, NULL);
	sitMessage->runAction(seq);
	daughter->sitDown();
	CCLOG("sitCallback");
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
		if(monster != NULL)
			monster->damage(30);
	}
	if (e == EVENT::MonsterDead) {
		this->removeChild(monster);
		monster = NULL;
		*background_speed = -100;
	}
	if (e == EVENT::CreateMountain) {
		BackgroundObject* mountain = BackgroundObject::create();
		mountain->setImage("Images/mountain.png", Vec2(1, 0.8f), 2.0f, BackgroundObject::ABSOLUTED, BackgroundObject::BOTTOM);
		mountain->setSpeed(background_speed, 100, 1);
		this->addChild(mountain, -105);
	}
	if (e == EVENT::CreateTree) {
		BackgroundObject* tree = BackgroundObject::create();
		tree->setImage("Images/tree.png", Vec2(1, 0.6f), 0.8f, BackgroundObject::ABSOLUTED, BackgroundObject::TOP);
		tree->setSpeed(background_speed, 190, 2);
		this->addChild(tree, -104);
	}
}