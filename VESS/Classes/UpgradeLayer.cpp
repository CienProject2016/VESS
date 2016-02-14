#pragma once
#include "UpgradeLayer.h"
#include "GameData.h"
#include "UpgradeController.h"
#include "Resources.h"

bool UpgradeLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	currentUpgradePhase = NONE;
	completeButtonPhase = CANNOT_CLICK;
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

	smeltingImage->setTag(ZOrder::SMELTING_IMAGE);
	hammeringImage->setTag(ZOrder::HAMMERING_IMAGE);
	quenchingImage->setTag(ZOrder::QUENCHING_IMAGE);
	upgradeImage->setTag(ZOrder::UPGRADE_IMAGE);
	repairImage->setTag(ZOrder::REPAIR_IMAGE);

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

	upgradeGold = GameData::getInstance()->getNeededUpgradeGold();
	auto upgradeLabel = Label::createWithTTF("강화골드", "fonts/arial.ttf", 50);
	upgradeLabel->setString(StringUtils::format("%d%s", upgradeGold, "GOLD"));
	// position the label on the center of the screen
	upgradeLabel->setPosition(Vec2(Vec2(origin.x + visibleSize.width * 0.11f, origin.y + visibleSize.height*0.86f)));
	upgradeLabel->setColor(ccc3(250, 250, 250)); 
	this->addChild(upgradeLabel, 1);

	auto gateImage = Sprite::create(ImageResources::DIMENSION_GATE_BUTTON_PATH);
	gateImage->setPosition(Vec2(visibleSize.width * 0.35f, visibleSize.height * 0.6f));
	this->addChild(gateImage, 55);

	//업그레이드 레이어는 ItemMode의 반대 이미지를 보여줌
	if (GameData::getInstance()->getItemMode() == GameData::ItemMode::SWORD) {
		itemImage = Sprite::create("Images/shield.png");
		itemName = Label::createWithSystemFont("방패 이름", "Arial", 50);
	}
	else {
		itemImage = Sprite::create("Images/sword.png");
		itemName = Label::createWithSystemFont("칼 이름", "Arial", 50);
	}
	itemImage->setPosition(Vec2(visibleSize.width * 0.35f, visibleSize.height * 0.6f));
	itemImage->setName("itemImage");
	itemName->setPosition(Vec2(origin.x+ visibleSize.width*0.35f, origin.x + visibleSize.height * 0.7f));
	itemName->setVisible(true);

	this->addChild(itemImage,56);
	this->addChild(itemName,58);

	repairGold = GameData::getInstance()->getNeededRepairGold();
	auto repairLabel = Label::createWithTTF("수리골드", "fonts/arial.ttf", 50);
	repairLabel->setString(StringUtils::format("%d%s", repairGold, "GOLD"));
	repairLabel->setPosition(Vec2(origin.x + visibleSize.width * 0.33f, origin.y + visibleSize.height*0.86f));
	repairLabel->setColor(ccc3(250, 250, 250)); 
	this->addChild(repairLabel, 2);

	completeUpgradeButton = Sprite::create("Images/upgrade_before_complete.png");
	completeUpgradeButton->setPosition(Vec2(visibleSize.width * 0.22f, visibleSize.height *7/10));
	completeUpgradeButton->setTag(ZOrder::COMPLETE_UPGRADE_BUTTON);
	this->addChild(completeUpgradeButton);
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
	hideBeforeUpgradeResources();
	//망치,담금질 비활성화 색상으로 변경
	hammeringImage->setOpacity(120);
	quenchingImage->setOpacity(120);
	
	return true;
}


