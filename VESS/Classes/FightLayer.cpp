#pragma once
#include "FightLayer.h"
#include "Monster.h"

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
	// add the sprite as a child to this layer
	this->addChild(daughterImage, 0);
	this->addChild(enemyImage, 1);
}
