#pragma once
#include "RefinementLayer.h"

bool RefinementLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	log("refinementLayer visibleWidthSize : %f", visibleSize.width);
	log("refinementLayer visibleHeightSize : %f", visibleSize.height);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	log("refinementLayer origin.x : %f, origin.y : %f", origin.x, origin.y);

	// 강화 샘플 이미지
	auto smithImage = Sprite::create("Images/smith.png");

	// position the sprite on the center of the screen
	smithImage->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y+visibleSize.height*0.4f));
	smithImage->setScale(1.0f);

	// add the sprite as a child to this layer
	this->addChild(smithImage, 0);
}