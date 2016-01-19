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
	

	
	auto smith_image = Sprite::create("Images/smith_image.png");
	auto fire_image = Sprite::create("Images/fire_button.png");
	auto grass_image = Sprite::create("Images/grass_button.png");
	auto water_image = Sprite::create("Images/water_button.png");
	auto smelting_image = Sprite::create("Images/smelting_button.png");
	auto hammering_image = Sprite::create("Images/hammering_button.png");
	auto quenching_image = Sprite::create("Images/quenching_button.png");
	auto list_image = Sprite::create("Images/list_button.png");
	auto upgrade_image = Sprite::create("Images/upgrade_button.png");
	auto repair_image = Sprite::create("images/repair_button.png");
	// position the sprite on the center of the screen
	smith_image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	smith_image->setScale(1.0f);

	fire_image->setPosition(Vec2(origin.x + visibleSize.width * 0.1f, origin.y + visibleSize.height*0.6f));
	fire_image->setScale(1.0f);

	grass_image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.7f));
	grass_image->setScale(1.0f);

	water_image->setPosition(Vec2(origin.x + visibleSize.width * 0.3f, origin.y + visibleSize.height*0.6f));
	water_image->setScale(1.0f);

	smelting_image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.2f));
	smelting_image->setScale(1.0f);

	hammering_image->setPosition(Vec2(origin.x + visibleSize.width * 0.1f, origin.y + visibleSize.height*0.4f));
	hammering_image->setScale(1.0f);

	quenching_image->setPosition(Vec2(origin.x + visibleSize.width * 0.3f, origin.y + visibleSize.height*0.4f));
	quenching_image->setScale(1.0f);

	list_image->setPosition(Vec2(origin.x + visibleSize.width * 0.35f, origin.y + visibleSize.height*0.8f));
	list_image->setScale(1.0f);

	upgrade_image->setPosition(Vec2(origin.x + visibleSize.width * 0.05f, origin.y + visibleSize.height*0.8f));
	upgrade_image->setScale(1.0f);

	repair_image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.8f));
	repair_image->setScale(1.0f);


	fire_image->setTag(tag_number);
	grass_image->setTag(tag_number+1);
	water_image->setTag(tag_number+2);
	smelting_image->setTag(tag_number+3);
	hammering_image->setTag(tag_number+4);
	quenching_image->setTag(tag_number+5);
	list_image->setTag(tag_number+6);
	upgrade_image->setTag(tag_number+7);
	repair_image->setTag(tag_number + 8);
	// add the sprite as a child to this layer
	this->addChild(smith_image);
	this->addChild(fire_image);
	this->addChild(grass_image);
	this->addChild(water_image);
	this->addChild(smelting_image);
	this->addChild(hammering_image);
	this->addChild(quenching_image);
	this->addChild(list_image);
	this->addChild(upgrade_image);
	this->addChild(repair_image);


	
	// 불속성 이미지

	//if (location_ != NULL) {
	//CCRect rect = CCRectMake(0, 0, grass_image->getContentSize().width, grass_image->getContentSize().height);
	//if (rect.containsPoint(location_)) {
	//	log("grass");
	//	}
	//}

	//setTouchListener();
	return true;
}

bool UpgradeLayer::onTouchBegan(Touch* touch_, Event* event_)
{

	// 0, 1, 2  속성이미지
	Point p = touch_->getLocation();
	auto fire_image = (Sprite*) this->getChildByTag(tag_number);
	Rect rect = fire_image->getBoundingBox();
	if (rect.containsPoint(p)) {

		fire_image->setScale(2.0);

	}
	else {

		fire_image->setScale(1);
	}

	auto grass_image = (Sprite*) this->getChildByTag(tag_number+1);
	Rect rect1 = grass_image->getBoundingBox();
	if (rect1.containsPoint(p)) {

		grass_image->setScale(2.0);

	}
	else {

		grass_image->setScale(1);
	}

	auto water_image = (Sprite*) this->getChildByTag(tag_number + 2);
	Rect rect2 = water_image->getBoundingBox();
	if (rect2.containsPoint(p)) {

		water_image->setScale(2.0);

	}
	else {

		water_image->setScale(1);
	}


	// 3, 4, 5  강화이미지
	auto smelting = (Sprite*) this->getChildByTag(tag_number + 3);
	Rect rect3 = smelting->getBoundingBox();
	if (rect3.containsPoint(p)) {

		smelting->setScale(2.0);

	}
	else {

		smelting->setScale(1);
	}

	auto hammering = (Sprite*) this->getChildByTag(tag_number + 4);
	Rect rect4 = hammering->getBoundingBox();
	if (rect4.containsPoint(p)) {

		hammering->setScale(2.0);

	}
	else {

		hammering->setScale(1);
	}

	auto quenching = (Sprite*) this->getChildByTag(tag_number + 5);
	Rect rect5 = quenching->getBoundingBox();
	if (rect5.containsPoint(p)) {

		quenching->setScale(2.0);

	}
	else {

		quenching->setScale(1);
	}

	//6, 7, 8 강화,도감,수리
	auto upgrade = (Sprite*) this->getChildByTag(tag_number + 6);
	Rect rect6 = upgrade->getBoundingBox();
	if (rect6.containsPoint(p)) {

		upgrade->setScale(2.0);

	}
	else {

		upgrade->setScale(1);
	}

	auto list = (Sprite*) this->getChildByTag(tag_number + 7);
	Rect rect7 = list->getBoundingBox();
	if (rect7.containsPoint(p)) {

		list->setScale(2.0);

	}
	else {

		list->setScale(1);
	}

	auto repair = (Sprite*) this->getChildByTag(tag_number + 8);
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

