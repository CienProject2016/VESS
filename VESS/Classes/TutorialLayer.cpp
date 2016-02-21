#include "TutorialLayer.h"

using namespace std;

bool TutorialLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TutorialLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto tutorial_layer = CCLayerColor::create(Color4B(0, 0, 0, 255 * 0.7), winSize.width, winSize.height*0.2f);
	tutorial_layer->setPosition(Vec2(0, 0));
	this->addChild(tutorial_layer, 0, "tutorialLayer");

	
	tutorialData = GameData::getInstance()->getTutorialList();
	tutorialIterator = tutorialData->begin();
	

	auto tutorial = CCString::createWithFormat((*tutorialIterator).getTutorial().c_str(), 50);
	auto tutorialLabel = CCLabelTTF::create(tutorial->getCString(), "Arial", 50);
	tutorialLabel->setAnchorPoint(Vec2(0, 0));
	tutorialLabel->setColor(Color3B::WHITE);
	tutorialLabel->setPosition(Vec2(visibleSize.width *0.03f, visibleSize.height *0.1f));
	tutorial_layer->addChild(tutorialLabel, 1, "tutorialLabel");

	tutorialIterator++;
	
	this->setTouchListener();
	return true;
}

bool TutorialLayer::hasNextTutorial()
{
	if (tutorialIterator != tutorialData->end()) {
		return true;
	}
	return false;
}
void TutorialLayer::showNextTutorial()
{
	CCLayer* tutorial_layer = (CCLayer*) this->getChildByName("tutorialLayer");
	auto tutorial = CCString::createWithFormat((*tutorialIterator).getTutorial().c_str(), 50);
	auto tutorialLabel = (CCLabelTTF*)tutorial_layer->getChildByName("tutorialLabel");
	tutorialLabel->setString(tutorial->getCString());
	tutorialIterator++;
}
void TutorialLayer::setTouchListener()
{
	// make touch listener

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TutorialLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TutorialLayer::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(TutorialLayer::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(TutorialLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool TutorialLayer::onTouchBegan(Touch* touch_, Event* event_)
{
	return true;
}
void TutorialLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void TutorialLayer::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void TutorialLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	if (hasNextTutorial()) {
		showNextTutorial();
	}
	else {
		this->setVisible(false);
		this->setTouchEnabled(false);
	}

}