#pragma once
#ifndef __SHIELD_H__
#define __SHEILD_H__
#include "item.h"
#include "cocos2d.h"
class Shield : public Item {
private:
	CC_SYNTHESIZE(int, defense, Defense);
public:
	Shield();
	~Shield();
};
#endif