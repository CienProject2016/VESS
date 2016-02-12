#pragma once
#ifndef __UPGRADE_CONTROLLER_H__
#define __UPGRADE_CONTROLLER_H__
#include "Item.h"

class UpgradeController {
public:
	static bool upgrade(int, Item::Type);
	static bool repair(int, Item::Type);
};

#endif // __UPGRADE_CONTROLLER_H__