void UpgradeLayer::update(float delta) {

	smeltingBarGauge->setPercentage(smeltingBarGauge->getPercentage() - delta * smeltingGaugeDownSpeed);
	hammeringBarGauge->setPercentage(hammeringBarGauge->getPercentage() - delta * hammeringGaugeDownSpeed);
	quenchingBarGauge->setPercentage(quenchingBarGauge->getPercentage() - delta * quenchingGaugeDownSpeed);

	checkComplete();
	checkLock();

	if (GameData::getInstance()->getItemMode() == GameData::ItemMode::SWORD) {
		itemImage->setTexture("Images/shield.png");
		itemName->setString(GameData::getInstance()->getShield().getName());
	}
	else {
		itemImage->setTexture("Images/sword.png");
		itemName->setString(StringUtils::format("%s", GameData::getInstance()->getSword().getName().c_str()));
	}
}

void UpgradeLayer::checkComplete() {
	switch (currentUpgradePhase) {
	case UpgradePhase::UPGRADE:
		if (quenchingBarGauge->getPercentage() >= 70)
		{
			showCompleteButton();
			completeButtonPhase = CompleteButtonPhase::CAN_CLICK;
		}
		break;
	case UpgradePhase::REPAIR:
		if (hammeringBarGauge->getPercentage() >= 95)
		{
			showCompleteButton();
			completeButtonPhase = CompleteButtonPhase::CAN_CLICK;
		}
		break;
	case UpgradePhase::NONE:
		//Nothing To Do
		break;
	}
}

void UpgradeLayer::checkLock() {
	// 나중에 강화마다 값을 다르게 할거면, 매개변수에 값을 받아오는 식으로 수정하시면 됩니다.
	if (smeltingBarGauge->getPercentage() >= 70){
		lockBeforeHammering = true;
		hammeringImage->setOpacity(255);
	}

	if (hammeringBarGauge->getPercentage() >= 70){
		lockBeforeQuenching = true;
		quenchingImage->setOpacity(255);
	}
}


void UpgradeLayer::increaseGauge(CCProgressTimer* gauge)
{
	float currentPercent = gauge->getPercentage();
	gauge->setPercentage(currentPercent + (float)8);
}

void UpgradeLayer::showUiButton(UpgradePhase upgradePhase) {
	if (upgradePhase == UpgradePhase::NONE) {
		completeUpgradeButton->setVisible(false);
		upgradeImage->setVisible(true);
		repairImage->setVisible(true);
		smeltingBarGauge->setVisible(false);
		smeltingTimeOutLine->setVisible(false);
		hammeringBarGauge->setVisible(false);
		hammeringTimeOutLine->setVisible(false);
		quenchingBarGauge->setVisible(false);
		quenchingTimeOutLine->setVisible(false);
	}
	else {
		completeUpgradeButton->setVisible(true);
		upgradeImage->setVisible(false);
		repairImage->setVisible(false);
		smeltingBarGauge->setVisible(true);
		smeltingTimeOutLine->setVisible(true);
		hammeringBarGauge->setVisible(true);
		hammeringTimeOutLine->setVisible(true);
		quenchingBarGauge->setVisible(true);
		quenchingTimeOutLine->setVisible(true);
	}
}


void UpgradeLayer::upgradeClicked()
{
	currentUpgradePhase = UpgradePhase::UPGRADE;
	log("Upgrade Phase");
	Sword* sword = &GameData::getInstance()->getSword();
	if (sword->isInUse()) {
		//소드는 딸이 사용중이므로 방패강화
		if (UpgradeController::payUpgradeCosts(upgradeGold, Item::SHIELD) == true) {
			showUiButton(currentUpgradePhase);
		}
		else {
			//돈이 없어 강화를 할 수 없는 경우
		}
	}
	else {
		if (UpgradeController::payUpgradeCosts(upgradeGold, Item::SWORD) == true) {
			showUiButton(currentUpgradePhase);
		}
		else {
			//돈이 없어 강화를 할 수 없는 경우
		}
	}
	

}
void UpgradeLayer::repairClicked()
{
	upgradeImage->setVisible(false);
	repairImage->setVisible(false);
	hammeringBarGauge->setVisible(true);
	hammeringTimeOutLine->setVisible(true);
	
	currentUpgradePhase = UpgradePhase::REPAIR; // 강화인지 수리인지 체크하는 변수
	lockBeforeHammering = true; // 수리의 경우 망치만 사용하므로 제한을 걸어둘 필요가 없다.
	getSword = GameData::getInstance()->getSword();
}


