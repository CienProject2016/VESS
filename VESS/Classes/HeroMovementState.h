#include "Unit.h"
#include "WindowSize.h"
#include "cocostudio\CocoStudio.h"
#include "cocos2d.h"
#include "ActionFrameValue.h"

#ifndef __HERO_MOVEMENT_STATE__
#define __HERO_MOVEMENT_STATE__

USING_NS_CC;

class Hero;


class HeroMovementState {
protected:
	
	float maxTime;
	float timer;
	float verticalVelocity;
	Hero* parent;
	float gravity;
	float movingDistance;
	CC_SYNTHESIZE(ActionFrameValue*, actionFrameValue, ActionFrameValue);
public:
	enum State { attack0, attack1, avoid_up, avoid_left, avoid_down, run, stay, defence };
	State state;
	HeroMovementState();
	virtual void update(float delta);
	void setGravity();
	void setVerticalVelocity();
	void initPos();
};

class RunMovementState : public HeroMovementState {
public :
	RunMovementState(Hero* parent);
};

class StayMovementState : public HeroMovementState {
public:
	StayMovementState(Hero* parent);
};

class JumpMovementState : public HeroMovementState {
public:
	JumpMovementState(Hero* parent);
	virtual void update(float delta);
};

class AttackMovementState : public HeroMovementState {
private:
	int direction;
public:
	AttackMovementState(Hero* parent);
	virtual void update(float delta);
	void attackEvent();
};

class AvoidMovementState : public HeroMovementState {
private:
	int direction;
public:
	AvoidMovementState(Hero* parent);
	virtual void update(float delta);
};

class SitdownMovementState : public HeroMovementState {
public:
	SitdownMovementState(Hero* parent);
	virtual void update(float delta);
};

#endif