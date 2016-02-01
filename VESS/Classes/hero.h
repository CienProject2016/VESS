#include "Unit.h"
#include "WindowSize.h"
#include "cocostudio\CocoStudio.h"
#include "HeroMovementState.h"

#ifndef __HERO_H__
#define __HERO_H__

using namespace cocostudio;

class FightLayer;

class Hero: public Unit {
private:

	HeroMovementState* movement_state;
	FightLayer* field;
	Size window_size;				//레이어 윈도우 사이즈
	Vec2 origin;					//레이어의 위치 좌표
	timeline::ActionTimeline* action;

public:

	static Hero* create();
	virtual bool init();

	void setParentLayer(FightLayer* layer);

	virtual void update(float dt);
	bool isAvailableCommand();
	void startAttack();
	void startJump();
	void startAvoid();
	void startSitDown();
	void attackDamage();
	void attackEffect();

	void setMovementState(HeroMovementState* state);
};
#endif