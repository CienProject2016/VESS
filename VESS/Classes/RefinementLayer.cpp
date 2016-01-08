#pragma once
#include "RefinementLayer.h"

bool RefinementLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	// 강화 샘플 이미지
	auto sprite = Sprite::create("Images/smith.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setScale(0.5f);

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
}