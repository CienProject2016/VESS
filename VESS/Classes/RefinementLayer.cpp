#pragma once
#include "RefinementLayer.h"
#include "WindowSize.h"


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
	int smith_width = smithImage->getTexture()->getPixelsWide();
	float smith_size = refinementLayerSize.width/ smith_width;
	smithImage->setPosition(Vec2(origin.x + smith_size * smith_width * 0.5f, origin.y + visibleSize.height*0.4f));
	smithImage->setScale(smith_size);

	
	// add the sprite as a child to this layer
	this->addChild(smithImage, 0);
}
