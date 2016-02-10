#pragma once
#ifndef __SLIME_H__
#define __SLIME_H__

#include "Monster.h"
#include <typeinfo>

class Slime : public Monster {
private:
	RepeatForever* makeAttack1();
	enum SlimeState {STAND, ATTACK0, ATTACK1};
	SlimeState currState;
	void changeState(SlimeState state);
protected:
	Slime();
	virtual void initImage();
	RepeatForever* stand, *attack_00, *attack_01;
public:
	~Slime();
	virtual void update(float delta);
	virtual bool init();
	static Slime* create();
};





#endif		// __SLIME_H__