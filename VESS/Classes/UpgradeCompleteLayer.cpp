#include "UpgradeCompleteLayer.h"
#include "ResourcePath.h"
#include "GameData.h"

USING_NS_CC;

cocos2d::Scene* UpgradeCompleteLayer::createScene() {
	auto scene = Scene::create(); //Scene생성
	auto layer = UpgradeCompleteLayer::create();//Layer생성
	scene->addChild(layer);//Layer을 Scene의 자식으로 함
	return scene;
}

bool UpgradeCompleteLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	static Size visibleSize = Director::getInstance()->getVisibleSize();
	static Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto upgradeCompleteFrameImage = Sprite::create(ImagePath::UPGRADE_COMPLETE_POPUP_FRAME_PATH);
	upgradeCompleteFrameImage->setAnchorPoint(Vec2(0, 0));
	upgradeCompleteFrameImage->setPosition(Vec2(0, 0));
	upgradeCompleteFrameImage->setName("upgradeCompleteFrameImage");
	this->addChild(upgradeCompleteFrameImage);

	showUpgradeInfo();
	

	auto confirmButton = MenuItemImage::create(ImagePath::CONFIRM_BUTTON_PATH, ImagePath::CONFIRM_BUTTON_PATH, ImagePath::DISABLE_BUTTON_PATH, CC_CALLBACK_1(UpgradeCompleteLayer::confirmCallback, this));
	auto menu = Menu::create(confirmButton, NULL);
	CCLOG("visibleSize : %d" , visibleSize.width);
	menu->setPosition(visibleSize.width * 0.30f, visibleSize.height * 0.115f);
	this->addChild(menu);
	this->scheduleUpdate();
	return true;
}

void UpgradeCompleteLayer::showUpgradeInfo() {
	static Size visibleSize = Director::getInstance()->getVisibleSize();
	static Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Label* nameLabel;
	Label* statusLabel;
	switch (GameData::getInstance()->getUpgradeItemMode()) {
	case GameData::ItemMode::SWORD:
		nameLabel = Label::createWithSystemFont("", "Arial", 50);
		nameLabel->setString(StringUtils::format("무기 이름 : %s", GameData::getInstance()->getSword()->getName().c_str()));
		statusLabel = Label::createWithSystemFont("", "Arial", 50);
		statusLabel->setString(StringUtils::format("공격력: %d", GameData::getInstance()->getSword()->getDamage()));
		break;
	case GameData::ItemMode::SHIELD:
		nameLabel = Label::createWithSystemFont("", "Arial", 50);
		nameLabel->setString(StringUtils::format("방패 이름 : %s", GameData::getInstance()->getShield()->getName().c_str()));
		statusLabel = Label::createWithSystemFont("", "Arial", 50);
		statusLabel->setString(StringUtils::format("방어력 : %d", GameData::getInstance()->getShield()->getDefense()));
		break;
	}
	nameLabel->setAnchorPoint(Vec2(0, 0));
	statusLabel->setAnchorPoint(Vec2(0, 0));
	nameLabel->setColor(Color3B(0, 0, 0));
	statusLabel->setColor(Color3B(0, 0, 0));
	nameLabel->setPosition(Vec2(visibleSize.width * 0.23f, visibleSize.height*0.32f));
	statusLabel->setPosition(Vec2(visibleSize.width * 0.23f, visibleSize.height*0.22f));
	nameLabel->setName("nameLabel");
	statusLabel->setName("statusLabel");
	this->addChild(nameLabel);
	this->addChild(statusLabel);
}

void UpgradeCompleteLayer::update(float delta) {
	
	switch (GameData::getInstance()->getRecentUpgradePhase()) {
	case GameData::UpgradePhase::UPGRADE:
		updateUpgradeInfo();
		break;
	case GameData::UpgradePhase::REPAIR:
		updateRepairInfo();
		break;
	}
}

void UpgradeCompleteLayer::updateRepairInfo() {
	auto nameLabel = (Label*)getChildByName("nameLabel");
	auto statusLabel = (Label*)getChildByName("statusLabel");
	auto upgradeCompleteFrameImage = (Sprite*)getChildByName("upgradeCompleteFrameImage");
	upgradeCompleteFrameImage->setTexture(ImagePath::REPAIR_COMPLETE_POPUP_FRAME_PATH);
	switch (GameData::getInstance()->getUpgradeItemMode()) {
	case GameData::ItemMode::SWORD:
		nameLabel->setString(StringUtils::format("무기 이름 : %s", GameData::getInstance()->getSword()->getName().c_str()));
		statusLabel->setString(StringUtils::format("수리 결과: %d", GameData::getInstance()->getSword()->getDamage()));
		break;
	case GameData::ItemMode::SHIELD:
		nameLabel->setString(StringUtils::format("방패 이름 : %s", GameData::getInstance()->getShield()->getName().c_str()));
		statusLabel->setString(StringUtils::format("수리 결과 : %d", GameData::getInstance()->getShield()->getDefense()));
		break;
	}
}

void UpgradeCompleteLayer::updateUpgradeInfo() {
	auto nameLabel = (Label*)getChildByName("nameLabel");
	auto statusLabel = (Label*)getChildByName("statusLabel");
	auto upgradeCompleteFrameImage = (Sprite*)getChildByName("upgradeCompleteFrameImage");
	upgradeCompleteFrameImage->setTexture(ImagePath::UPGRADE_COMPLETE_POPUP_FRAME_PATH);
	switch (GameData::getInstance()->getUpgradeItemMode()) {
	case GameData::ItemMode::SWORD:
		nameLabel->setString(StringUtils::format("무기 이름 : %s", GameData::getInstance()->getSword()->getName().c_str()));
		statusLabel->setString(StringUtils::format("공격력: %d", GameData::getInstance()->getSword()->getDamage()));
		break;
	case GameData::ItemMode::SHIELD:
		nameLabel->setString(StringUtils::format("방패 이름 : %s", GameData::getInstance()->getShield()->getName().c_str()));
		statusLabel->setString(StringUtils::format("방어력 : %d", GameData::getInstance()->getShield()->getDefense()));
		break;
	}
}

void UpgradeCompleteLayer::confirmCallback(cocos2d::Ref* pSender) {
	this->setVisible(false);
}
