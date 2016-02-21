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
	UserDefault::getInstance()->getIntegerForKey("swordDamage", swordDamage);
	UserDefault::getInstance()->getIntegerForKey("swordDurability", swordDurability);
	UserDefault::getInstance()->getIntegerForKey("swordMaxDurability", swordMaxDurability);
}