#include "GameData.h"

GameData* GameData::instance_ = nullptr;

GameData::GameData() : moving_distance_(0), itemMode(ItemMode::SWORD), stage_(), hero_hp_(100), gold_(150), costume_(0), needed_upgrade_gold_(150), needed_repair_gold_(15), upgradeSwordInfo()
{
	//대화 정보 설정
	setDialogInfo();
	
	//강화 정보 설정
	setUpgradeInfo();

	setTutorialInfo();
}

GameData::~GameData()
{

}

GameData* GameData::getInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new GameData();
	}
	return instance_;
}

void GameData::setTutorialInfo() {
	auto tutorialFileData = FileUtils::getInstance()->getStringFromFile("json/tutorial.json");

	tutorialList_ = new vector<Tutorial>();
	rapidjson::Document doc;
	doc.Parse(tutorialFileData.c_str());

	auto& data = doc["opening"];

	for (auto iter = data.Begin(); iter != data.End(); iter++) {
		Tutorial tutorial;
		
		
		if ((*iter)["lines"] == NULL) {
			log("GameData - Dialog lines정보 없음");
			tutorial.setTutorial("");
		}
		else {
			tutorial.setTutorial((*iter)["lines"].GetString());
		}
		tutorialList_->push_back(tutorial);
	}
}
void GameData::setDialogInfo() {
	auto dialogFileData = FileUtils::getInstance()->getStringFromFile("json/dialog.json");

	dialogList_ = new vector<Dialog>();
	rapidjson::Document doc;
	doc.Parse(dialogFileData.c_str());

	auto& data = doc["opening"];

	for (auto iter = data.Begin(); iter != data.End(); iter++) {
		Dialog dialog;
		if ((*iter)["name"] == NULL) {
			dialog.setName("");
			log("GameData - Dialog 이름 정보 없음");
		}
		else {
			dialog.setName((*iter)["name"].GetString());
		}
		if ((*iter)["image"] == NULL) {
			dialog.setImage("no_image");
			log("GameData - Dialog image 정보 없음");
		}
		else {
			dialog.setImage((*iter)["image"].GetString());
		}

		if ((*iter)["position"] == NULL) {
			dialog.setPosition(Dialog::Position::RIGHT);
			log("GameData - Dialog position 정보 없음");
		}
		else {
			if ((*iter)["position"] == "left") {
				dialog.setPosition(Dialog::Position::LEFT);
			}
			else {
				dialog.setPosition(Dialog::Position::RIGHT);
			}
		}

		if ((*iter)["lines"] == NULL) {
			log("GameData - Dialog lines정보 없음");
			dialog.setDialogue("");
		}
		else {
			dialog.setDialogue((*iter)["lines"].GetString());
		}
		dialogList_->push_back(dialog);
	}
}

void GameData::setUpgradeInfo() {
	auto upgradeSwordFileData = FileUtils::getInstance()->getStringFromFile("json/sword.json");

	upgradeSwordInfo.Parse(upgradeSwordFileData.c_str());
	auto& upgradeSwordData = upgradeSwordInfo["sword"]["1"];
	Sword sword;
	sword.setDamage(upgradeSwordData["damage"].GetInt());
	sword.setName(upgradeSwordData["name"].GetString());
	sword.setSpeed(upgradeSwordData["speed"].GetInt());
	sword.setUpgradeId(1);
	this->setSword(sword);

	auto upgradeShieldFileData = FileUtils::getInstance()->getStringFromFile("json/shield.json");

	upgradeShieldInfo.Parse(upgradeShieldFileData.c_str());
	auto& upgradeShieldData = upgradeShieldInfo["방패"]["1"];
	Shield shield;
	shield.setDefense(upgradeShieldData["defense"].GetInt());
	shield.setName(upgradeShieldData["name"].GetString());
	shield.setSpeed(upgradeShieldData["speed"].GetInt());
	shield.setUpgradeId(1);
	this->setShield(shield);
}

rapidjson::Document& GameData::getUpgradeSwordInfo() {
	return upgradeSwordInfo;
}

rapidjson::Document& GameData::getUpgradeShieldInfo() {
	return upgradeShieldInfo;
}

void GameData::setItemMode(ItemMode itemMode) {
	this->itemMode = itemMode;
}

GameData::ItemMode GameData::getItemMode() {
	return this->itemMode;
}

GameData::ItemMode GameData::getUpgradeItemMode() {
	if (this->itemMode == GameData::ItemMode::SWORD) {
		return GameData::ItemMode::SHIELD;
	}
	else {
		return GameData::ItemMode::SWORD;
	}
}