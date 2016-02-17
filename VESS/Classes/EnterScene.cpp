#pragma once
#include "EnterScene.h"
#include "Settings.h"

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
	int i;
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create("CloseNormal.png","CloseSelected.png",CC_CALLBACK_1(EnterScene::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);
	
	auto enterButton = Sprite::create("Images/enter_button.png");
	enterButton->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 5 + origin.y));
	enterButton->setScale(0.15f);
	this->addChild(enterButton, 2);

	auto settingButton = MenuItemImage::create("Images/setting_button.png", "Images/setting_button.png", CC_CALLBACK_1(EnterScene::settingClicked, this));
	settingButton->setPosition(Vec2((visibleSize.width / 5) * 4 + origin.x, (visibleSize.height / 5) * 4 + origin.y));
	settingButton->setScale(0.3f);

	auto setting = Menu::create(settingButton, NULL);
	setting->setPosition(Vec2::ZERO);
	this->addChild(setting, 1);

	auto backgroundScreen = Sprite::create("Images/background_screen.png");
	backgroundScreen->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	backgroundScreen->setScale(1.2f);
	this->addChild(backgroundScreen, 0);

	auto myScene = Scene::create();

	for (i = 1; i < 10; i++){
		auto enterStage = ui::Button::create("Images/door.png", "", "Images/setting_button.png");
		if (i < 6)
			enterStage->setPosition(Vec2(visibleSize.width / 5 + (i - 1)*0.7*(visibleSize.width / 5), visibleSize.height / 5));
		else
			enterStage->setPosition(Vec2(visibleSize.width / 5 + (i - 6)*0.7*(visibleSize.width / 5), visibleSize.height / 5 + (visibleSize.width / 5)));
		enterStage->setScale(2.0f);
		enterStage->setTag(stageDoor + i);

		enterStage->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
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
		this->addChild(enterStage);
	}

	auto backButton = Sprite::create("Images/back.png");
	backButton->setPosition(Vec2(visibleSize.width / 5, (visibleSize.height / 5) * 4 + origin.y));
	backButton->setScale(0.3f);
	this->addChild(backButton,0);

	setTouchListener();
	
	return true;
}



void EnterScene::setTouchListener()
{
	
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
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, dialogScene, Color3B(255, 255, 255)));
	log("Touched");
}

void EnterScene::settingClicked(Ref* pSender)
{
	Scene *settingScene = Settings::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, settingScene, Color3B(255, 255, 255)));
	log("Touched");

}


void EnterScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

