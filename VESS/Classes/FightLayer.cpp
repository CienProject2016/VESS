#pragma once
#include "FightLayer.h"

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
	auto enemyImage = Sprite::create("Images/slime.png");

	// position the sprite on the center of the screen	
	daughterImage->setPosition(Vec2(origin.x, origin.y + visibleSize.height*0.5f));
	daughterImage->setScale(1.0f);
	//daughterImage->setAnchorPoint(ccp(0, 0.5f));
	
	enemyImage->setPosition(Vec2(origin.x + visibleSize.width*0.5f, origin.y + visibleSize.height*0.5f));
	enemyImage->setScale(4.0f);
	enemyImage->setVisible(true);

	// add the sprite as a child to this layer
	this->addChild(daughterImage, 0);
	this->addChild(enemyImage, 1);

	
	auto enemyMove = MoveTo::create(4, ccp(origin.x, origin.y + visibleSize.height*0.5f));
	auto enemyRelocate = MoveTo::create(0, ccp(origin.x + visibleSize.width*0.5f, origin.y + visibleSize.height*0.5f));

	auto seq = CCSequence::create(enemyMove, CCDelayTime::create(2), enemyRelocate, CCDelayTime::create(2), NULL);
	auto rep = CCRepeatForever::create(seq); //무한반복
	enemyImage->runAction(rep);

	
	
}
