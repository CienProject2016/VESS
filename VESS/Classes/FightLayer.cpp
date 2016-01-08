#pragma once
#include "FightLayer.h"

bool FightLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	// ���� ���� �̹���
	auto sprite = Sprite::create("Images/daughter.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setScale(0.5f);

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
}