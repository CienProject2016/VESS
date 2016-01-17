#pragma once
#include "UpgradeLayer.h"

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
	auto shop_image = Sprite::create("Images/shop_button.png");
	auto upgrade_image = Sprite::create("Images/upgrade_button.png");
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

	shop_image->setPosition(Vec2(origin.x + visibleSize.width * 0.35f, origin.y + visibleSize.height*0.8f));
	shop_image->setScale(1.0f);

	upgrade_image->setPosition(Vec2(origin.x + visibleSize.width * 0.05f, origin.y + visibleSize.height*0.8f));
	upgrade_image->setScale(1.0f);
	// add the sprite as a child to this layer
	this->addChild(smith_image);
	this->addChild(fire_image);
	this->addChild(grass_image);
	this->addChild(water_image);
	this->addChild(smelting_image);
	this->addChild(hammering_image);
	this->addChild(quenching_image);
	this->addChild(shop_image);
	this->addChild(upgrade_image);
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
	Vec2 location = touch_->getLocation();
	Sprite* spr = (Sprite*) this->getChildByTag(1);
	Rect rect = spr->getBoundingBox();

	if (rect.containsPoint(location)) {

		spr->setScale(2.0);

	}
	else {

		spr->setScale(1);
	}

	return true;
}


//void UpgradeLayer::setTouchListener()
//{
//	// make touch listener
//
//	auto listener = EventListenerTouchOneByOne::create();
//	listener->onTouchBegan = CC_CALLBACK_2(UpgradeLayer::onTouchBegan, this);
//	listener->onTouchMoved = CC_CALLBACK_2(UpgradeLayer::onTouchMoved, this);
//	listener->onTouchCancelled = CC_CALLBACK_2(UpgradeLayer::onTouchCancelled, this);
//	listener->onTouchEnded = CC_CALLBACK_2(UpgradeLayer::onTouchEnded, this);
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//}
//
//bool UpgradeLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
//{
//	
//	return true;
//}
//
//void UpgradeLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
//{
//
//}
//
//void UpgradeLayer::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
//{
//
//}
//
//void UpgradeLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
//{
//	auto target = this->getChildByName("grass_image");
//	if (target == NULL) 
//	{
//		log("fxxk");
//	}else if (target->boundingBox().containsPoint(touch->getLocation()))
//	{
//		log("grasssssss");
//	}
//}

