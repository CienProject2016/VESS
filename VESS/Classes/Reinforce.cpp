#include "Reinforce.h"
#include "GameScene.h"
#include "UpgradeLayer.h"
//#include "GameData.h"
//#include "Stage.h"
//#include "FightLayer.h"


USING_NS_CC;
using namespace std;

Reinforce::Reinforce()
{}
Reinforce::~Reinforce()
{}
Scene* Reinforce::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	//스테이이 정보
	//Document data = getGameData();
	//GameData::getInstance()->getStage().setStageLevel(data["stage"].GetInt());
	

	// 'layer' is an autorelease object
	auto reinforce_layer = Reinforce::create();
	//auto fight_layer = FightLayer::create();

	reinforce_layer->setContentSize(Size(760, 1080));
	reinforce_layer->setPosition(Vec2(0, 0));//강화창

	//fight_layer->setContentSize(Size(1160, 1080));
	//fight_layer->setPosition(Vec2(760, 0));//전투창

	scene->addChild(reinforce_layer, 1);
	//scene->addChild(fight_layer, 0);

	return scene;
}
bool Reinforce::init()
{
	if (!Layer::init()) {
		return false;
	}
	counter = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	log("UpgradeLayer visibleWidthSize : %f", visibleSize.width);
	log("UpgradeLayer visibleHeightSize : %f", visibleSize.height);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	log("UpgradeLayer origin.x : %f, origin.y : %f", origin.x, origin.y);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Reinforce::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto smelting_image = Sprite::create("Images/smelting_button.png");
	auto hammering_image = Sprite::create("Images/hammering_button.png");
	auto quenching_image = Sprite::create("Images/quenching_button.png");

	smelting_image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.2f));
	smelting_image->setScale(1.0f);
	smelting_image->setTag(1);

	hammering_image->setPosition(Vec2(origin.x + visibleSize.width * 0.1f, origin.y + visibleSize.height*0.4f));
	hammering_image->setScale(1.0f);
	hammering_image->setTag(2);

	quenching_image->setPosition(Vec2(origin.x + visibleSize.width * 0.3f, origin.y + visibleSize.height*0.4f));
	quenching_image->setScale(1.0f);
	quenching_image->setTag(3);

	this->addChild(smelting_image);
	this->addChild(hammering_image);
	this->addChild(quenching_image);

	
	return true;
	
}
void Reinforce::gazeCreate()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (counter == 0)
	{
		CCSprite *timer_gaze = CCSprite::create("timebar.png");
		CCProgressTimer *gazing = CCProgressTimer::create(timer_gaze);
		gazing->setPosition(Vec2(origin.x + visibleSize.width * 0.2, origin.y + visibleSize.height*0.95));
		gazing->setPercentage(0);
		gazing->setMidpoint(ccp(0, 0.5));
		gazing->setBarChangeRate(ccp(1, 0));
		gazing->setType(kCCProgressTimerTypeBar);

		this->addChild(gazing);

		CCProgressFromTo* progressToZero = CCProgressFromTo::create(15, 100, 0);
		gazing->runAction(progressToZero);

		CCSprite* timeOutline = CCSprite::create("timeoutline.png");
		timeOutline->setPosition(Vec2(origin.x + visibleSize.width * 0.2, origin.y + visibleSize.height*0.95));
		timeOutline->setVisible(true);
		this->addChild(timeOutline);
		counter += 1;

	}
	else if (counter == 1)
	{
		CCSprite *timer_gaze2 = CCSprite::create("timebar.png");
		CCProgressTimer *gazing2 = CCProgressTimer::create(timer_gaze2);
		gazing2->setPosition(Vec2(origin.x + visibleSize.width * 0.2, origin.y + visibleSize.height*0.9));
		gazing2->setPercentage(100.f);
		gazing2->setMidpoint(ccp(0, 0.5));
		gazing2->setBarChangeRate(ccp(1, 0));
		gazing2->setType(kCCProgressTimerTypeBar);

		this->addChild(gazing2);

		CCProgressFromTo* progressToZero2 = CCProgressFromTo::create(15, 100, 0);
		gazing2->runAction(progressToZero2);

		CCSprite* timeOutline2 = CCSprite::create("timeoutline.png");
		timeOutline2->setPosition(Vec2(origin.x + visibleSize.width * 0.2, origin.y + visibleSize.height*0.9));
		timeOutline2->setVisible(true);
		this->addChild(timeOutline2);
		counter += 1;

	}
	else if (counter == 2)
	{
		CCSprite *timer_gaze3 = CCSprite::create("timebar.png");
		CCProgressTimer *gazing3 = CCProgressTimer::create(timer_gaze3);
		gazing3->setPosition(Vec2(origin.x + visibleSize.width * 0.2, origin.y + visibleSize.height*0.85));
		gazing3->setPercentage(100.f);
		gazing3->setMidpoint(ccp(0, 0.5));
		gazing3->setBarChangeRate(ccp(1, 0));
		gazing3->setType(kCCProgressTimerTypeBar);

		this->addChild(gazing3);

		CCProgressFromTo* progressToZero3 = CCProgressFromTo::create(15, 100, 0);
		gazing3->runAction(progressToZero3);

		CCSprite* timeOutline3 = CCSprite::create("timeoutline.png");
		timeOutline3->setPosition(Vec2(origin.x + visibleSize.width * 0.2, origin.y + visibleSize.height*0.85));
		timeOutline3->setVisible(true);
		this->addChild(timeOutline3);
		

	}
	
}
void Reinforce::gazeIncrease()
{
	
	
}
bool Reinforce::onTouchBegan(Touch* touch_, Event* event_)
{
	Point p = touch_->getLocation();
	auto smelting = (Sprite*) this->getChildByTag(1);
	Rect rect3 = smelting->getBoundingBox();
	if (rect3.containsPoint(p)) {

		gazeCreate();
		//smelting->setScale(2);
	}
	else {

		smelting->setScale(1);
	}

	auto hammering = (Sprite*) this->getChildByTag(2);
	Rect rect4 = hammering->getBoundingBox();
	if (rect4.containsPoint(p)) {

		gazeCreate();
		//hammering->setScale(2);
	}
	else {

		hammering->setScale(1);
	}

	auto quenching = (Sprite*) this->getChildByTag(3);
	Rect rect5 = quenching->getBoundingBox();
	if (rect5.containsPoint(p)) {

		gazeCreate();
		//quenching->setScale(2);
	}
	else {

		quenching->setScale(1);
	}
	
	
	return true;

}
void Reinforce::setTouchListener()
{
	// make touch listener

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Reinforce::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Reinforce::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(Reinforce::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(Reinforce::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


void Reinforce::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void Reinforce::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void Reinforce::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}