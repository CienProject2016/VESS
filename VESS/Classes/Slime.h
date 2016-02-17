#pragma once
#ifndef __SLIME_H__
#define __SLIME_H__

#include "Monster.h"
#include <typeinfo>

class Slime : public Monster {
private:
	RepeatForever* makeAttack1();
	enum SLIME_STATE {STAND, ATTACK0, ATTACK1};
	SLIME_STATE currentState;
	void changeState(SLIME_STATE state);

protected:
	Slime() {}
	virtual void initImage();
	RepeatForever* stand, *attack00, *attack01;
public:

	virtual void update(float delta);
	virtual bool init();
	static Slime* create();
};





#endif		// __SLIME_H__