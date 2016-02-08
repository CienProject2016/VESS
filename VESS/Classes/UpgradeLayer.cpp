#pragma once
#include "UpgradeLayer.h"


#define tag_number 50

bool UpgradeLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	log("UpgradeLayer visibleWidthSize : %f", visibleSize.width);
	log("UpgradeLayer visibleHeightSize : %f", visibleSize.height);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	log("UpgradeLayer origin.x : %f, origin.y : %f", origin.x, origin.y);
	//사이즈 세팅


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(UpgradeLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	// 강화 샘플 이미지
	
	//키보드 입력
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(UpgradeLayer::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(UpgradeLayer::keyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto background_image = Sprite::create("Images/background_image.png");
	auto background2_image = Sprite::create("Images/background2_image.png");
	auto smith_image = Sprite::create("Images/smith_image.png");
	smelting_image = Sprite::create("Images/smelting_button.png");
	hammering_image = Sprite::create("Images/hammering_button.png");
	quenching_image = Sprite::create("Images/quenching_button.png");
	upgrade_image = Sprite::create("Images/upgrade_button.png");
	repair_image = Sprite::create("Images/repair_button.png");
	// position the sprite on the center of the screen
	background_image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	background_image->setScale(2.4f);

	background2_image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	background2_image->setScale(2.0f);

	smith_image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	smith_image->setScale(2.0f);

	smelting_image->setPosition(Vec2(origin.x + visibleSize.width * 0.12f, origin.y + visibleSize.height*0.4f));
	smelting_image->setScale(1.0f);

	hammering_image->setPosition(Vec2(origin.x + visibleSize.width * 0.22f, origin.y + visibleSize.height*0.2f));
	hammering_image->setScale(1.0f);

	quenching_image->setPosition(Vec2(origin.x + visibleSize.width * 0.32f, origin.y + visibleSize.height*0.4f));
	quenching_image->setScale(1.0f);

	upgrade_image->setPosition(Vec2(origin.x + visibleSize.width * 0.1f, origin.y + visibleSize.height*0.7f));
	upgrade_image->setScale(1.3f);

	repair_image->setPosition(Vec2(origin.x + visibleSize.width * 0.33f, origin.y + visibleSize.height*0.7f));
	repair_image->setScale(1.5f);

	smelting_image->setTag(tag_number+1);
	hammering_image->setTag(tag_number+2);
	quenching_image->setTag(tag_number+3);
	upgrade_image->setTag(tag_number+4);
	repair_image->setTag(tag_number + 5);

	//smelting bar create
	CCSprite *timer_gauge = CCSprite::create("timebar.png");
	gauge_1 = CCProgressTimer::create(timer_gauge);
	gauge_1->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.95));
	gauge_1->setPercentage(0);
	gauge_1->setMidpoint(ccp(0, 0.5));
	gauge_1->setBarChangeRate(ccp(1, 0));
	gauge_1->setType(kCCProgressTimerTypeBar);
	timeOutline1 = CCSprite::create("timeoutline.png");
	timeOutline1->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.95));
	gauge_speed_1 = 10;

	//hammering bar create
	CCSprite *timer_gauge2 = CCSprite::create("timebar.png");
	gauge_2 = CCProgressTimer::create(timer_gauge2);
	gauge_2->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.9));
	gauge_2->setPercentage(0);
	gauge_2->setMidpoint(ccp(0, 0.5));
	gauge_2->setBarChangeRate(ccp(1, 0));
	gauge_2->setType(kCCProgressTimerTypeBar);
	timeOutline2 = CCSprite::create("timeoutline.png");
	timeOutline2->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.9));
	gauge_speed_2 = 20;

	//quenching bar create
	CCSprite *timer_gauge3 = CCSprite::create("timebar.png");
	gauge_3 = CCProgressTimer::create(timer_gauge3);
	gauge_3->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.85));
	gauge_3->setPercentage(0);
	gauge_3->setMidpoint(ccp(0, 0.5));
	gauge_3->setBarChangeRate(ccp(1, 0));
	gauge_3->setType(kCCProgressTimerTypeBar);
	timeOutline3 = CCSprite::create("timeoutline.png");
	timeOutline3->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.85));
	gauge_speed_3 = 25;


	// add the sprite as a child to this layer
	this->addChild(background_image);
	this->addChild(background2_image);
	this->addChild(smith_image);
	this->addChild(smelting_image);
	this->addChild(hammering_image);
	this->addChild(quenching_image);
	this->addChild(upgrade_image);
	this->addChild(repair_image);
	this->addChild(gauge_1,2);
	this->addChild(timeOutline1);
	this->addChild(gauge_2,2);
	this->addChild(timeOutline2);
	this->addChild(gauge_3,2);
	this->addChild(timeOutline3);
	this->scheduleUpdate();
	//강화 게이지바 숨김
	hideGauge();
	//망치,담금질 비활성화 색상으로 변경
	hammering_image->setOpacity(120);
	quenching_image->setOpacity(120);
	
	
	return true;
}
void UpgradeLayer::update(float delta) {

	gauge_1->setPercentage(gauge_1->getPercentage() - delta * gauge_speed_1);
	gauge_2->setPercentage(gauge_2->getPercentage() - delta * gauge_speed_2);
	gauge_3->setPercentage(gauge_3->getPercentage() - delta * gauge_speed_3);

	checkRepairComplete();
	checkLock();

}
void UpgradeLayer::checkRepairComplete() {
	if (gauge_2->getPercentage() >= 95 && !isUpgrade)
	{
		completeButton();
		isComplete = true;
	}
}
void UpgradeLayer::checkLock() {
	// 나중에 강화마다 값을 다르게 할거면, 매개변수에 값을 받아오는 식으로 수정하시면 됩니다.
	if (gauge_1->getPercentage() >= 70)
	{
		lock_01 = true;
		hammering_image->setOpacity(255);
		
	}

	if (gauge_2->getPercentage() >= 70)
	{
		lock_02 = true;
		quenching_image->setOpacity(255);
	}

}


