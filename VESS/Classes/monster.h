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
private:
	FightLayer* field;
	void init(FightLayer* layer, Monster::Kind);
	void initWindowSize();
	void initHp();
	void initImage();
	void initBehavior();
	Size windowSize;
	Vec2 origin;


};





//��ü�� �������� ����. �׳� ���ϸ� ��. (Controller)
class MonsterInfo {
private: 
	MonsterInfo();
public:
	static int getHp(Monster::Kind kind);
};







//��ü�� ���� �� �ش� ���Ͱ� ���� ����. �ֳ��ϸ�, class M.B.P. ���� update �� ����Ǹ�, ������ �ٲپ�� �ϱ� ����.
class MonsterBehaviorPattern {
private:
	float timer;
	float maxTimer;
	Monster* monster;
	MonsterBehaviorPattern();
	enum MonsterState { stand, attack0, attack1, attack2, attack3, dead };
	void decisionBehavior();
	void playAnimationForState();
public:
	MonsterState state;
	MonsterBehaviorPattern(Monster* parent);
	bool isStandState();
	void update(float delta);
};








#endif // __MONSTER_H__