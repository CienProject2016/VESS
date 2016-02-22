#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include <string>
using namespace std;
#include "cocos2d.h"

class Item {
public:
	enum Type { SWORD, SHIELD };
	enum Grade { A=10, B=7 ,C=5 };
	Item();
	~Item();
protected :
	CC_SYNTHESIZE(int, speed, Speed);
	CC_SYNTHESIZE(int, upgradeId, UpgradeId);
	CC_SYNTHESIZE(string, name, Name);
	CC_SYNTHESIZE(int, durability, Durability);
	CC_SYNTHESIZE(int, maxDurability, MaxDurability);
	CC_SYNTHESIZE(int, upgradeGold, UpgradeGold);
	CC_SYNTHESIZE(int, repairGold, RepairGold);
	Type itemType;	
};

#endif

