#include "GameData.h"

GameData* GameData::instance_ = nullptr;

GameData::GameData() : stageLevel(1), moving_distance(0), sword(), shield(), itemMode(ItemMode::SWORD), stage(), hero_hp(100), gold(5), costume(0), needed_upgrade_gold(10), needed_repair_gold(3)
{
	//대화 정보 설정
	setDialogInfo();
	
	setStageInfo();
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

void GameData::setStageInfo() {
	auto stageFileData = FileUtils::getInstance()->getStringFromFile("json/stage.json");
	stageList = new vector<Stage>();
	rapidjson::Document doc;
	doc.Parse(stageFileData.c_str());

	auto& data = doc["stage"];

	for (auto iter = data.Begin(); iter != data.End(); iter++) {
		Stage stage;
		if ((*iter)["gold"] == NULL) {
			log("GameData - Stage gold 정보 없음");
			stage.setGold(1);
		}
		else {
			stage.setGold((*iter)["gold"].GetInt());
		}
		if ((*iter)["health"] == NULL) {
			log("GameData - Stage health 정보 없음");
			stage.setHealth(1);
		}
		else {
			stage.setHealth((*iter)["health"].GetInt());
		}
		stageList->push_back(stage);
	}
}

void GameData::setTutorialInfo() {
	auto tutorialFileData = FileUtils::getInstance()->getStringFromFile("json/tutorial.json");

	tutorialList = new vector<Tutorial>();
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
		tutorialList->push_back(tutorial);
	}
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
	swordList = new vector<Sword*>();
	shieldList = new vector<Shield*>();
	
	auto upgradeSwordFileData = FileUtils::getInstance()->getStringFromFile("json/sword.json");


	rapidjson::Document upgradeSwordInfo;
	upgradeSwordInfo.Parse(upgradeSwordFileData.c_str());
	rapidjson::Value& upgradeSwordData = upgradeSwordInfo["sword"];
	

	for (rapidjson::Value* iter = upgradeSwordData.Begin(); iter != upgradeSwordData.End(); iter++) {
		Sword* sword = new Sword;
		sword->setDamage((*iter)["damage"].GetInt());
		sword->setName((*iter)["name"].GetString());
		sword->setSpeed((*iter)["speed"].GetInt());
		sword->setMaxDurability((*iter)["durability"].GetInt());
		sword->setDurability((*iter)["durability"].GetInt());
		sword->setUpgradeGold((*iter)["upgrade"].GetInt());
		sword->setRepairGold((*iter)["repair"].GetInt());
		swordList->push_back(sword);
	}
	Sword* sword = swordList->at(0);
	sword->setUpgradeId(1);	
	this->setSword(sword);

	auto upgradeShieldFileData = FileUtils::getInstance()->getStringFromFile("json/shield.json");

	rapidjson::Document upgradeShieldInfo;
	upgradeShieldInfo.Parse(upgradeShieldFileData.c_str());
	rapidjson::Value& upgradeShieldData = upgradeShieldInfo["방패"];

	for (rapidjson::Value* iter = upgradeShieldData.Begin(); iter != upgradeShieldData.End(); iter++) {
		Shield* shield = new Shield();
		shield->setDefense((*iter)["defense"].GetInt());
		shield->setName((*iter)["name"].GetString());
		shield->setSpeed((*iter)["speed"].GetInt());
		shield->setMaxDurability((*iter)["durability"].GetInt());
		shield->setDurability((*iter)["durability"].GetInt());
		shield->setUpgradeGold((*iter)["upgrade"].GetInt());
		shield->setRepairGold((*iter)["repair"].GetInt());
		shieldList->push_back(shield);
	}
	Shield* shield = shieldList->at(0);
	shield->setUpgradeId(1);
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