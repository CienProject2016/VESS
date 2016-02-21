#include "GameScene.h"

#include "UpgradeLayer.h"
#include "FightLayer.h"
#include "TutorialLayer.h"
#include "GameData.h"
#include "Stage.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;


Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	//게임 거리정보 초기화
	GameData::getInstance()->setMovingDistance(0);

	// 'layer' is an autorelease object
	auto upgrade_layer = UpgradeLayer::create();
	auto fight_layer = FightLayer::create();

	upgrade_layer->setContentSize(Size(760, 1080));
	upgrade_layer->setPosition(Vec2(0, 0));//강화창

	fight_layer->setContentSize(Size(1160, 1080));
	fight_layer->setPosition(Vec2(760, 0));//전투창
	scene->addChild(upgrade_layer, 1, "upgradeLayer");
	scene->addChild(fight_layer, 0, "fightLayer");

	if (GameData::getInstance()->getIsTutorial()) {
		auto tutorialLayer = TutorialLayer::create();

		tutorialLayer->setContentSize(Size(1920, 1080));
		tutorialLayer->setPosition(Vec2(0, 0));//튜토리얼창

		// add layer as a child to scene

		scene->addChild(tutorialLayer, 2, "tutorialLayer");
		
	}
	
	
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AudioPath::BGM_NEO_ROCK.c_str(), true);
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

	upgradeLayer = UpgradeLayer::create();
	fightLayer = FightLayer::create();
	
	fightLayer->setName("fightLayer");
	upgradeLayer->setName("upgradeLayer");
	this->addChild(upgradeLayer);
	this->addChild(fightLayer);	
	auto tutorialLayer = TutorialLayer::create();
	tutorialLayer->setName("tutorialLayer");
	this->addChild(tutorialLayer);
	
	return true;
}


void GameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
