#pragma once
#ifndef __UPGRADE_CONTROLLER_H__
#define __UPGRADE_CONTROLLER_H__
#include "Item.h"
#include "GameData.h"

class UpgradeController {
private :
	static void upgradeSword(int upgradeCoefficient);
	static void upgradeShield(int upgradeCoefficient);
	static void repairSword();
	static void repairShield();
public:
	static bool upgradeItem(GameData::ItemMode,int upgradeCoefficient);
	static bool repairItem(GameData::ItemMode);
	static bool payUpgradeCosts(int, Item::Type);	
	static bool payRepairCosts(int, Item::Type);
};

#endif // __UPGRADE_CONTROLLER_H__