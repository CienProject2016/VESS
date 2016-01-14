#pragma once
#include "cocos2d.h"
#include "Stage.h"
#include "Hero.h"

class GameData
{
private:
	static GameData* instance_;
	CC_SYNTHESIZE(Stage, stage_, Stage);
	CC_SYNTHESIZE(int, hero_hp_, HeroHp);
	CC_SYNTHESIZE(int, gold_, Gold);
	CC_SYNTHESIZE(int, costume_, Costume);
	GameData();
	~GameData();
public:
	static GameData* getInstance();
};