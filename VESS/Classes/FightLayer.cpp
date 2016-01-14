#pragma once
#include "FightLayer.h"
#include "Monster.h"

#define Print 2000

bool FightLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	log("fightLayer visibleWidthSize : %f", visibleSize.width);
	log("fightLayer visibleHeightSize : %f", visibleSize.height);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	log("fightLayer origin.x : %f, origin.y : %f", origin.x, origin.y);


	// 전투 샘플 이미지
	auto daughterImage = Sprite::create("Images/daughter.png");
	// position the sprite on the center of the screen	
	daughterImage->setPosition(Vec2(origin.x, origin.y + visibleSize.height*0.5f));
	daughterImage->setScale(1.0f);
	//daughterImage->setAnchorPoint(ccp(0, 0.5f));

	Monster* enemyImage = Monster::create("slime");

	//공격버튼
	auto attack_Button = MenuItemImage::create("Images/AttackButton.png","Images/AttackButton.png", "Images/DisabledButton.png", CC_CALLBACK_1(FightLayer::attackCallback, this));
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
	
	
	// add the sprite as a child to this layer
	this->addChild(daughterImage, 0);
	this->addChild(enemyImage, 1);
	this->addChild(battle_Menu, 2);
	this->addChild(attackMessage, 3);
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
