#include "GameScene.h"

#include "UpgradeLayer.h"
#include "FightLayer.h"
#include "GameData.h"
#include "Stage.h"
#include "WindowSize.h"

USING_NS_CC;
using namespace std;


Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	//스테이지 정보를 게임데이터에서 얻어온다.
	Document data = getGameData();
	GameData::getInstance()->getStage().setStageLevel(data["stage"].GetInt());



	// 'layer' is an autorelease object
	auto upgrade_layer = UpgradeLayer::create();
	auto fight_layer = FightLayer::create();

	upgrade_layer->setContentSize(Size(960, 1080));
	upgrade_layer->setPosition(Vec2(0, 0));

	fight_layer->setContentSize(Size(960, 1080));
	fight_layer->setPosition(Vec2(960, 0));

	// add layer as a child to scene
	scene->addChild(upgrade_layer);
	scene->addChild(fight_layer);

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
	

	auto upgrade_layer = UpgradeLayer::create();
	auto fight_layer = FightLayer::create();
	this->addChild(upgrade_layer);
	this->addChild(fight_layer);	

	return true;
}

Document GameScene::getGameData()
{
	// 1. Json을 Dom구조로 파싱하기
	const char* json = "{\"stage\" : 1}";
	Document document;
	document.Parse(json);

	// 2. Dom구조로 고치기
	rapidjson::Value& s = document["stage"];
	s.SetInt(s.GetInt() + 1);

	
	// 3. Stringify the DOM
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	document.Accept(writer);

	return document;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
