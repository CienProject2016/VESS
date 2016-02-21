#pragma once
#ifndef __HERO_H__
#define __HERO_H__

#include "Unit.h"
#include "WindowSize.h"
#include "cocostudio\CocoStudio.h"
#include "HeroMovementState.h"
#include "SimpleAudioEngine.h"

using namespace cocostudio;

class FightLayer;
class EffectController;

class Hero : public Unit {
public:
	static Hero* create();
	virtual bool init();
	void setParentLayer(FightLayer* layer);
	virtual void update(float delta);
	bool isAvailableCommand();
	void startAttack();
	void startJump();
	void startAvoid();
	void startSitDown();
	void attackDamage();
	void attackEffect(int damage);
	void getDamage(bool damage);
	void setMovementState(HeroMovementState* state);
private:
	void checkEffectEnd();
	EffectController* effectController;
	const int SIZE_OF_LIFE = 3;
	int numGetDamage;
	HeroMovementState* movementState;
	bool effectEnd;
	float effectTime = 0;
	FightLayer* field;
	Size windowSize;			
	Vec2 origin;					
	timeline::ActionTimeline* action;
	float avoidDistance;			
	float attackDistance;		
};
#endif