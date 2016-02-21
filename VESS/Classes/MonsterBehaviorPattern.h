#pragma once
#ifndef __MONSTER_BEHAVIOR_PATTERN_H__
#define __MONSTER_BEHAVIOR_PATTERN_H__

#include "Monster.h"

//��ü�� ���� �� �ش� ���Ͱ� ���� ����. �ֳ��ϸ�, class M.B.P. ���� update �� ����Ǹ�, ������ �ٲپ�� �ϱ� ����.
class MonsterBehaviorPattern {
private:
	float timer;
	float maxTimer, attackTimer;
	bool isOneAnimationAttack;
	Monster* monster;
	MonsterBehaviorPattern();
	enum MonsterState { stand, attack0, attack1, attack2, attack3, dead };
	void decisionBehavior();
	void attackToHero();
	void playAnimationForState();
	void setStateAndTimer(MonsterState state, float maxTimer);
	void setStateAndTimer(MonsterState state, float maxTimer, float attackTimer);
public:
	MonsterState state;
	MonsterBehaviorPattern(Monster* parent);
	bool isStandState();
	void update(float delta);
};

#endif // __MONSTER_INFO_H__