void UpgradeLayer::showCompleteButton()
{
	if (currentUpgradePhase == REPAIR)	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		completeUpgradeButton->setTexture("Images/upgrade_after_complete.png"); //TODO 바꿔야됨
	}
	else if (currentUpgradePhase == UPGRADE) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		completeUpgradeButton->setTexture("Images/upgrade_after_complete.png");		
	}
}


void UpgradeLayer::hideBeforeUpgradeResources()
{
	completeUpgradeButton->setVisible(false);
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

	auto smeltingButton = (Sprite*) this->getChildByTag(ZOrder::SMELTING_IMAGE);
	Rect smeltingTouchRect = smeltingButton->getBoundingBox();
	if (smeltingTouchRect.containsPoint(p)) {
		increaseGauge(smeltingBarGauge);
	}

	auto hammeringButton = (Sprite*) this->getChildByTag(ZOrder::HAMMERING_IMAGE);
	
	Rect hammeringTouchRect = hammeringButton->getBoundingBox();
	if (hammeringTouchRect.containsPoint(p) && lockBeforeHammering) {
		increaseGauge(hammeringBarGauge);
	}

	auto quenchingButton = (Sprite*) this->getChildByTag(ZOrder::QUENCHING_IMAGE);
	Rect quenchingTouchRect = quenchingButton->getBoundingBox();
	if (quenchingTouchRect.containsPoint(p) && lockBeforeQuenching) {
		increaseGauge(quenchingBarGauge);
	}

	// 강화, 수리 이미지
	auto upgradeButton = (Sprite*) this->getChildByTag(ZOrder::UPGRADE_IMAGE);
	Rect upgradeTouchRect = upgradeButton->getBoundingBox();
	if (upgradeTouchRect.containsPoint(p)) {
		upgradeClicked();
	}

	auto repairButton = (Sprite*) this->getChildByTag(ZOrder::REPAIR_IMAGE);
	Rect repairTouchRect = repairButton->getBoundingBox();
	if (repairTouchRect.containsPoint(p)) {
		repairClicked();
	}

	if (completeButtonPhase == CAN_CLICK) {
		auto completeUpgradeButton = (Sprite*) this->getChildByTag(ZOrder::COMPLETE_UPGRADE_BUTTON);
		Rect completeUpgradeTouchRect = completeUpgradeButton->getBoundingBox();
		if (completeUpgradeTouchRect.containsPoint(p)) {
			completeClicked();
		}		
	}
	return true;
}

void UpgradeLayer::completeClicked() {
	lockBeforeHammering = false; // 초기화
	lockBeforeQuenching = false;
	isComplete = false;
	log("complete!!");
	switch (currentUpgradePhase) {
	case UpgradePhase::UPGRADE:
		UpgradeController::upgradeItem();
		break;
	case UpgradePhase::REPAIR:		
		getSword.setDurability(getSword.getMaxDurability());
		log("%d", getSword.getDurability());
		break;
	}

	currentUpgradePhase = UpgradePhase::NONE;
	showUiButton(currentUpgradePhase);
	hideBeforeUpgradeResources();
	hammeringImage->setOpacity(120);
	quenchingImage->setOpacity(120);
	completeButtonPhase = CompleteButtonPhase::CANNOT_CLICK;
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
		increaseGauge(smeltingBarGauge);
	}

	if (key_code_ == EventKeyboard::KeyCode::KEY_S && lockBeforeHammering)
	{
		increaseGauge(hammeringBarGauge);
	}

	if (key_code_ == EventKeyboard::KeyCode::KEY_D && lockBeforeQuenching)
	{
		increaseGauge(quenchingBarGauge);
	}
}
void UpgradeLayer::keyReleased(cocos2d::EventKeyboard::KeyCode key_code_, cocos2d::Event *event_)
{

}

