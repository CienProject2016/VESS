#include "Unit.h"
#include "WindowSize.h"
#include "cocostudio\CocoStudio.h"



#ifndef __HERO_MOVEMENT_STATE__
#define __HERO_MOVEMENT_STATE__

using namespace cocostudio;

class Hero;

class HeroMovementState {
protected:
	float maxTime;
	float timer;
	float verticalVelocity;
	Hero* parent;
	float gravity;
	float moveDistance;
public:
	HeroMovementState();
	virtual void update(float delta);
	void setGravity();
	void setVerticalVelocity();
	void initPos();
	virtual bool isAvailableCommand();
};



class StayMovementState : public HeroMovementState {
public:
	StayMovementState(Hero* parent);
	virtual bool isAvailableCommand();
};

class JumpMovementState : public HeroMovementState {
public:
	JumpMovementState(Hero* parent);
	virtual void update(float delta);
};

class AttackMovementState : public HeroMovementState {
public:
	int direction;
	AttackMovementState(Hero* parent);
	virtual void update(float delta);
	void attackEvent();
};

class AvoidMovementState : public HeroMovementState {
public:
	int direction;
	AvoidMovementState(Hero* parent);
	virtual void update(float delta);
};

class SitdownMovementState : public HeroMovementState {
public:
	SitdownMovementState(Hero* parent);
	virtual void update(float delta);
};

#endif