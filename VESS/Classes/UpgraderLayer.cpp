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
	

	auto background_image = Sprite::create("images/background_image.png");
	auto background2_image = Sprite::create("images/background2_image.png");
	auto smith_image = Sprite::create("Images/smith_image.png");
	auto ingredient_slot = Sprite::create("Images/ingredient_slot.png");
	auto ingredient2_slot = Sprite::create("Images/ingredient_slot.png");
	auto jewel_slot = Sprite::create("Images/jewel_slot.png");
	auto inventory_slot = Sprite::create("Images/inventory_slot.png");
	auto smelting_image = Sprite::create("Images/smelting_button.png");
	auto hammering_image = Sprite::create("Images/hammering_button.png");
	auto quenching_image = Sprite::create("Images/quenching_button.png");
	auto list_image = Sprite::create("Images/list_button.png");
	auto upgrade_image = Sprite::create("Images/upgrade_button.png");
	auto repair_image = Sprite::create("images/repair_button.png");
	// position the sprite on the center of the screen
	background_image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	background_image->setScale(2.0f);

	background2_image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	background2_image->setScale(2.0f);

	smith_image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	smith_image->setScale(2.0f);

	ingredient_slot->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.1f));
	ingredient_slot->setScale(1.0f);

	ingredient2_slot->setPosition(Vec2(origin.x + visibleSize.width * 0.26f, origin.y + visibleSize.height*0.1f));
	ingredient2_slot->setScale(1.0f);

	jewel_slot->setPosition(Vec2(origin.x + visibleSize.width * 0.32f, origin.y + visibleSize.height*0.1f));
	jewel_slot->setScale(1.0f);

	inventory_slot->setPosition(Vec2(origin.x + visibleSize.width * 0.05f, origin.y + visibleSize.height*0.4f));
	inventory_slot->setScale(1.0f);

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


	ingredient_slot->setTag(tag_number);
	ingredient2_slot->setTag(tag_number+1);
	jewel_slot->setTag(tag_number+2);
	inventory_slot->setTag(tag_number+3);
	smelting_image->setTag(tag_number+4);
	hammering_image->setTag(tag_number+5);
	quenching_image->setTag(tag_number+6);
	list_image->setTag(tag_number+7);
	upgrade_image->setTag(tag_number+8);
	repair_image->setTag(tag_number + 9);
	// add the sprite as a child to this layer
	this->addChild(background_image);
	this->addChild(background2_image);
	this->addChild(smith_image);
	this->addChild(ingredient_slot);
	this->addChild(ingredient2_slot);
	this->addChild(jewel_slot);
	this->addChild(inventory_slot);
	this->addChild(smelting_image);
	this->addChild(hammering_image);
	this->addChild(quenching_image);
	this->addChild(list_image);
	this->addChild(upgrade_image);
	this->addChild(repair_image);


	
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

bool UpgradeLayer::onTouchBegan(Touch* touch_, Event* event_)
{

	// 0, 1, 2, 3  슬롯
	Point p = touch_->getLocation();
	auto ingredient_slot = (Sprite*) this->getChildByTag(tag_number);
	Rect rect = ingredient_slot->getBoundingBox();
	if (rect.containsPoint(p)) {

		ingredient_slot->setScale(2.0);

	}
	else {

		ingredient_slot->setScale(1);
	}

	auto ingredient2_slot = (Sprite*) this->getChildByTag(tag_number+1);
	Rect rect9 = ingredient2_slot->getBoundingBox();
	if (rect9.containsPoint(p)) {

		ingredient2_slot->setScale(2.0);

	}
	else {

		ingredient2_slot->setScale(1);
	}

	auto jewel_slot = (Sprite*) this->getChildByTag(tag_number+2);
	Rect rect1 = jewel_slot->getBoundingBox();
	if (rect1.containsPoint(p)) {

		jewel_slot->setScale(2.0);

	}
	else {

		jewel_slot->setScale(1);
	}

	auto inventory_slot = (Sprite*) this->getChildByTag(tag_number + 3);
	Rect rect2 = inventory_slot->getBoundingBox();
	if (rect2.containsPoint(p)) {

		inventory_slot->setScale(2.0);

	}
	else {

		inventory_slot->setScale(1);
	}


	// 4, 5, 6  강화이미지
	auto smelting = (Sprite*) this->getChildByTag(tag_number + 4);
	Rect rect3 = smelting->getBoundingBox();
	if (rect3.containsPoint(p)) {

		smelting->setScale(2.0);

	}
	else {

		smelting->setScale(1);
	}

	auto hammering = (Sprite*) this->getChildByTag(tag_number + 5);
	Rect rect4 = hammering->getBoundingBox();
	if (rect4.containsPoint(p)) {

		hammering->setScale(2.0);

	}
	else {

		hammering->setScale(1);
	}

	auto quenching = (Sprite*) this->getChildByTag(tag_number + 6);
	Rect rect5 = quenching->getBoundingBox();
	if (rect5.containsPoint(p)) {

		quenching->setScale(2.0);

	}
	else {

		quenching->setScale(1);
	}

	// 7, 8, 9 강화,도감,수리
	auto upgrade = (Sprite*) this->getChildByTag(tag_number + 7);
	Rect rect6 = upgrade->getBoundingBox();
	if (rect6.containsPoint(p)) {

		upgrade->setScale(2.0);

	}
	else {

		upgrade->setScale(1);
	}

	auto list = (Sprite*) this->getChildByTag(tag_number + 8);
	Rect rect7 = list->getBoundingBox();
	if (rect7.containsPoint(p)) {

		list->setScale(2.0);

	}
	else {

		list->setScale(1);
	}

	auto repair = (Sprite*) this->getChildByTag(tag_number + 9);
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

