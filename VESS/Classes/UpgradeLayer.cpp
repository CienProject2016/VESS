﻿#pragma once
#include "UpgradeLayer.h"
#include "GameData.h"

#define tag_number 50
#define gold "GOLD"

bool UpgradeLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(UpgradeLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	
	//키보드 입력
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(UpgradeLayer::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(UpgradeLayer::keyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto backgroundImage = Sprite::create("Images/background_image.png");
	auto background2Image = Sprite::create("Images/background2_image.png");
	auto smith_image = Sprite::create("Images/smith_image.png");
	smeltingImage = Sprite::create("Images/smelting_button.png");
	hammeringImage = Sprite::create("Images/hammering_button.png");
	quenchingImage = Sprite::create("Images/quenching_button.png");
	upgradeImage = Sprite::create("Images/upgrade_button.png");
	repairImage = Sprite::create("Images/repair_button.png");
	// position the sprite on the center of the screen
	backgroundImage->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	backgroundImage->setScale(2.4f);

	background2Image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	background2Image->setScale(2.0f);

	smith_image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	smith_image->setScale(2.0f);

	smeltingImage->setPosition(Vec2(origin.x + visibleSize.width * 0.12f, origin.y + visibleSize.height*0.4f));
	smeltingImage->setScale(1.0f);

	hammeringImage->setPosition(Vec2(origin.x + visibleSize.width * 0.22f, origin.y + visibleSize.height*0.2f));
	hammeringImage->setScale(1.0f);

	quenchingImage->setPosition(Vec2(origin.x + visibleSize.width * 0.32f, origin.y + visibleSize.height*0.4f));
	quenchingImage->setScale(1.0f);

	upgradeImage->setPosition(Vec2(origin.x + visibleSize.width * 0.11f, origin.y + visibleSize.height*0.9f));
	upgradeImage->setScale(1.0f);

	repairImage->setPosition(Vec2(origin.x + visibleSize.width * 0.325f, origin.y + visibleSize.height*0.9f));
	repairImage->setScale(1.0f);

	smeltingImage->setTag(tag_number+1);
	hammeringImage->setTag(tag_number+2);
	quenchingImage->setTag(tag_number+3);
	upgradeImage->setTag(tag_number+4);
	repairImage->setTag(tag_number + 5);

	//smelting bar create
	CCSprite *smeltingTimeBar = CCSprite::create("timebar.png");
	smeltingBarGauge = CCProgressTimer::create(smeltingTimeBar);
	smeltingBarGauge->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.95));
	smeltingBarGauge->setPercentage(0);
	smeltingBarGauge->setMidpoint(ccp(0, 0.5));
	smeltingBarGauge->setBarChangeRate(ccp(1, 0));
	smeltingBarGauge->setType(kCCProgressTimerTypeBar);
	smeltingTimeOutLine = CCSprite::create("timeoutline.png");
	smeltingTimeOutLine->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.95));
	smeltingGaugeDownSpeed = 10;

	//hammering bar create
	CCSprite *hammeringTimeBar = CCSprite::create("timebar.png");
	hammeringBarGauge = CCProgressTimer::create(hammeringTimeBar);
	hammeringBarGauge->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.9));
	hammeringBarGauge->setPercentage(0);
	hammeringBarGauge->setMidpoint(ccp(0, 0.5));
	hammeringBarGauge->setBarChangeRate(ccp(1, 0));
	hammeringBarGauge->setType(kCCProgressTimerTypeBar);
	hammeringTimeOutLine = CCSprite::create("timeoutline.png");
	hammeringTimeOutLine->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.9));
	hammeringGaugeDownSpeed = 20;

	//quenching bar create
	CCSprite *quenchingTimeBar = CCSprite::create("timebar.png");
	quenchingBarGauge = CCProgressTimer::create(quenchingTimeBar);
	quenchingBarGauge->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.85));
	quenchingBarGauge->setPercentage(0);
	quenchingBarGauge->setMidpoint(ccp(0, 0.5));
	quenchingBarGauge->setBarChangeRate(ccp(1, 0));
	quenchingBarGauge->setType(kCCProgressTimerTypeBar);
	quenchingTimeOutLine = CCSprite::create("timeoutline.png");
	quenchingTimeOutLine->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.85));
	quenchingGaugeDownSpeed = 25;


	// add the sprite as a child to this layer
	this->addChild(backgroundImage);
	this->addChild(background2Image);
	this->addChild(smith_image);

	int upgradeGold = GameData::getInstance()->getNeededUpgradeGold();
	auto upgradeLabel = Label::createWithTTF("강화골드", "fonts/arial.ttf", 50);
	upgradeLabel->setString(StringUtils::format("%d%s", upgradeGold, gold));
	// position the label on the center of the screen
	upgradeLabel->setPosition(Vec2(Vec2(origin.x + visibleSize.width * 0.13f, origin.y + visibleSize.height*0.86f)));
	upgradeLabel->setColor(ccc3(250, 250, 250)); 
	this->addChild(upgradeLabel, 1);


	auto swordSprite = Sprite::create("Images/sword.png");
	auto shieldSprite = Sprite::create("Images/shield.png");
	swordSprite->setPosition(Vec2(visibleSize.width / 10, visibleSize.height / 2));
	shieldSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	shieldSprite->setScale(.25f);
	swordSprite->setScale(.75f);
	swordSprite->setTag(600);
	shieldSprite->setTag(601);
	this->addChild(swordSprite);
	this->addChild(shieldSprite);
	
	int repairGold = GameData::getInstance()->getNeededRepairGold();
	auto repairLabel = Label::createWithTTF("수리골드", "fonts/arial.ttf", 50);
	repairLabel->setString(StringUtils::format("%d%s", repairGold, gold));
	repairLabel->setPosition(Vec2(origin.x + visibleSize.width * 0.33f, origin.y + visibleSize.height*0.86f));
	repairLabel->setColor(ccc3(250, 250, 250)); 
	this->addChild(repairLabel, 2);


	this->addChild(smeltingImage);
	this->addChild(hammeringImage);
	this->addChild(quenchingImage);
	this->addChild(upgradeImage);
	this->addChild(repairImage);
	this->addChild(smeltingBarGauge,2);
	this->addChild(smeltingTimeOutLine);
	this->addChild(hammeringBarGauge,2);
	this->addChild(hammeringTimeOutLine);
	this->addChild(quenchingBarGauge,2);
	this->addChild(quenchingTimeOutLine);
	this->scheduleUpdate();
	//강화 게이지바 숨김
	hideGauge();
	//망치,담금질 비활성화 색상으로 변경
	hammeringImage->setOpacity(120);
	quenchingImage->setOpacity(120);
	
	
	return true;
}
void UpgradeLayer::update(float delta) {

	smeltingBarGauge->setPercentage(smeltingBarGauge->getPercentage() - delta * smeltingGaugeDownSpeed);
	hammeringBarGauge->setPercentage(hammeringBarGauge->getPercentage() - delta * hammeringGaugeDownSpeed);
	quenchingBarGauge->setPercentage(quenchingBarGauge->getPercentage() - delta * quenchingGaugeDownSpeed);

	checkRepairComplete();
	checkLock();

}
void UpgradeLayer::checkRepairComplete() {
	if (hammeringBarGauge->getPercentage() >= 95 && !isUpgrade)
	{
		completeButton();
		isComplete = true;
	}
}
void UpgradeLayer::checkLock() {
	// 나중에 강화마다 값을 다르게 할거면, 매개변수에 값을 받아오는 식으로 수정하시면 됩니다.
	if (smeltingBarGauge->getPercentage() >= 70)
	{
		lock_01 = true;
		hammeringImage->setOpacity(255);
		
	}

	if (hammeringBarGauge->getPercentage() >= 70)
	{
		lock_02 = true;
		quenchingImage->setOpacity(255);
	}

}


