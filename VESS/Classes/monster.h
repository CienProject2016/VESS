#include "unit.h"
#ifndef __MONSTER_H__
#define __MONSTER_H__
class Monster: public Unit {
private:
	int monsterNumber;
	double monsterHP;

public:
	Monster();
	~Monster();
	virtual void getHP();
	virtual void setHP();
};
#endif