#pragma once
#ifndef __MONSTER_ANIMATION_H__
#define __MONSTER_ANIMATION_H__

#include "Monster.h"
#include "MonsterInfo.h"

class MonsterAnimation {
private:
	void ReadyForPlist(char* plist);
	RepeatForever* makeAction(MakeAnimationInfo* info);
	Monster* monster;
	MonsterAnimation();

	int attackCount;
	void changePlistAction(MonsterInfo::AnimName anim);

public:
	MonsterAnimation(Monster* monster);
	void playAttack(int num);
	void playDamage();
	void playDead();
	void playStand();
};

#endif // __MONSTER_ANIMATION_H__