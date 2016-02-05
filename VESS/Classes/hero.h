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
	Size window_size;				//���̾� ������ ������
	Vec2 origin;					//���̾��� ��ġ ��ǥ
	timeline::ActionTimeline* action;

	float avoidDistance;			//���Ҷ� ������ �������� �Ÿ�
	float attackDistance;			//������ ����� �������� �Ÿ�

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
	void getDamage(bool damage);
	int numGetDamage = 0;

	void setMovementState(HeroMovementState* state);
};
#endif