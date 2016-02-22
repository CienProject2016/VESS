#pragma once
#ifndef __UPGRADE_CONTROLLER_H__
#define __UPGRADE_CONTROLLER_H__
#include "Item.h"
#include "GameData.h"

class UpgradeController {
private :
	static void upgradeSword(Item::Grade upgradeCoefficient);
	static bool upgradeShield();
	static void repairSword();
	static bool repairShield();
	static bool isSuccess(int);
public:
	static bool upgradeItem(GameData::ItemMode, Item::Grade upgradeCoefficient);
	static bool repairItem(GameData::ItemMode);
	static bool payUpgradeCosts(int, Item::Type);	
	static bool payRepairCosts(int, Item::Type);
};

#endif // __UPGRADE_CONTROLLER_H__