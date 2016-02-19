#include "Unit.h"
#include "WindowSize.h"
#include "cocostudio\CocoStudio.h"
#include "HeroMovementState.h"
#include "SimpleAudioEngine.h"

#ifndef __HERO_H__
#define __HERO_H__

using namespace cocostudio;


class FightLayer;
class HitArea;

class Hero: public Unit {
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
	void setHitArea(int area);
	void monsterAttackToHero(HitArea* attackArea);
private:
	HitArea* heroPosition;
	const int SIZE_OF_LIFE = 3;
	int numGetDamage = 0;
	HeroMovementState* movementState;
	FightLayer* field;
	Size windowSize;				//���̾� ������ ������
	Vec2 origin;					//���̾��� ��ġ ��ǥ
	timeline::ActionTimeline* action;
	float avoidDistance;			//���Ҷ� ������ �������� �Ÿ�
	float attackDistance;			//������ ����� �������� �Ÿ�

};
#endif