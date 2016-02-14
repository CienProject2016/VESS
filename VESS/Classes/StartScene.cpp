#pragma once
#include "StartScene.h"
#include "GameScene.h"
#include "Settings.h"
#include "EnterScene.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StartScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)))
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
   
	
	auto openSetting = MenuItemImage::create("Images/SettingButton.png", "Images/SettingButton.png", CC_CALLBACK_1(StartScene::settingClicked, this));
	openSetting->setPosition(Vec2(origin.x + visibleSize.width - openSetting->getContentSize().width / 10,
		origin.y + visibleSize.height - openSetting->getContentSize().height/7));
	openSetting->setScale(0.2f);

	auto setting = Menu::create(openSetting, NULL);
	setting->setPosition(Vec2::ZERO);
	this->addChild(setting, 1);

    // add a label shows "Hello World"
    // create and initialize a label
	auto subLabel = Label::createWithSystemFont("본격 강화 피지컬 액션 RPG", "Arial", 70);
	subLabel->setPosition(Vec2(origin.x + visibleSize.width *0.25f, origin.y + visibleSize.height *0.5f));
	subLabel->setColor(ccc3(0, 0, 0));
	this->addChild(subLabel);

	auto label = Label::createWithTTF("V   E        S   S", "fonts/arial.ttf", 250);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height*2.5));
	label->setColor(ccc3(0, 0, 0)); //black

	auto touchLabel = Label::createWithSystemFont("시작하시려면 화면을 터치하세요", "Arial", 70);
	touchLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 + 10,
		origin.y + visibleSize.height - touchLabel->getContentSize().height * 12));
	touchLabel->setColor(ccc3(0, 0, 0));
	// add the label as a child to this layer
	this->addChild(label, 1);
	this->addChild(touchLabel, 2);

	// add "StartScene" splash screen"
	auto sprite = Sprite::create("Images/daughter.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setScale(1.5f);


	setTouchListener();

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/bgm_op.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm_op.mp3");
    return true;
}

void StartScene::setTouchListener()   
{
	// make touch listener

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(StartScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(StartScene::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(StartScene::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(StartScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

bool StartScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}

void StartScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void StartScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void StartScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	//CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Scene *EnterScene = EnterScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, EnterScene, Color3B(0, 255, 255)));
	log("Touched");
}


void StartScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void StartScene::settingClicked(Ref* pSender)
{
	Scene *settingScene=Settings::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, settingScene, Color3B(0, 255, 255)));
	log("Touched");
	
}