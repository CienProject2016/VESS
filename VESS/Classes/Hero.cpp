#include "Hero.h"

bool Hero::init()
{
	if (Unit::init())
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto daughterImage = Sprite::create("Images/daughter.png");
		daughterImage->setPosition(Vec2(origin.x, origin.y + visibleSize.height*0.5f));
		daughterImage->setScale(1.0f);
		daughterImage->setVisible(true);
		this->addChild(daughterImage);
		
		return true;
	}
	return false;
}

Hero* Hero::create()
{
	Hero *hero = new Hero();
	if (hero && hero->init())
	{
		hero->autorelease();

		return hero;
	}
	CC_SAFE_DELETE(hero);
	return nullptr;
}
