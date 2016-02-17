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
private:
	CC_SYNTHESIZE(int, stage_level_, StageLevel);
	CC_SYNTHESIZE(vector<int>, monster_length_info_, MonsterLengthInfo); //Json구조로 가져올 수 있는지 문제
};

#endif