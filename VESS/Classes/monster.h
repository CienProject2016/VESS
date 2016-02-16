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

	// ���� �� ������ ���� �������� �ֱ� ������ public ���� �ΰ� ���� ���� �� �ֵ��� ����.
	// �ƿ� �ٸ� Ŭ�������� �̵��� �� �� �ִٴ� ������ ������, ���� �� ������ ������ ��� ���� �� ������?
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





//��ü�� �������� ����. �׳� ���ϸ� ��. (Controller)
class MonsterInfo {
private: 
	MonsterInfo();
public:
	static int getHp(Monster::Name name);
};







//��ü�� ���� �� �ش� ���Ͱ� ���� ����. �ֳ��ϸ�, class M.B.P. ���� update �� ����Ǹ�, ������ �ٲپ�� �ϱ� ����.
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