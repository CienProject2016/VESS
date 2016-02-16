#pragma once
#ifndef __UPGRADE_CONTROLLER_H__
#define __UPGRADE_CONTROLLER_H__
#include "Item.h"

class UpgradeController {
private :
	static void upgradeSword();
	static void upgradeShield();
	static string to_string(int);
public:
	static bool upgradeItem();
	static bool payUpgradeCosts(int, Item::Type);	
	static bool payRepairCosts(int, Item::Type);
};

#endif // __UPGRADE_CONTROLLER_H__