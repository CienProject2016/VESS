#include "Unit.h"

#ifndef __HERO_H__
#define __HERO_H__

class Hero: public Unit {

public:
	Hero();
	~Hero();
	virtual int getHP();
	virtual void setHP();
};
#endif