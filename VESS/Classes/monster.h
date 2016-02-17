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





//객체를 생성하지 않음. 그냥 리턴만 함. (Controller)
class MonsterInfo {
private: 
	MonsterInfo();
public:
	static int getHp(Monster::Kind kind);
};







//객체를 생성 후 해당 몬스터가 갖고 있음. 왜냐하면, class M.B.P. 내에 update 가 실행되며, 패턴을 바꾸어야 하기 때문.
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