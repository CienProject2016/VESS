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
public:
	enum Name { Tauren, Slime };

	// 밑의 두 변수는 서로 연관성이 있기 때문에 public 으로 두고 서로 읽을 수 있도록 했음.
	// 아에 다른 클래스에서 이들을 볼 수 있다는 단점이 있지만, 봐도 뭐 쓰지만 않으면 상관 없을 것 같은데?
	MonsterAnimation* anim;
	MonsterBehaviorPattern* pattern;

	static Monster* create(FightLayer* layer, Monster::Name);

	void dropItem();
	void damage(int dam);
	virtual void update(float delta);
	Name kind;
private:
	FightLayer* field;
	void init(FightLayer* layer, Monster::Name);
	void initWindowSize();
	void initHp(Monster::Name name);
	void initImage(Monster::Name name);
	Node* image;
	Size windowSize;
	Vec2 origin;
	Monster();
	~Monster();

};





//객체를 생성하지 않음. 그냥 리턴만 함. (Controller)
class MonsterInfo {
private: 
	MonsterInfo();
public:
	static int getHp(Monster::Name name);
};







//객체를 생성 후 해당 몬스터가 갖고 있음. 왜냐하면, class M.B.P. 내에 update 가 실행되며, 패턴을 바꾸어야 하기 때문.
class MonsterBehaviorPattern {
private:
	Monster* monster;
	MonsterBehaviorPattern();
	enum MonsterState { stand, attack0, attack1, attack2, attack3, dead };
public:
	MonsterBehaviorPattern(Monster* parent);
	bool isStandState();
	void update(float delta);
};






class MonsterAnimation {
private:
	RepeatForever* makeAction(char** plist, int plistCount, int imageCount, char* imageName, float frameTime);
	Monster* monster;
	MonsterAnimation();
public:
	MonsterAnimation(Monster* monster, Monster::Name);
	void playAttack(int num);
	void playDamage();
	void playDead();
};

#endif // __MONSTER_H__