void UpgradeLayer::gaugeIncrease(CCProgressTimer* gauge)
{
	float currentPercent = gauge->getPercentage();
	gauge->setPercentage(currentPercent + (float)8);

}


void UpgradeLayer::upgradeClicked()
{
	upgradeImage->setVisible(false);
	repairImage->setVisible(false);
	smeltingBarGauge->setVisible(true);
	smeltingTimeOutLine->setVisible(true);
	hammeringBarGauge->setVisible(true);
	hammeringTimeOutLine->setVisible(true);
	quenchingBarGauge->setVisible(true);
	quenchingTimeOutLine->setVisible(true);

}
void UpgradeLayer::repairClicked()
{
	upgradeImage->setVisible(false);
	repairImage->setVisible(false);
	hammeringBarGauge->setVisible(true);
	hammeringTimeOutLine->setVisible(true);
	
	isUpgrade = false; // 강화인지 수리인지 체크하는 변수
	lock_01 = true; // 수리의 경우 망치만 사용하므로 제한을 걸어둘 필요가 없다.
	getSword = GameData::getInstance()->getSword();
}


void UpgradeLayer::completeButton()
{
	if (!isUpgrade)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto complete_button = Sprite::create("Images/slime.png");
		complete_button->setPosition(Vec2(origin.x + visibleSize.width*0.2f, origin.y + visibleSize.height*0.5f));
		complete_button->setScale(2.0f);
		complete_button->setTag(tag_number + 6);

		this->addChild(complete_button);
	}

	// 현재 완료버튼은 수리가 완료됬을 경우에만 생성됨. 강화는 현재 미지원.
}


