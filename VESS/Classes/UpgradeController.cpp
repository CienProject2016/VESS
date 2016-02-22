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

bool UpgradeController::upgradeItem(GameData::ItemMode itemMode, Item::Grade upgradeCoefficient) {
	GameData::getInstance()->setRecentUpgradePhase(GameData::UpgradePhase::UPGRADE);
	switch (itemMode) {
	case GameData::ItemMode::SWORD:
		upgradeSword(upgradeCoefficient);
		break;
	case GameData::ItemMode::SHIELD:
		log("ShieldUpgradePhase");
		if (upgradeShield()) {
			return true;
		}
		return false;
		break;
	default : 
		log("Item Mode 정보 오류");
		return false;
	}
	return true;
}

bool UpgradeController::repairItem(GameData::ItemMode itemMode) {
	GameData::getInstance()->setRecentUpgradePhase(GameData::UpgradePhase::REPAIR);
	switch (itemMode) {
	case GameData::ItemMode::SWORD:
		repairSword();
		return true;
		break;
	case GameData::ItemMode::SHIELD:
		if (repairShield()) {
			return true;
		}		
		break;
	default:
		log("Item Mode 정보 오류2");
		return false;
	}	
	return false;
}

void UpgradeController::upgradeSword(Item::Grade upgradeCoefficient) {
	Sword* oldSword = GameData::getInstance()->getSword();

	int upgradeId = oldSword->getUpgradeId() + 1;
	vector<Sword*>* swordList = GameData::getInstance()->getSwordList();
	log("upgrade Sword id : %d", upgradeId);
	if (swordList->size() > upgradeId-1) {
		Sword* newSword = swordList->at(upgradeId-1);
		newSword->setUpgradeId(upgradeId);
		newSword->setDamage(oldSword->getDamage()+((newSword->getDamage())/10)*upgradeCoefficient);
		newSword->setName(newSword->getName());
		newSword->setSpeed(newSword->getSpeed());
		newSword->setMaxDurability(newSword->getMaxDurability());
		newSword->setDurability(newSword->getMaxDurability());
		newSword->setUpgradeGold(newSword->getUpgradeGold());
		newSword->setRepairGold(newSword->getRepairGold());
		GameData::getInstance()->setSword(newSword);
	}	
}

void UpgradeController::repairSword() {
	Sword* oldSword = GameData::getInstance()->getSword();
	oldSword->setDurability(oldSword->getMaxDurability());
	GameData::getInstance()->setSword(oldSword);
}

bool UpgradeController::repairShield() {
	Shield* oldShield = GameData::getInstance()->getShield();
	if (isSuccess(oldShield->getRepairPercent())) {
		Shield* oldShield = GameData::getInstance()->getShield();
		oldShield->setDurability(oldShield->getMaxDurability());
		oldShield->setMaxDurability(oldShield->getMaxDurability());
		return true;
	}	
	return false;
}

bool UpgradeController::upgradeShield() {
	vector<Shield*>* shieldList = GameData::getInstance()->getShieldList();
	Shield* oldShield = GameData::getInstance()->getShield();
	int upgradeId = oldShield->getUpgradeId() + 1;
	if (shieldList->size() > upgradeId-1) {
		if (isSuccess(oldShield->getUpgradePercent())) {
			Shield* newShield = shieldList->at(upgradeId - 1);
			newShield->setUpgradeId(upgradeId);
			newShield->setName(newShield->getName());
			newShield->setMaxDurability(newShield->getMaxDurability()+oldShield->getDurability());
			newShield->setDurability(newShield->getDurability()+oldShield->getDurability());
			newShield->setUpgradeGold(newShield->getUpgradeGold());
			newShield->setRepairGold(newShield->getRepairGold());
			GameData::getInstance()->setShield(newShield);
			return true;
		}		
	}
	return false;
}

bool UpgradeController::isSuccess(int percentRate) {
	if (percentRate == 100) {
		return true;
	}
	return (rand()%100) <= percentRate;
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
