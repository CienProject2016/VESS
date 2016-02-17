#pragma once
#ifndef __MONSTER_ANIMATION_H__
#define __MONSTER_ANIMATION_H__

#include "Monster.h"

class MonsterAnimation {
private:
	void ReadyForPlist(char* plist);
	RepeatForever* makeAction(int imageCount, char* imageName, float frameTime);
	Monster* monster;
	MonsterAnimation();
	RepeatForever *stand, **attack, *damage, *dead;
	int attackCount;
public:
	MonsterAnimation(Monster* monster);
	void playAttack(int num);
	void playDamage();
	void playDead();
	void playStand();
};

#endif // __MONSTER_ANIMATION_H__