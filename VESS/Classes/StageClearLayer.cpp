#pragma once
#include "StageClearLayer.h"
#include "GameScene.h"
#include "EnterScene.h"

bool StageClearLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	log("StageClearLayer visibleWidthSize : %f", visibleSize.width);
	log("StageClearLayer visibleHeightSize : %f", visibleSize.height);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	log("StageClearLayer origin.x : %f, origin.y : %f", origin.x, origin.y);


	//��ư
	auto nextStageButton = MenuItemImage::create("Images/NextStageButton.png", "Images/NextStageButton.png", "Images/DisabledButton.png", CC_CALLBACK_1(StageClearLayer::nextStageCallback, this));
	auto stageSelectButton = MenuItemImage::create("Images/StageSelectButton.png", "Images/StageSelectButton.png", "Images/DisabledButton.png", CC_CALLBACK_1(StageClearLayer::stageSelectCallback, this));
	nextStageButton->setScale(0.7f);
	stageSelectButton->setScale(2.5f);

	//���
	auto backgroundImage = Sprite::create("Images/BlackBackground.png");
	backgroundImage->setPosition(Vec2(origin.x, origin.y ));
	backgroundImage->setScale(0.5f);

	//�޴�
	auto clear_Menu = Menu::create(nextStageButton, stageSelectButton, NULL);
	clear_Menu->setPosition(Vec2(origin.x , origin.y + visibleSize.height*0.05f));
	//setPosition(Vec2(origin.x + visibleSize.width*0.325f, origin.y + visibleSize.height*0.15f)
	clear_Menu->alignItemsHorizontally();
	clear_Menu->alignItemsVerticallyWithPadding(visibleSize.width*0.02f);
	
	this->addChild(backgroundImage,1);
	this->addChild(clear_Menu,2);
	
	return true;
}

void StageClearLayer::nextStageCallback(cocos2d::Ref* pSender)
{
	
	CCLOG("nextStageCallback");
}

void StageClearLayer::stageSelectCallback(cocos2d::Ref* pSender)
{

	Scene *EnterScene = EnterScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, EnterScene, Color3B(0, 255, 255)));
	CCLOG("stageSelectCallback");
}