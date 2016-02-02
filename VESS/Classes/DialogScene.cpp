 #include "DialogScene.h"
#include "GameScene.h"
#include "GameData.h"
USING_NS_CC;

Scene* DialogScene::createScene()
{
	auto scene = Scene::create(); //Scene생성
	auto layer = DialogScene::create();//Layer생성
	scene->addChild(layer);//Layer을 Scene의 자식으로 함
	return scene;
}

bool DialogScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = CCDirector::sharedDirector()->getWinSize();
	dialogData = GameData::getInstance()->getDialogList();
	dialogIterator = dialogData->begin();
	auto textLayer = CCLayerColor::create(ccc4(0, 0, 0, 255 * 0.7), winSize.width, winSize.height * 0.25);
	textLayer->setPosition(Vec2(0, 0));
	this->addChild(textLayer,0,"textLayer");

	auto dialogue = CCString::createWithFormat((*dialogIterator).getDialogue().c_str(), 30);

	auto textLabel = CCLabelTTF::create(dialogue->getCString(), "Arial", 30);
	textLabel->setAnchorPoint(ccp(0, 0));
	textLabel->setColor(Color3B::WHITE);
	textLabel->setPosition(ccp(30, textLayer->getContentSize().height - textLabel->getContentSize().height - 30));
	textLayer->addChild(textLabel, 1, "textLabel");

	this->setTouchListener();
	dialogIterator++;
	return true;
}

bool DialogScene::hasNextDialog()	
{
	if (dialogIterator != dialogData->end()) {
		return true;
	}
	return false;
}

void DialogScene::showNextDialog()
{
	CCLayer* dialogLayer = (CCLayer*) this->getChildByName("textLayer");
	auto dialogue = CCString::createWithFormat((*dialogIterator).getDialogue().c_str(), 30);
	auto textLabel = (CCLabelTTF*)dialogLayer->getChildByName("textLabel");
	textLabel->setString(dialogue->getCString());
	dialogIterator++;
}

void DialogScene::setTouchListener()
{
	// make touch listener

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(DialogScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(DialogScene::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(DialogScene::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(DialogScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

bool DialogScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}

void DialogScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void DialogScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void DialogScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	if (hasNextDialog()) {
		showNextDialog();
	}
	else {
		Scene *gameScene = GameScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameScene, Color3B(0, 255, 255)));
	}
	log("Touched");
}


void DialogScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
