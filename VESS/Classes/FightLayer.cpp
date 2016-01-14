#pragma once
#include "FightLayer.h"
#include "Monster.h"
#include "Hero.h"


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


	// µşÀÌ »ı¼ºµÊ
	auto daughter = Hero::create();

	//¸ó½ºÅÍ°¡ »ı¼ºµÊ
	auto monster = Monster::create("slime");

	// add the unit as a child to this layer
	this->addChild(daughter, 0);
	this->addChild(monster, 1);

	
	return true;
}
