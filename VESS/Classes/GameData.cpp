#include "GameData.h"

GameData* GameData::instance_ = nullptr;

GameData::GameData() : moving_distance(0), itemMode(ItemMode::SWORD), stage(), hero_hp(100), gold(150), costume(0), needed_upgrade_gold(150), needed_repair_gold(15), key(1)
{
	//대화 정보 설정
	setDialogInfo();
	
	//강화 정보 설정
	setUpgradeInfo();
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

void GameData::setDialogInfo() {
	auto dialogFileData = FileUtils::getInstance()->getStringFromFile("json/dialog.json");

	dialogList = new vector<Dialog>();
	rapidjson::Document doc;
	doc.Parse(dialogFileData.c_str());

	rapidjson::Value& data = doc["opening"];

	for (rapidjson::Value* iter = data.Begin(); iter != data.End(); iter++) {
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
		dialogList->push_back(dialog);
	}
}

void GameData::setUpgradeInfo() {
	swordList = new vector<Sword>();
	shieldList = new vector<Shield>();
	
	auto upgradeSwordFileData = FileUtils::getInstance()->getStringFromFile("json/sword.json");


	rapidjson::Document upgradeSwordInfo;
	upgradeSwordInfo.Parse(upgradeSwordFileData.c_str());
	rapidjson::Value& upgradeSwordData = upgradeSwordInfo["sword"];
	

	for (rapidjson::Value* iter = upgradeSwordData.Begin(); iter != upgradeSwordData.End(); iter++) {
		Sword sword;
		sword.setDamage((*iter)["damage"].GetInt());
		sword.setName((*iter)["name"].GetString());
		sword.setSpeed((*iter)["speed"].GetInt());
		swordList->push_back(sword);
	}
	Sword sword = swordList->at(0);
	sword.setUpgradeId(1);	
	this->setSword(sword);

	auto upgradeShieldFileData = FileUtils::getInstance()->getStringFromFile("json/shield.json");

	rapidjson::Document upgradeShieldInfo;
	upgradeShieldInfo.Parse(upgradeShieldFileData.c_str());
	rapidjson::Value& upgradeShieldData = upgradeShieldInfo["방패"];

	for (rapidjson::Value* iter = upgradeShieldData.Begin(); iter != upgradeShieldData.End(); iter++) {
		Shield shield;
		shield.setDefense((*iter)["defense"].GetInt());
		shield.setName((*iter)["name"].GetString());
		shield.setSpeed((*iter)["speed"].GetInt());
		shieldList->push_back(shield);
	}
	Shield shield = shieldList->at(0);
	shield.setUpgradeId(1);
	this->setShield(shield);
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