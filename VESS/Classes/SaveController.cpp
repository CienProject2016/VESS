#include "SaveController.h"
#include "GameData.h"

void SaveController::save() {
	int topStageLevel = GameData::getInstance()->getTopStage();
	int gold = GameData::getInstance()->getGold();
	
	int shieldId = GameData::getInstance()->getShield()->getUpgradeId();
	UserDefault::getInstance()->setIntegerForKey("topStageLevel", topStageLevel);
	UserDefault::getInstance()->setIntegerForKey("gold", gold);
	
	saveSword();

	UserDefault::getInstance()->setIntegerForKey("shieldId", shieldId);
	UserDefault::getInstance()->flush();
}

void saveSword() {
	int swordId = GameData::getInstance()->getSword()->getUpgradeId();
	int swordDamage = GameData::getInstance()->getSword()->getDamage();
	int swordDurability = GameData::getInstance()->getSword()->getDurability();
	int swordMaxDurability = GameData::getInstance()->getSword()->getMaxDurability();
	UserDefault::getInstance()->setIntegerForKey("swordId", swordId);
	UserDefault::getInstance()->setIntegerForKey("swordDamage", swordDamage);
	UserDefault::getInstance()->setIntegerForKey("swordDurability", swordDurability);
	UserDefault::getInstance()->setIntegerForKey("swordMaxDurability", swordMaxDurability);
}

void saveShield() {
	int shieldId = GameData::getInstance()->getShield()->getUpgradeId();
	int shieldDurability = GameData::getInstance()->getShield()->getDurability();
	int shieldMaxDurability = GameData::getInstance()->getShield()->getMaxDurability();
	UserDefault::getInstance()->setIntegerForKey("shieldId", shieldId);
	UserDefault::getInstance()->setIntegerForKey("shieldDurability", shieldDurability);
	UserDefault::getInstance()->setIntegerForKey("shieldMaxDurability", shieldMaxDurability);
}

void saveGold() {
	int gold = GameData::getInstance()->getGold();
	UserDefault::getInstance()->setIntegerForKey("gold", gold);
}