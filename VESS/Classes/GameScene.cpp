#include "GameScene.h"
#include "RefinementLayer.h"
#include "FightLayer.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto refinementLayer = RefinementLayer::create();
	auto fightLayer = FightLayer::create();

	refinementLayer->setContentSize(Size(480, 780));
	refinementLayer->setPosition(Vec2(0, 0));

	fightLayer->setContentSize(Size(480, 780));
	fightLayer->setPosition(Vec2(240, 0));

	// add layer as a child to scene
	scene->addChild(refinementLayer);
	scene->addChild(fightLayer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto refinementLayer = RefinementLayer::create();
	auto fightLayer = FightLayer::create();
	this->addChild(refinementLayer);
	this->addChild(fightLayer);

	return true;
}


void GameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
