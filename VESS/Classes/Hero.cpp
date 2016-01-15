#include "Hero.h"
#include "cocostudio\CocoStudio.h"
using namespace cocostudio;
bool Hero::init()
{
	if (Unit::init())
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();


		Node* node = CSLoader::createNode("animation/Hero.csb");
		this->addChild(node); //get animation data 
		timeline::ActionTimeline* action = CSLoader::createTimeline("animation/Hero.csb");
		node->setPosition(Vec2(0 ,0));

		node->runAction(action);
		action->gotoFrameAndPlay(0, 32, true);
		
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
