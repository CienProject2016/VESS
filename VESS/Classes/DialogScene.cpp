
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
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundImage = Sprite::create("Images/bg_background.png");
	backgroundImage->setPosition(Vec2(0, 0));
	backgroundImage->setAnchorPoint(Vec2(0, 0));
	this->addChild(backgroundImage);


	auto winSize = CCDirector::sharedDirector()->getWinSize();
	dialogData = GameData::getInstance()->getDialogList();
	dialogIterator = dialogData->begin();
	auto dialogLayer = CCLayerColor::create(ccc4(0, 0, 0, 255 * 0.7), winSize.width, winSize.height * 0.35);
	dialogLayer->setPosition(Vec2(0, 0));
	this->addChild(dialogLayer,0,"dialogLayer");

	auto dialogue = CCString::createWithFormat((*dialogIterator).getDialogue().c_str(), 50);
	auto dialogLabel = CCLabelTTF::create(dialogue->getCString(), "Arial", 50);
	dialogLabel->setAnchorPoint(Vec2(0, 0));
	dialogLabel->setColor(Color3B::WHITE);
	dialogLabel->setPosition(Vec2(visibleSize.width *0.3f , visibleSize.height *0.1f));
	dialogLayer->addChild(dialogLabel, 1, "dialogLabel");

	auto nameLabel = Label::createWithSystemFont( (*dialogIterator).getName().c_str(), "Arial", 60);
	nameLabel->setAnchorPoint(Vec2(0, 0));
	nameLabel->setColor(Color3B::WHITE);
	nameLabel->setPosition(Vec2(visibleSize.width*0.1f, visibleSize.height *0.4f));
	dialogLayer->addChild(nameLabel, 2, "nameLabel");

	string imagePath = (*dialogIterator).getImage();
	auto faceImage = Sprite::create("Images/" + imagePath + ".png");
	faceImage->setAnchorPoint(Vec2(0, 0));
	faceImage->setPosition(Vec2(visibleSize.width*0.6f, visibleSize.height *0.15f));
	dialogLayer->addChild(faceImage, 3, "faceImage");


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
	CCLayer* dialogLayer = (CCLayer*) this->getChildByName("dialogLayer");
	auto dialogue = CCString::createWithFormat((*dialogIterator).getDialogue().c_str(), 50);
	auto dialogLabel = (CCLabelTTF*)dialogLayer->getChildByName("dialogLabel");
	dialogLabel->setString(dialogue->getCString());

	auto name = CCString::createWithFormat((*dialogIterator).getName().c_str(), 60);
	auto nameLabel = (Label*)dialogLayer->getChildByName("nameLabel");
	nameLabel->setString(name->getCString());
	

	string imagePath = (*dialogIterator).getImage();
	auto faceImage = (Sprite*)dialogLayer->getChildByName("faceImage");
	faceImage->setTexture("Images/" + imagePath + ".png");
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
