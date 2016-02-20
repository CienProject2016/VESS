#pragma once
#ifndef __STAGE_H__
#define __STAGE_H__

#include "cocos2d.h"
#include <vector>

using namespace std;
class Stage
{
public:
	Stage();
	~Stage();
	int getFinalDistance();
private:
	CC_SYNTHESIZE(vector<int>, monsterLengthInfo, MonsterLengthInfo); //Json구조로 가져올 수 있는지 문제
	CC_SYNTHESIZE(int, gold, Gold);
	CC_SYNTHESIZE(int, health, Health);
	CC_SYNTHESIZE(bool, isClear, IsClear);
	CC_SYNTHESIZE(bool, key, Key);

};

#endif