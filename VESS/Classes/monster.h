#pragma once
#include "Unit.h"
#ifndef __MONSTER_H__
#define __MONSTER_H__
class Monster : public Unit {
private:
	int monster_number;

public:
	Monster();
	~Monster();
	void createMonster(int);
};
#endif // __MONSTER_H__