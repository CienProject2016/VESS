#include "GameData.h"

GameData* GameData::instance_ = nullptr;

GameData::GameData() : isPause(false), isInTutorial(false), isTutorial(false), topStage(0), stageLevel(0), movingDistance(0), sword(), shield(), itemMode(ItemMode::SWORD), stage(), gold(15), costume(0), key(1)
{


	//대화 정보 설정
	setDialogInfo();

	setStageInfo();

	//강화 정보 설정
	setUpgradeInfo();

	setTutorialInfo();

	//저장된 정보 불러옴
	loadSaveInfo();
}

void GameData::resetInfo() {
	log("Game Reset");
	topStage = 0;
	gold = 15;
	UserDefault::getInstance()->reset();
	setUpgradeInfo();	
}

void GameData::loadSaveInfo() {
	if (UserDefault::getInstance()->isXMLFileExist()){
		if (topStage != 0) {
			this->topStage = UserDefault::getInstance()->getIntegerForKey("topStageLevel");
			this->gold = UserDefault::getInstance()->getIntegerForKey("gold");
			sword->setUpgradeId(UserDefault::getInstance()->getIntegerForKey("swordUpgradeGold"));
			sword->setDamage(UserDefault::getInstance()->getIntegerForKey("swordDamage"));
			sword->setDurability(UserDefault::getInstance()->getIntegerForKey("swordDurability"));
			sword->setMaxDurability(UserDefault::getInstance()->getIntegerForKey("swordMaxDurability"));
			sword->setRepairGold(UserDefault::getInstance()->getIntegerForKey("swordRepairGold"));
			sword->setUpgradeGold(UserDefault::getInstance()->getIntegerForKey("swordUpgradeGold"));
			sword->setSpeed(UserDefault::getInstance()->getIntegerForKey("swordSpeed"));
			sword->setName(UserDefault::getInstance()->getStringForKey("swordName"));
			shield->setUpgradeId(UserDefault::getInstance()->getIntegerForKey("shieldUpgradeGold"));
			shield->setRepairPercent(UserDefault::getInstance()->getIntegerForKey("shieldRepairPercent"));
			shield->setUpgradePercent(UserDefault::getInstance()->getIntegerForKey("shieldUpgradePercent"));
			shield->setDurability(UserDefault::getInstance()->getIntegerForKey("shieldDurability"));
			shield->setMaxDurability(UserDefault::getInstance()->getIntegerForKey("shieldMaxDurability"));
			shield->setRepairGold(UserDefault::getInstance()->getIntegerForKey("shieldRepairGold"));
			shield->setUpgradeGold(UserDefault::getInstance()->getIntegerForKey("shieldUpgradeGold"));
			shield->setName(UserDefault::getInstance()->getStringForKey("shieldName"));
		}		
	}
}

Stage GameData::getCurrentStageInfo() {
	return this->getStageList()->at(this->stageLevel);
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
			tutorial.setLines("");
		}
		else {
			tutorial.setLines((*iter)["lines"].GetString());
		}
		if ((*iter)["eventType"] == NULL) {
			log("GameData - Dialog lines정보 없음");
			tutorial.setEventType("");
		}
		else {
			tutorial.setEventType((*iter)["eventType"].GetString());
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
	rapidjson::Value& upgradeShieldData = upgradeShieldInfo["shield"];

	for (rapidjson::Value* iter = upgradeShieldData.Begin(); iter != upgradeShieldData.End(); iter++) {
		Shield* shield = new Shield();
		shield->setName((*iter)["name"].GetString());
		shield->setMaxDurability((*iter)["durability"].GetInt());
		shield->setDurability((*iter)["durability"].GetInt());
		shield->setUpgradeGold((*iter)["upgradeGold"].GetInt());
		shield->setRepairGold((*iter)["repairGold"].GetInt());
		shield->setRepairPercent((*iter)["repairPercent"].GetInt());
		shield->setUpgradePercent((*iter)["upgradePercent"].GetInt());
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