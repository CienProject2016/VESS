#include "unit.h"
#ifndef __HERO_H__
#define __HERO_H__
class Hero: public Unit {
private:
	int monsterNumber;
	double monsterHP;

public:
	Hero();
	~Hero();
	virtual void getHP();
	virtual void setHP();
};
#endif