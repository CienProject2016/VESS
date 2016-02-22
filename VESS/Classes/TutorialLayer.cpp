#include "TutorialLayer.h"
#include "TutorialInfo.h"

using namespace std;

bool TutorialLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	tutorialBeginLock = false;
	GameData::getInstance()->setIsInTutorial(true);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TutorialLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto tutorial_layer = CCLayerColor::create(Color4B(0, 0, 0, 255 * 0.7), winSize.width, winSize.height*0.3f);
	tutorial_layer->setPosition(Vec2(0, 0));
	this->addChild(tutorial_layer, 0, "tutorialLayer");

	TutorialInfo::getInstance()->initTutorialInfo();
	
	tutorialYesButton = cocos2d::ui::Button::create(ImagePath::TUTORIAL_YES_BUTTON, ImagePath::TUTORIAL_YES_BUTTON, ImagePath::DISABLE_BUTTON_PATH);
	tutorialYesButton->addTouchEventListener(CC_CALLBACK_2(TutorialLayer::tutorialYesCallback, this));
	tutorialYesButton->setPosition(Vec2(visibleSize.width *0.3f, visibleSize.height *0.5f));
	this->addChild(tutorialYesButton);

	tutorialNoButton = cocos2d::ui::Button::create(ImagePath::TUTORIAL_NO_BUTTON, ImagePath::TUTORIAL_NO_BUTTON, ImagePath::DISABLE_BUTTON_PATH);
	tutorialNoButton->addTouchEventListener(CC_CALLBACK_2(TutorialLayer::tutorialNoCallback, this));
	tutorialNoButton->setPosition(Vec2(visibleSize.width *0.7f, visibleSize.height *0.5f));
	this->addChild(tutorialNoButton);


	tutorialData = GameData::getInstance()->getTutorialList();
	tutorialIterator = tutorialData->begin();
	
	this->setZOrder(3);
	auto tutorial = CCString::createWithFormat((*tutorialIterator).getLines().c_str(), 50);
	auto tutorialLabel = CCLabelTTF::create(tutorial->getCString(), "Arial", 50);
	tutorialLabel->setAnchorPoint(Vec2(0, 0));
	tutorialLabel->setColor(Color3B::WHITE);
	tutorialLabel->setPosition(Vec2(visibleSize.width *0.03f, visibleSize.height *0.1f));
	tutorial_layer->addChild(tutorialLabel, 1, "tutorialLabel");
	this->setTouchListener();
	
	return true;
}

void TutorialLayer::tutorialYesCallback(cocos2d::Ref* pSender, ui::Widget::TouchEventType type)
{
	switch (type) {
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED:
		tutorialBeginLock = true;
		this->removeChild(tutorialNoButton);
		this->removeChild(tutorialYesButton);
		showNextTutorial();
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	}
}

void TutorialLayer::tutorialNoCallback(cocos2d::Ref* pSender, ui::Widget::TouchEventType type)
{
	switch (type) {
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED: {
		this->setZOrder(-3);
		this->setVisible(false);
		GameData::getInstance()->setIsInTutorial(false);
		auto gameScene = (GameScene*)Director::getInstance()->getRunningScene();
		gameScene->removeChild(this);
		break;
	}		
	case ui::Widget::TouchEventType::CANCELED:
		break;
	}
}

bool TutorialLayer::hasNextTutorial()
{
	if (tutorialIterator+1 != tutorialData->end()) {
		return true;
	}
	return false;
}

bool TutorialLayer::isNoneEvent() {
	if ((*tutorialIterator).getEventType() == "none") {
		return true;
	}
	return false;
}
void TutorialLayer::showNextTutorial()
{
	tutorialIterator++;
	GameData::getInstance()->setIsInTutorial(true);
	this->setZOrder(3);
	auto gameScene = (GameScene*)Director::getInstance()->getRunningScene();
	CCLayer* tutorial_layer = (CCLayer*) this->getChildByName("tutorialLayer");
	auto tutorial = CCString::createWithFormat((*tutorialIterator).getLines().c_str(), 50);
	auto tutorialLabel = (CCLabelTTF*)tutorial_layer->getChildByName("tutorialLabel");
	tutorialLabel->setString(tutorial->getCString());
}

void TutorialLayer::setTouchListener()
{
	// make touch listener

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
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
	if (tutorialBeginLock) {
		if (hasNextTutorial()) {
			if (isNoneEvent()) {				
				showNextTutorial();
			}
			else {
				TutorialInfo::getInstance()->setCurrentEvent((*tutorialIterator).getEventType());
				Director::getInstance()->resume();
				GameData::getInstance()->setIsInTutorial(false);
				this->setVisible(false);
				this->setZOrder(-3);
			}
		}
		else {
			this->setVisible(false);
			this->setZOrder(-3);
			Director::getInstance()->resume();
			TutorialInfo::getInstance()->initTutorialInfo();
			GameData::getInstance()->setIsInTutorial(false);
			auto gameScene = (GameScene*)Director::getInstance()->getRunningScene();
			gameScene->removeChild(this);
		}
	}

}

