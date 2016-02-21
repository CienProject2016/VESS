
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
	bool isAvailableCommand();
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
private:
	HitArea* heroPosition;
	const int SIZE_OF_LIFE = 3;
	HeroMovementState* movementState;
	FightLayer* field;
	Size windowSize;				//���̾� ������ ������
	Vec2 origin;					//���̾��� ��ġ ��ǥ
	Node* actionNode, *itemNode;
	timeline::ActionTimeline* action, *itemAction;
	float avoidDistance;			//���Ҷ� ������ �������� �Ÿ�
	float attackDistance;			//������ ����� �������� �Ÿ�
};
#endif