void UpgradeLayer::gaugeIncrease(CCProgressTimer* gauge)
{
	float currentPercent = gauge->getPercentage();
	gauge->setPercentage(currentPercent + (float)8);

}


void UpgradeLayer::upgradeClicked()
{
	upgrade_image->setVisible(false);
	repair_image->setVisible(false);
	gauge_1->setVisible(true);
	timeOutline1->setVisible(true);
	gauge_2->setVisible(true);
	timeOutline2->setVisible(true);
	gauge_3->setVisible(true);
	timeOutline3->setVisible(true);

}
void UpgradeLayer::repairClicked()
{
	upgrade_image->setVisible(false);
	repair_image->setVisible(false);
	gauge_2->setVisible(true);
	timeOutline2->setVisible(true);
	
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
	gauge_1->setVisible(false);
	timeOutline1->setVisible(false);
	gauge_2->setVisible(false);
	timeOutline2->setVisible(false);
	gauge_3->setVisible(false);
	timeOutline3->setVisible(false);
}

bool UpgradeLayer::onTouchBegan(Touch* touch_, Event* event_)
{
	Point p = touch_->getLocation();
    // 제련, 망치, 담금질 이미지


	auto smelting = (Sprite*) this->getChildByTag(tag_number + 1);
	Rect rect3 = smelting->getBoundingBox();
	if (rect3.containsPoint(p)) {

		gaugeIncrease(gauge_1);

	}
	else {

		smelting->setScale(1);
	}

	auto hammering = (Sprite*) this->getChildByTag(tag_number + 2);
	Rect rect4 = hammering->getBoundingBox();
	if (rect4.containsPoint(p) && lock_01) {

		gaugeIncrease(gauge_2);

	}
	else {

		hammering->setScale(1);
	}

	auto quenching = (Sprite*) this->getChildByTag(tag_number + 3);
	Rect rect5 = quenching->getBoundingBox();
	if (rect5.containsPoint(p) && lock_02) {

		gaugeIncrease(gauge_3);

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
		gaugeIncrease(gauge_1);
	}

	if (key_code_ == EventKeyboard::KeyCode::KEY_S && lock_01)
	{
		gaugeIncrease(gauge_2);
	}

	if (key_code_ == EventKeyboard::KeyCode::KEY_D && lock_02)
	{
		gaugeIncrease(gauge_3);
	}
}
void UpgradeLayer::keyReleased(cocos2d::EventKeyboard::KeyCode key_code_, cocos2d::Event *event_)
{

}

