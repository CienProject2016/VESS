#pragma once
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
	log("UpgradeLayer visibleWidthSize : %f", visibleSize.width);
	log("UpgradeLayer visibleHeightSize : %f", visibleSize.height);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	log("UpgradeLayer origin.x : %f, origin.y : %f", origin.x, origin.y);


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(UpgradeLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto upgrade_image = Sprite::create("Images/upgrade_button.png");
	auto repair_image = Sprite::create("Images/repair_button.png");


	auto background_image = Sprite::create("Images/background_image.png");
	auto background2_image = Sprite::create("Images/background2_image.png");
	auto smith_image = Sprite::create("Images/smith_image.png");
	
	auto smelting_image = Sprite::create("Images/smelting_button.png");
	auto hammering_image = Sprite::create("Images/hammering_button.png");
	auto quenching_image = Sprite::create("Images/quenching_button.png");
	
	// position the sprite on the center of the screen
	background_image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	background_image->setScale(2.4f);

	background2_image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	background2_image->setScale(2.0f);

	smith_image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	smith_image->setScale(2.0f);

	

	smelting_image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.2f));
	smelting_image->setScale(1.0f);

	hammering_image->setPosition(Vec2(origin.x + visibleSize.width * 0.1f, origin.y + visibleSize.height*0.4f));
	hammering_image->setScale(1.0f);
	quenching_image->setPosition(Vec2(origin.x + visibleSize.width * 0.3f, origin.y + visibleSize.height*0.4f));
	quenching_image->setScale(1.0f);
	upgrade_image->setPosition(Vec2(origin.x + visibleSize.width * 0.15f, origin.y + visibleSize.height*0.9f));
	upgrade_image->setScale(1.3f);
	repair_image->setPosition(Vec2(origin.x + visibleSize.width * 0.33f, origin.y + visibleSize.height*0.9f));
	repair_image->setScale(1.5f);

	smelting_image->setTag(tag_number+4);
	hammering_image->setTag(tag_number+5);
	quenching_image->setTag(tag_number+6);
	upgrade_image->setTag(tag_number+7);
	repair_image->setTag(tag_number+8);
	
	// add the sprite as a child to this layer
	this->addChild(background_image);
	this->addChild(background2_image);
	this->addChild(smith_image);
	
	this->addChild(smelting_image);
	this->addChild(hammering_image);
	this->addChild(quenching_image);
	this->addChild(upgrade_image);
	this->addChild(repair_image);
	

	int upgradeGold = GameData::getInstance()->getNeededUpgradeGold();
	auto touchLabel1 = Label::createWithTTF("골드", "fonts/arial.ttf", 50);
	touchLabel1->setString(StringUtils::format("%d%s", upgradeGold, gold));
	// position the label on the center of the screen
	touchLabel1->setPosition(Vec2(Vec2(origin.x + visibleSize.width * 0.15f, origin.y + visibleSize.height*0.8f)));
	touchLabel1->setColor(ccc3(250, 250, 250)); 
	this->addChild(touchLabel1, 1);

	int repairGold = GameData::getInstance()->getNeededRepairGold();
	auto touchLabel2 = Label::createWithTTF("골드", "fonts/arial.ttf", 50);
	touchLabel2->setString(StringUtils::format("%d%s", repairGold, gold));
	// position the label on the center of the screen
	touchLabel2->setPosition(Vec2(origin.x + visibleSize.width * 0.33f, origin.y + visibleSize.height*0.8f));
	touchLabel2->setColor(ccc3(250, 250, 250)); 

	this->addChild(touchLabel2, 2);

	int Gold = GameData::getInstance()->getGold();
	auto touchLabel3 = Label::createWithTTF("", "fonts/arial.ttf", 50);
	touchLabel3->setString(StringUtils::format("%d%s", Gold,gold));
	// position the label on the center of the screen
	touchLabel3->setPosition(Vec2(origin.x + visibleSize.width * 0.9f, origin.y + visibleSize.height*0.9f));
	touchLabel3->setColor(ccc3(0, 0, 0)); //black	

	this->addChild(touchLabel3, 3);

	//setTouchListener();
	return true;
}

bool UpgradeLayer::onTouchBegan(Touch* touch_, Event* event_)
{

	// 0, 1, 2, 3  슬롯
	Point p = touch_->getLocation();



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

