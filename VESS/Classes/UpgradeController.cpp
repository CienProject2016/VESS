#include "UpgradeController.h"
#include "GameData.h"

bool UpgradeController::upgrade(int neededGold, Item::Type itemType) {
	int currentGold = GameData::getInstance()->getGold();
	log("Upgrade Complete");
	if (currentGold >= neededGold) {
		GameData::getInstance()->setGold(currentGold - neededGold);
		return true;
	}
	return false;

	//TODO ���׷��̵� ���� �ʿ�
	if (itemType == Item::Type::SWORD) {
		
	}
	else {

	}	
}

bool UpgradeController::repair(int neededGold, Item::Type itemType) {
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