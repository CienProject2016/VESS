#pragma once
#ifndef __SWORD_H__
#define __SWORD_H__
#include "Item.h"

class Sword : public Item {
private:
	CC_SYNTHESIZE(int, damage, Damage);
public:
	enum SwordType { Gum };
	Sword();
	~Sword();
};

#endif

