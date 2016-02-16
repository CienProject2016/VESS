#include "UpgradeController.h"
#include "GameData.h"
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

void UpgradeController::upgradeSword() {
	Sword oldSword = GameData::getInstance()->getSword();
	
	int upgradeId = oldSword.getUpgradeId() + 1;
	vector<Sword>* swordList = GameData::getInstance()->getSwordList();

	if (swordList->size() < upgradeId) {
		Sword newSword = swordList->at(upgradeId-1);
		GameData::getInstance()->setSword(newSword);
	}	
}

void UpgradeController::upgradeShield() {
	Shield oldShield = GameData::getInstance()->getShield();

	int upgradeId = oldShield.getUpgradeId() + 1;
	vector<Shield>* shieldList = GameData::getInstance()->getShieldList();

	if (shieldList->size() < upgradeId) {
		Shield newShield = shieldList->at(upgradeId - 1);
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
