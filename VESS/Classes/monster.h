#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "WindowSize.h"
#include "Unit.h"
#include <string>
#include "cocostudio\CocoStudio.h"

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

	static Monster* create(FightLayer* layer, Monster::Kind);

	void dropItem();
	void damage(int dam);
	virtual void update(float delta);
	Kind kind;
	Node* image;
	FightLayer* field;
private:
	void init(FightLayer* layer, Monster::Kind);
	void initWindowSize();
	void initHp();
	void initImage();
	void initBehavior();
	Size windowSize;
	Vec2 origin;


};

#endif // __MONSTER_H__