#include "Unit.h"

#ifndef __HERO_H__
#define __HERO_H__

class Hero: public Unit {

public:
	static Hero* create();
	virtual bool init();
};
#endif