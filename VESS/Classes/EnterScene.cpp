#pragma once
#include "EnterScene.h"
#include "DialogScene.h"
#include "ui/CocosGUI.h"

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
	settingButton->setPosition(Vec2((visibleSize.width / 5) * 4 + origin.x, (visibleSize.height / 5) * 4 + origin.y));
	settingButton->setScale(0.3f);
	this->addChild(settingButton, 1);

	auto backgroundScreen = Sprite::create("Images/BackgroundScreen.png");
	backgroundScreen->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	backgroundScreen->setScale(1.2f);
	this->addChild(backgroundScreen, 0);

	auto myScene = Scene::create();

	auto enterStage1 = ui::Button::create("Images/Door.png", "Images/BackgroundScreen.png", "Images/SettingButton.png");
	enterStage1->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 5));
	enterStage1->setScale(0.5f);
	enterStage1->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(enterStage1);
	

	auto enterStage2 = ui::Button::create("Images/Door.png", "Images/BackgroundScreen.png", "Images/SettingButton.png");
	enterStage2->setPosition(Vec2(visibleSize.width / 5 +.7*(visibleSize.width/5), visibleSize.height / 5));
	enterStage2->setScale(.5f);
	enterStage2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(enterStage2);


	auto enterStage3 = ui::Button::create("Images/Door.png", "Images/BackgroundScreen.png", "Images/SettingButton.png");
	enterStage3->setPosition(Vec2(visibleSize.width / 5 + 1.4*(visibleSize.width / 5), visibleSize.height / 5));
	enterStage3->setScale(.5f);
	enterStage3->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(enterStage3);

	auto enterStage4 = ui::Button::create("Images/Door.png", "Images/BackgroundScreen.png", "Images/SettingButton.png");
	enterStage4->setPosition(Vec2(visibleSize.width / 5 + 2.1*(visibleSize.width / 5), visibleSize.height / 5));
	enterStage4->setScale(.5f);
	enterStage4->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(enterStage4);


	auto enterStage5 = ui::Button::create("Images/Door.png", "Images/BackgroundScreen.png", "Images/SettingButton.png");
	enterStage5->setPosition(Vec2(visibleSize.width / 5 + 2.8*(visibleSize.width / 5), visibleSize.height / 5));
	enterStage5->setScale(.5f);
	enterStage5->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(enterStage5);


	auto enterStage6 = ui::Button::create("Images/Door.png", "Images/BackgroundScreen.png", "Images/SettingButton.png");
	enterStage6->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 5 + (visibleSize.width / 5)));
	enterStage6->setScale(.5f);
	enterStage6->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(enterStage6);


	auto enterStage7 = ui::Button::create("Images/Door.png", "Images/BackgroundScreen.png", "Images/SettingButton.png");
	enterStage7->setPosition(Vec2(visibleSize.width / 5 + .7*(visibleSize.width / 5), visibleSize.height / 5 + (visibleSize.width / 5)));
	enterStage7->setScale(.5f);
	enterStage7->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(enterStage7);

	auto enterStage8 = ui::Button::create("Images/Door.png", "Images/BackgroundScreen.png", "Images/SettingButton.png");
	enterStage8->setPosition(Vec2(visibleSize.width / 5 + 1.4*(visibleSize.width / 5), visibleSize.height / 5 + (visibleSize.width / 5)));
	enterStage8->setScale(.5f);
	enterStage8->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(enterStage8);


	auto enterStage9 = ui::Button::create("Images/Door.png", "Images/BackgroundScreen.png", "Images/SettingButton.png");
	enterStage9->setPosition(Vec2(visibleSize.width / 5 + 2.1*(visibleSize.width / 5), visibleSize.height / 5 + (visibleSize.width / 5)));
	enterStage9->setScale(.5f);
	enterStage9->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(enterStage9);

	auto backButton = Sprite::create("Images/back.png");
	backButton->setPosition(Vec2(visibleSize.width / 5, (visibleSize.height / 5) * 4 + origin.y));
	backButton->setScale(0.3f);
	this->addChild(backButton,0);

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
	Scene *dialogScene = DialogScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, dialogScene, Color3B(0, 255, 255)));
	log("Touched");
}


void EnterScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

