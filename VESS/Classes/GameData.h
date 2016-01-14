#pragma once
#include "cocos2d.h"

class GameData
{
private:
	static GameData* instance_;
	CC_SYNTHESIZE(int, stage_, Stage);
	GameData();
	~GameData();
public:
	static GameData* getInstance();
};