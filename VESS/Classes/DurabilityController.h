#pragma once
#ifndef __DURABILITY_CONTROLLER_H__
#define __DURABILITY_CONTROLLER_H__
#include "Item.h"
class DurabilityController {
public:
	static void reduceDurability(Item::Type, int);
	static void increaseDurability(Item::Type, int);
};

#endif
