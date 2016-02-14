#include "UpgradeController.h"
#include "GameData.h"

bool UpgradeController::payUpgradeCosts(int neededGold, Item::Type itemType) { //pay money
	int currentGold = GameData::getInstance()->getGold();
	log("Upgrade Complete");
	if (currentGold >= neededGold) {
		GameData::getInstance()->setGold(currentGold - neededGold);
		upgradeSword(); //Ÿ�̹� �������� ���� -> ��ȭ��ư ���� �Ŀ� �Ǿ�� ��
		return true;
	}
	return false;	
}

bool UpgradeController::upgradeItem() {
	switch (GameData::getInstance()->getItemMode()) {
	case GameData::ItemMode::SWORD:
		upgradeSword();
		break;
	case GameData::ItemMode::SHIELD:
		upgradeShield();
		break;
	default : 
		log("Item Mode ���� ����");
		return false;
	}
	return true;
}

void UpgradeController::upgradeSword() {
	Sword& oldSword = GameData::getInstance()->getSword();
	rapidjson::Document& upgradeSwordInfo = GameData::getInstance()->getUpgradeSwordInfo();
	string upgradeId = to_string(oldSword.getUpgradeId() + 1);
	auto& upgradeSwordData = upgradeSwordInfo["sword"][upgradeId.c_str()];
	Sword newSword;
	newSword.setName(upgradeSwordData["name"].GetString());
	newSword.setSpeed(upgradeSwordData["speed"].GetInt());
	newSword.setUpgradeId(oldSword.getUpgradeId() + 1);
	GameData::getInstance()->setSword(newSword);
}

void UpgradeController::upgradeShield() {

}

bool UpgradeController::payRepairCosts(int neededGold, Item::Type itemType) {
	int currentGold = GameData::getInstance()->getGold();
	if (currentGold >= neededGold) {
		GameData::getInstance()->setGold(currentGold - neededGold);
		return true;
	}
	return false;

	//TODO ���� ���� �ʿ�
	if (itemType == Item::Type::SWORD) {

	}
	else {

	}
}