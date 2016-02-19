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

	// ���� �� ������ ���� �������� �ֱ� ������ public ���� �ΰ� ���� ���� �� �ֵ��� ����.
	// �ƿ� �ٸ� Ŭ�������� �̵��� �� �� �ִٴ� ������ ������, ���� �� ������ ������ ��� ���� �� ������?
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