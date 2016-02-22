
#ifndef __HERO_H__
#define __HERO_H__

class FightLayer;
class HitArea;

#include "Unit.h"
#include "WindowSize.h"
#include "cocostudio\CocoStudio.h"
#include "HeroMovementState.h"
#include "SimpleAudioEngine.h"
#include "FightLayer.h"
#include "Item.h"

using namespace cocostudio;


class Hero: public Unit {
public:
	static Hero* create();
	virtual bool init();
	void setParentLayer(FightLayer* layer);
	virtual void update(float delta);
	void startAttack();
	void startJump();
	void startAvoid();
	void startDefense();
	void startSitDown();
	void attackDamage();
	void attackEffect(int damage);
	void setMovementState(HeroMovementState* state);
	void setHitArea(int area);
	void monsterAttackToHero(HitArea* attackArea);
	void decreaseHp(int);
	void changeAction(string, int, int);
	void changeItemAction(Item::Type itemType);
	void setAnimation(HeroMovementState::State state);
private:
	int attackCount;
	HitArea* heroPosition;
	const int SIZE_OF_LIFE = 3;
	HeroMovementState* movementState;
	FightLayer* field;
	Size windowSize;				//레이어 윈도우 사이즈
	Vec2 origin;					//레이어의 위치 좌표
	Node* actionNode, *itemNode;
	timeline::ActionTimeline* action, *itemAction;
	float avoidDistance;			//피할때 어디까지 피할지의 거리
	float attackDistance;			//때릴때 어디쯤 때릴지의 거리
};
#endif