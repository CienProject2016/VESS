#include "SaveController.h"
#include "GameData.h"
#include <string>
using namespace std;

void SaveController::save() {
	saveTopStage();
	saveGold();
	saveSword();
	saveShield();
	UserDefault::getInstance()->flush();
}

void SaveController::saveSword() {
	int swordId = GameData::getInstance()->getSword()->getUpgradeId();
	int swordDamage = GameData::getInstance()->getSword()->getDamage();
	int swordDurability = GameData::getInstance()->getSword()->getDurability();
	int swordMaxDurability = GameData::getInstance()->getSword()->getMaxDurability();
	int swordRepairGold = GameData::getInstance()->getSword()->getRepairGold();
	int swordUpgradeGold = GameData::getInstance()->getSword()->getUpgradeGold();
	int swordSpeed = GameData::getInstance()->getSword()->getSpeed();
	string swordName = GameData::getInstance()->getSword()->getName();
	UserDefault::getInstance()->setIntegerForKey("swordId", swordId);
	UserDefault::getInstance()->setIntegerForKey("swordDamage", swordDamage);
	UserDefault::getInstance()->setIntegerForKey("swordDurability", swordDurability);
	UserDefault::getInstance()->setIntegerForKey("swordMaxDurability", swordMaxDurability);
	UserDefault::getInstance()->setStringForKey("swordName", swordName);
	UserDefault::getInstance()->setIntegerForKey("swordRepairGold", swordRepairGold);
	UserDefault::getInstance()->setIntegerForKey("swordUpgradeGold", swordUpgradeGold);
	UserDefault::getInstance()->setIntegerForKey("swordSpeed", swordSpeed);
}

void SaveController::saveShield() {
	int shieldId = GameData::getInstance()->getShield()->getUpgradeId();
	int shieldDurability = GameData::getInstance()->getShield()->getDurability();
	int shieldMaxDurability = GameData::getInstance()->getShield()->getMaxDurability();
	int shieldRepairGold = GameData::getInstance()->getShield()->getRepairGold();
	int shieldUpgradeGold = GameData::getInstance()->getShield()->getUpgradeGold();
	int shieldRepairPercent = GameData::getInstance()->getShield()->getRepairPercent();
	int shieldUpgradePercent = GameData::getInstance()->getShield()->getUpgradePercent();
	string shieldName = GameData::getInstance()->getShield()->getName();
	UserDefault::getInstance()->setIntegerForKey("shieldId", shieldId);
	UserDefault::getInstance()->setIntegerForKey("shieldDurability", shieldDurability);
	UserDefault::getInstance()->setIntegerForKey("shieldMaxDurability", shieldMaxDurability);
	UserDefault::getInstance()->setStringForKey("shieldName", shieldName);
	UserDefault::getInstance()->setIntegerForKey("shieldRepairGold", shieldRepairGold);
	UserDefault::getInstance()->setIntegerForKey("shieldUpgradeGold", shieldUpgradeGold);
	UserDefault::getInstance()->setIntegerForKey("shieldUpgradePercent",shieldUpgradePercent);
	UserDefault::getInstance()->setIntegerForKey("shieldRepairPercent", shieldRepairPercent);
}

void SaveController::saveGold() {
	int gold = GameData::getInstance()->getGold();
	UserDefault::getInstance()->setIntegerForKey("gold", gold);
}

void SaveController::saveTopStage() {
	int topStageLevel = GameData::getInstance()->getTopStage();
	UserDefault::getInstance()->setIntegerForKey("topStageLevel", topStageLevel);
}