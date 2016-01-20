#pragma once
#include "EnterScene.h"
#include "StageScene.h"

USING_NS_CC;

Scene* EnterScene::createScene()
{
	auto scene = Scene::create(); //Scene생성
	auto layer = EnterScene::create();//Layer생성
	scene->addChild(layer);//Layer을 Scene의 자식으로 함
	return scene;
}

bool EnterScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(EnterScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);
	//새 스프라이트들 만들어서 크기,위치 지정
	auto enterButton = Sprite::create("Images/EnterButton.png");
	enterButton->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 5 + origin.y));
	enterButton->setScale(0.15f);
	this->addChild(enterButton, 2);

	auto settingButton = Sprite::create("Images/SettingButton.png");
	settingButton->setPosition(Vec2((visibleSize.width / 5)*4 + origin.x, (visibleSize.height / 5)*4 + origin.y));
	settingButton->setScale(0.3f);
	this->addChild(settingButton, 1);

	auto backgroundScreen = Sprite::create("Images/BackgroundScreen.png");
	backgroundScreen->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	backgroundScreen->setScale(1.2f);
	this->addChild(backgroundScreen, 0); 




	setTouchListener();

}



void EnterScene::setTouchListener()
{
	// make touch listener

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(EnterScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(EnterScene::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(EnterScene::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(EnterScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

bool EnterScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}

void EnterScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void EnterScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void EnterScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	Scene *stageScene = StageScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, stageScene, Color3B(0, 255, 255)));
	log("Touched");
}


void EnterScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

