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



	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(UpgradeLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	// 강화 샘플 이미지
	

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
	CCSprite *timer_gaze = CCSprite::create("timebar.png");
	gazing1 = CCProgressTimer::create(timer_gaze);
	gazing1->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.95));
	gazing1->setPercentage(0);
	gazing1->setMidpoint(ccp(0, 0.5));
	gazing1->setBarChangeRate(ccp(1, 0));
	gazing1->setType(kCCProgressTimerTypeBar);
	timeOutline1 = CCSprite::create("timeoutline.png");
	timeOutline1->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.95));
	gazingSpeed1 = 10;
	//hammering bar create
	CCSprite *timer_gaze2 = CCSprite::create("timebar.png");
	gazing2 = CCProgressTimer::create(timer_gaze2);
	gazing2->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.9));
	gazing2->setPercentage(0);
	gazing2->setMidpoint(ccp(0, 0.5));
	gazing2->setBarChangeRate(ccp(1, 0));
	gazing2->setType(kCCProgressTimerTypeBar);
	timeOutline2 = CCSprite::create("timeoutline.png");
	timeOutline2->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.9));
	gazingSpeed2 = 20;
	//quenching bar create
	CCSprite *timer_gaze3 = CCSprite::create("timebar.png");
	gazing3 = CCProgressTimer::create(timer_gaze3);
	gazing3->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.85));
	gazing3->setPercentage(0);
	gazing3->setMidpoint(ccp(0, 0.5));
	gazing3->setBarChangeRate(ccp(1, 0));
	gazing3->setType(kCCProgressTimerTypeBar);
	timeOutline3 = CCSprite::create("timeoutline.png");
	timeOutline3->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.85));
	gazingSpeed3 = 25;
	// add the sprite as a child to this layer
	this->addChild(background_image);
	this->addChild(background2_image);
	this->addChild(smith_image);
	this->addChild(smelting_image);
	this->addChild(hammering_image);
	this->addChild(quenching_image);
	this->addChild(upgrade_image);
	this->addChild(repair_image);
	this->addChild(gazing1);
	this->addChild(timeOutline1);
	this->addChild(gazing2);
	this->addChild(timeOutline2);
	this->addChild(gazing3);
	this->addChild(timeOutline3);
	this->scheduleUpdate();
	//강화 게이지바 숨김
	hideGaze();
	


	
	// 불속성 이미지

	//if (location_ != NULL) {
	//CCRect rect = CCRectMake(0, 0, jewel_slot->getContentSize().width, jewel_slot->getContentSize().height);
	//if (rect.containsPoint(location_)) {
	//	log("grass");
	//	}
	//}

	//setTouchListener();
	return true;
}
void UpgradeLayer::update(float delta) {

	gazing1->setPercentage(gazing1->getPercentage() - delta * gazingSpeed1);
	gazing2->setPercentage(gazing2->getPercentage() - delta * gazingSpeed2);
	gazing3->setPercentage(gazing3->getPercentage() - delta * gazingSpeed3);


}
void UpgradeLayer::gazeIncrease(CCProgressTimer* gazing)
{
	float currentPercent = gazing->getPercentage();
	gazing->setPercentage(currentPercent + (float)8);

}
void UpgradeLayer::upgradeClicked()
{
	upgrade_image->setVisible(false);
	repair_image->setVisible(false);
	gazing1->setVisible(true);
	timeOutline1->setVisible(true);
	gazing2->setVisible(true);
	timeOutline2->setVisible(true);
	gazing3->setVisible(true);
	timeOutline3->setVisible(true);

}
void UpgradeLayer::hideGaze()
{
	gazing1->setVisible(false);
	timeOutline1->setVisible(false);
	gazing2->setVisible(false);
	timeOutline2->setVisible(false);
	gazing3->setVisible(false);
	timeOutline3->setVisible(false);
}

bool UpgradeLayer::onTouchBegan(Touch* touch_, Event* event_)
{
	Point p = touch_->getLocation();
    // 제련, 망치, 담금질 이미지
	auto smelting = (Sprite*) this->getChildByTag(tag_number + 1);
	Rect rect3 = smelting->getBoundingBox();
	if (rect3.containsPoint(p)) {

		gazeIncrease(gazing1);

	}
	else {

		smelting->setScale(1);
	}

	auto hammering = (Sprite*) this->getChildByTag(tag_number + 2);
	Rect rect4 = hammering->getBoundingBox();
	if (rect4.containsPoint(p)) {

		gazeIncrease(gazing2);

	}
	else {

		hammering->setScale(1);
	}

	auto quenching = (Sprite*) this->getChildByTag(tag_number + 3);
	Rect rect5 = quenching->getBoundingBox();
	if (rect5.containsPoint(p)) {

		gazeIncrease(gazing3);

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

		repair->setScale(2.0);

	}
	else {

		repair->setScale(1);
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

