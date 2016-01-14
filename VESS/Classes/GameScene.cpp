#include "GameScene.h"

#include "RefinementLayer.h"
#include "FightLayer.h"
#include "GameData.h"

USING_NS_CC;
using namespace std;


Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	//스테이지 정보를 게임데이터에서 얻어온다.
	Document data = getGameData();
	GameData::getInstance()->setStage(data["stage"].GetInt());
	log("stage : %d", GameData::getInstance()->getStage());


	// 'layer' is an autorelease object
	auto refinementLayer = RefinementLayer::create();
	auto fightLayer = FightLayer::create();

	refinementLayer->setContentSize(Size(960, 1080));
	refinementLayer->setPosition(Vec2(0, 0));

	fightLayer->setContentSize(Size(960, 1080));
	fightLayer->setPosition(Vec2(960, 0));

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
