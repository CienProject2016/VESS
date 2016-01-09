#pragma once
#include "Unit.h"
#ifndef __MONSTER_H__
#define __MONSTER_H__
class Monster : public Unit {
private:
	int monsterNumber;

public:
	Monster();
	~Monster();
	void createMonster(int);
};
#endif