#include "UpgradeController.h"

#include <sstream>

bool UpgradeController::payUpgradeCosts(int neededGold, Item::Type itemType) { //pay money
	int currentGold = GameData::getInstance()->getGold();
	log("Upgrade Complete");
	if (currentGold >= neededGold) {
		GameData::getInstance()->setGold(currentGold - neededGold);
		return true;
	}

	return false;	
}

bool UpgradeController::upgradeItem(GameData::ItemMode itemMode) {
	switch (itemMode) {
	case GameData::ItemMode::SWORD:
		upgradeSword();
		break;
	case GameData::ItemMode::SHIELD:
		log("ShieldUpgradePhase");
		upgradeShield();		
		break;
	default : 
		log("Item Mode 정보 오류");
		return false;
	}
	GameData::getInstance()->setRecentUpgradePhase(GameData::UpgradePhase::UPGRADE);
	return true;
}

bool UpgradeController::repairItem(GameData::ItemMode itemMode) {
	switch (itemMode) {
	case GameData::ItemMode::SWORD:
		repairSword();
		break;
	case GameData::ItemMode::SHIELD:
		repairShield();
		break;
	default:
		log("Item Mode 정보 오류2");
		return false;
	}
	GameData::getInstance()->setRecentUpgradePhase(GameData::UpgradePhase::REPAIR);
	return true;
}

void UpgradeController::upgradeSword() {
	Sword* oldSword = GameData::getInstance()->getSword();
	
	int upgradeId = oldSword->getUpgradeId() + 1;
	vector<Sword*>* swordList = GameData::getInstance()->getSwordList();
	log("upgrade Sword id : %d", upgradeId);
	if (swordList->size() > upgradeId-1) {
		Sword* newSword = swordList->at(upgradeId-1);
		newSword->setUpgradeId(upgradeId);
		GameData::getInstance()->setSword(newSword);
	}	
}

void UpgradeController::repairSword() {
	Sword* oldSword = GameData::getInstance()->getSword();
	oldSword->setDurability(oldSword->getMaxDurability());
	GameData::getInstance()->setSword(oldSword);
}

void UpgradeController::repairShield() {
	Shield* oldShield = GameData::getInstance()->getShield();
	oldShield->setDurability(oldShield->getMaxDurability());
	GameData::getInstance()->setShield(oldShield);
}

void UpgradeController::upgradeShield() {
	Shield* oldShield = GameData::getInstance()->getShield();

	int upgradeId = oldShield->getUpgradeId() + 1;
	vector<Shield*>* shieldList = GameData::getInstance()->getShieldList();
	log("upgrade SHIELD id : %d", upgradeId);
	if (shieldList->size() > upgradeId-1) {
		Shield* newShield = shieldList->at(upgradeId-1);
		newShield->setUpgradeId(upgradeId);
		GameData::getInstance()->setShield(newShield);
		log("%s", GameData::getInstance()->getShield()->getName().c_str());
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