void UpgradeLayer::hideGauge()
{
	smeltingBarGauge->setVisible(false);
	smeltingTimeOutLine->setVisible(false);
	hammeringBarGauge->setVisible(false);
	hammeringTimeOutLine->setVisible(false);
	quenchingBarGauge->setVisible(false);
	quenchingTimeOutLine->setVisible(false);
}

bool UpgradeLayer::onTouchBegan(Touch* touch_, Event* event_)
{
	Point p = touch_->getLocation();
    // 제련, 망치, 담금질 이미지


	auto smelting = (Sprite*) this->getChildByTag(tag_number + 1);
	Rect rect3 = smelting->getBoundingBox();
	if (rect3.containsPoint(p)) {

		gaugeIncrease(smeltingBarGauge);

	}
	else {

		smelting->setScale(1);
	}

	auto hammering = (Sprite*) this->getChildByTag(tag_number + 2);
	Rect rect4 = hammering->getBoundingBox();
	if (rect4.containsPoint(p) && lock_01) {

		gaugeIncrease(hammeringBarGauge);

	}
	else {

		hammering->setScale(1);
	}

	auto quenching = (Sprite*) this->getChildByTag(tag_number + 3);
	Rect rect5 = quenching->getBoundingBox();
	if (rect5.containsPoint(p) && lock_02) {

		gaugeIncrease(quenchingBarGauge);

	}
	else {

		quenching->setScale(1);
	}

	// 강화, 수리 이미지
	auto upgrade = (Sprite*) this->getChildByTag(tag_number + 4);
	Rect rect6 = upgrade->getBoundingBox();
	if (rect6.containsPoint(p)) {

		upgradeClicked();

	}
	else {

		upgrade->setScale(1);
	}

	auto repair = (Sprite*) this->getChildByTag(tag_number + 5);
	Rect rect8 = repair->getBoundingBox();
	if (rect8.containsPoint(p)) {

		repairClicked();

	}
	else {

		repair->setScale(1);
	}

	if (isComplete) {
		auto completeButton = (Sprite*) this->getChildByTag(tag_number + 6);
		Rect rect9 = completeButton->getBoundingBox();
		if (rect9.containsPoint(p)) {
			getSword.setDurability(getSword.getMaxDurability());
			log("complete!!");
			log("%d", getSword.getDurability());
			lock_01 = false; // 초기화
			lock_02 = false;
			isUpgrade = true;
			isComplete = false;
		}

	}
	return true;

}


void UpgradeLayer::setTouchListener()
{
	// make touch listener

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(UpgradeLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(UpgradeLayer::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(UpgradeLayer::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(UpgradeLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


void UpgradeLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void UpgradeLayer::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void UpgradeLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void UpgradeLayer::keyPressed(cocos2d::EventKeyboard::KeyCode key_code_, cocos2d::Event *event_) 
{
	if (key_code_ == EventKeyboard::KeyCode::KEY_A)
	{
		gaugeIncrease(smeltingBarGauge);
	}

	if (key_code_ == EventKeyboard::KeyCode::KEY_S && lock_01)
	{
		gaugeIncrease(hammeringBarGauge);
	}

	if (key_code_ == EventKeyboard::KeyCode::KEY_D && lock_02)
	{
		gaugeIncrease(quenchingBarGauge);
	}
}
void UpgradeLayer::keyReleased(cocos2d::EventKeyboard::KeyCode key_code_, cocos2d::Event *event_)
{

}

