#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "WindowSize.h"
#include "Unit.h"
#include <string>
#include "cocostudio\CocoStudio.h"
#include "EffectFactory.h"

using namespace std;
using namespace cocostudio;

class FightLayer;

class MonsterAnimation;
class MonsterBehaviorPattern;
class MonsterInfo;

class Monster : public Unit{
protected:
	Monster();
	~Monster();
public:
	enum Kind { Tauren, Slime };

	// 밑의 두 변수는 서로 연관성이 있기 때문에 public 으로 두고 서로 읽을 수 있도록 했음.
	// 아에 다른 클래스에서 이들을 볼 수 있다는 단점이 있지만, 봐도 뭐 쓰지만 않으면 상관 없을 것 같은데?
	MonsterAnimation* anim;
	MonsterBehaviorPattern* behavior;

	static Monster* create(FightLayer* layer, Monster::Kind, int health);

	void dropItem();
	void damage(int dam);
	virtual void update(float delta);
	Sprite * hpBar = Sprite::create("Images/hpBar.png");
	ProgressTimer* hpBarDecreasing = ProgressTimer::create(hpBar);
	Kind kind;
	Node* image;
	timeline::ActionTimeline* csbAction;
	FightLayer* field;
private:
	void init(FightLayer* layer, Monster::Kind, int health);
	void initWindowSize();
	void initHp(int);
	void initImage();
	void initBehavior();
	Size windowSize;
	Vec2 origin;
	void update_forDead(float delta);
	float targetPosition;	// 몬스터 생성시 뒤에서 생성 되었다가, 있어야 할 자리까지 가려고 할 때, 몬스터가 가려고 하는 위치.
	bool isDead;
	void positionUpdate(float delta);
};

#endif // __MONSTER_H__