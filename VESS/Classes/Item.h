#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include <string>
using namespace std;
#include "cocos2d.h"

class Item {
public:
	enum Type { SWORD, SHIELD };
	Item();
	~Item();
protected :
	CC_SYNTHESIZE(int, speed, Speed);
	CC_SYNTHESIZE(int, upgradeId, UpgradeId);
	CC_SYNTHESIZE(string, name, Name);
	CC_SYNTHESIZE(int, durability, Durability);
	CC_SYNTHESIZE(int, maxDurability, MaxDurability);
	Type itemType;	
};

#endif

