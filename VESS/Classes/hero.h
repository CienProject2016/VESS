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
	const int SIZE_OF_LIFE = 3;
	int numGetDamage = 0;
	HeroMovementState* movementState;
	FightLayer* field;
	Size windowSize;				//레이어 윈도우 사이즈
	Vec2 origin;					//레이어의 위치 좌표
	timeline::ActionTimeline* action;
	float DistanceOfAvoid;			//피할때 어디까지 피할지의 거리
	float DistanceOfAttack;			//때릴때 어디쯤 때릴지의 거리

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
	void attackEffect();
	void getDamage(bool damage);
	

	void setMovementState(HeroMovementState* state);
};
#endif