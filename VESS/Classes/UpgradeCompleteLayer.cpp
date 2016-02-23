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
	CCLOG("visibleSize : %d", visibleSize.width);
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
	Label* durabilityLabel;
	switch (GameData::getInstance()->getUpgradeItemMode()) {
	case GameData::ItemMode::SWORD:
		nameLabel = Label::createWithSystemFont("", "Arial", 50);
		nameLabel->setString(StringUtils::format("%s : %s", SWORD_NAME, GameData::getInstance()->getSword()->getName().c_str()));
		statusLabel = Label::createWithSystemFont("", "Arial", 50);
		statusLabel->setString(StringUtils::format("%s : %d", ATTACK_NAME, GameData::getInstance()->getSword()->getDamage()));
		durabilityLabel = Label::createWithSystemFont("", "Arial", 50);
		durabilityLabel->setString(StringUtils::format("%s : %d", MAX_DURABILITY_NAME, GameData::getInstance()->getSword()->getMaxDurability()));
		break;
	case GameData::ItemMode::SHIELD:
		nameLabel = Label::createWithSystemFont("", "Arial", 50);
		nameLabel->setString(StringUtils::format("%s : %s", SHIELD_NAME, GameData::getInstance()->getShield()->getName().c_str()));
		statusLabel = Label::createWithSystemFont("", "Arial", 50);
		durabilityLabel = Label::createWithSystemFont("", "Arial", 50);
		durabilityLabel->setString(StringUtils::format("%s : %d", MAX_DURABILITY_NAME, GameData::getInstance()->getShield()->getMaxDurability()));
		break;
	}

	gradeLabel = Label::createWithSystemFont("", "Arial", 50);
	gradeLabel->setColor(Color3B(0, 0, 0));
	gradeLabel->setPosition(Vec2(visibleSize.width * 0.272f, visibleSize.height*0.33f));

	nameLabel->setAnchorPoint(Vec2(0, 0));
	statusLabel->setAnchorPoint(Vec2(0, 0));
	durabilityLabel->setAnchorPoint(Vec2(0, 0));
	nameLabel->setColor(Color3B(0, 0, 0));
	statusLabel->setColor(Color3B(0, 0, 0));
	nameLabel->setPosition(Vec2(visibleSize.width * 0.21f, visibleSize.height*0.26f));
	statusLabel->setPosition(Vec2(visibleSize.width * 0.21f, visibleSize.height*0.22f));
	nameLabel->setName("nameLabel");
	statusLabel->setName("statusLabel");
	durabilityLabel->setName("durabilityLabel");
	durabilityLabel->setPosition(Vec2(visibleSize.width * 0.21f, visibleSize.height * 0.34f));
	durabilityLabel->setColor(Color3B(0, 0, 0));
	this->addChild(gradeLabel);
	this->addChild(durabilityLabel);
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
	auto durabilityLabel = (Label*)getChildByName("durabilityLabel");
	auto upgradeCompleteFrameImage = (Sprite*)getChildByName("upgradeCompleteFrameImage");
	upgradeCompleteFrameImage->setTexture(ImagePath::REPAIR_COMPLETE_POPUP_FRAME_PATH);
	switch (GameData::getInstance()->getUpgradeItemMode()) {
	case GameData::ItemMode::SWORD:

		gradeLabel->setVisible(false);
		nameLabel->setString(StringUtils::format("%s : %s", SWORD_NAME, GameData::getInstance()->getSword()->getName().c_str()));
		durabilityLabel->setString(StringUtils::format("%s : %d", DURABILITY_NAME, GameData::getInstance()->getSword()->getDurability()));
		break;
	case GameData::ItemMode::SHIELD:
		gradeLabel->setVisible(false);
		nameLabel->setString(StringUtils::format("%s : %s", SHIELD_NAME, GameData::getInstance()->getShield()->getName().c_str()));
		durabilityLabel->setString(StringUtils::format("%s : %d", DURABILITY_NAME, GameData::getInstance()->getShield()->getDurability()));
		break;
	}
}

void UpgradeCompleteLayer::updateUpgradeInfo() {
	auto nameLabel = (Label*)getChildByName("nameLabel");
	auto statusLabel = (Label*)getChildByName("statusLabel");
	auto upgradeCompleteFrameImage = (Sprite*)getChildByName("upgradeCompleteFrameImage");
	auto durabilityLabel = (Label*)getChildByName("durabilityLabel");
	upgradeCompleteFrameImage->setTexture(ImagePath::UPGRADE_COMPLETE_POPUP_FRAME_PATH);
	switch (GameData::getInstance()->getUpgradeItemMode()) {
	case GameData::ItemMode::SWORD: {
		string grade = setGrade();
		gradeLabel->setString(StringUtils::format("%s : %s", UPGRADE_GRADE, grade.c_str()));
		gradeLabel->setVisible(true);
		nameLabel->setString(StringUtils::format("%s : %s", SWORD_NAME, GameData::getInstance()->getSword()->getName().c_str()));
		statusLabel->setString(StringUtils::format("%s : %d", ATTACK_NAME, GameData::getInstance()->getSword()->getDamage()));
		durabilityLabel->setString(StringUtils::format("%s : %d", DURABILITY_NAME, GameData::getInstance()->getSword()->getDurability()));

	}
		break;
	case GameData::ItemMode::SHIELD:
		gradeLabel->setVisible(false);
		nameLabel->setString(StringUtils::format("%s : %s", SHIELD_NAME, GameData::getInstance()->getShield()->getName().c_str()));
		durabilityLabel->setString(StringUtils::format("%s : %d", DURABILITY_NAME, GameData::getInstance()->getShield()->getDurability()));

		break;
	}
}

string UpgradeCompleteLayer::setGrade() {
	switch (GameData::getInstance()->getCurrentUpgradeGrade()) {
	case Item::Grade::A:
		return "A";
		break;
	case Item::Grade::B:
		return "B";
		break;
	case Item::Grade::C:
		return "C";
		break;
	}
}

void UpgradeCompleteLayer::confirmCallback(cocos2d::Ref* pSender) {
	this->setVisible(false);
}
