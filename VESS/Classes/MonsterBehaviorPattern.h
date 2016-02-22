#pragma once
#ifndef __MONSTER_BEHAVIOR_PATTERN_H__
#define __MONSTER_BEHAVIOR_PATTERN_H__

#include "Monster.h"

//객체를 생성 후 해당 몬스터가 갖고 있음. 왜냐하면, class M.B.P. 내에 update 가 실행되며, 패턴을 바꾸어야 하기 때문.
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