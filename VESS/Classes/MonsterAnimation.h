#pragma once
#ifndef __MONSTER_ANIMATION_H__
#define __MONSTER_ANIMATION_H__

#include "Monster.h"

class MonsterAnimation {
private:
	enum animKind {stand, attack0, attack1, attack2, attack3, dead, damage};
	void ReadyForPlist(char* plist);
	RepeatForever* makeAction(int imageCount, char* imageName, float frameTime);
	RepeatForever* makeAction(animKind kind);
	Monster* monster;
	MonsterAnimation();

	int attackCount;
	void changeAction(animKind kind);

public:
	MonsterAnimation(Monster* monster);
	void playAttack(int num);
	void playDamage();
	void playDead();
	void playStand();
};

#endif // __MONSTER_ANIMATION_H__