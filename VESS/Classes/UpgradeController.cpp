#include "UpgradeController.h"
#include "GameData.h"

bool UpgradeController::payUpgradeCosts(int neededGold, Item::Type itemType) { //pay money
	int currentGold = GameData::getInstance()->getGold();
	log("Upgrade Complete");
	if (currentGold >= neededGold) {
		GameData::getInstance()->setGold(currentGold - neededGold);
		return true;
	}
	return false;	
}

bool UpgradeController::upgradeItem() {
	switch (GameData::getInstance()->getItemMode()) {
	case GameData::ItemMode::SWORD:
		upgradeShield();
		break;
	case GameData::ItemMode::SHIELD:
		log("ShieldUpgradePhase");
		upgradeSword();		
		break;
	default : 
		log("Item Mode 정보 오류");
		return false;
	}
	return true;
}

bool UpgradeController::repairItem() {
	switch (GameData::getInstance()->getItemMode()) {
	case GameData::ItemMode::SWORD:
		repairShield();
		break;
	case GameData::ItemMode::SHIELD:
		repairShield();
		break;
	default:
		log("Item Mode 정보 오류2");
		return false;
	}
	return true;
}

void UpgradeController::upgradeSword() {
	Sword& oldSword = GameData::getInstance()->getSword();
	
	rapidjson::Document& upgradeSwordInfo = GameData::getInstance()->getUpgradeSwordInfo();
	string upgradeId = to_string(oldSword.getUpgradeId() + 1);
	if (upgradeSwordInfo["sword"][upgradeId.c_str()] != NULL) {
		auto& upgradeSwordData = upgradeSwordInfo["sword"][upgradeId.c_str()];
		Sword newSword;
		newSword.setName(upgradeSwordData["name"].GetString());
		newSword.setSpeed(upgradeSwordData["speed"].GetInt());
		newSword.setDamage(upgradeSwordData["damage"].GetInt());
		newSword.setUpgradeId(oldSword.getUpgradeId() + 1);
		GameData::getInstance()->setSword(newSword);
	}	
}

void UpgradeController::repairSword() {
	Sword& oldSword = GameData::getInstance()->getSword();
	oldSword.setDurability(oldSword.getMaxDurability());
	GameData::getInstance()->setSword(oldSword);
}

void UpgradeController::repairShield() {
	Shield& oldShield = GameData::getInstance()->getShield();
	oldShield.setDurability(oldShield.getMaxDurability());
	GameData::getInstance()->setShield(oldShield);
}

void UpgradeController::upgradeShield() {
	Shield& oldShield = GameData::getInstance()->getShield();

	rapidjson::Document& upgradeShieldInfo = GameData::getInstance()->getUpgradeShieldInfo();
	string upgradeId = to_string(oldShield.getUpgradeId() + 1);
	if (upgradeShieldInfo["방패"][upgradeId.c_str()] != NULL) {
		auto& upgradeShieldData = upgradeShieldInfo["방패"][upgradeId.c_str()];
		Shield newShield;
		newShield.setName(upgradeShieldData["name"].GetString());
		newShield.setSpeed(upgradeShieldData["speed"].GetInt());
		newShield.setDefense(upgradeShieldData["defense"].GetInt());
		newShield.setUpgradeId(oldShield.getUpgradeId() + 1);
		GameData::getInstance()->setShield(newShield);
	}
}

bool UpgradeController::payRepairCosts(int neededGold, Item::Type itemType) {
	int currentGold = GameData::getInstance()->getGold();
	if (currentGold >= neededGold) {
		GameData::getInstance()->setGold(currentGold - neededGold);
		return true;
	}
	return false;

	//TODO 수리 로직 필요
	if (itemType == Item::Type::SWORD) {

	}
	else {

	}
}