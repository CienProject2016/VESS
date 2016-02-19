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
	CC_SYNTHESIZE(vector<int>, monsterLengthInfo, MonsterLengthInfo); //Json������ ������ �� �ִ��� ����
	CC_SYNTHESIZE(int, gold, Gold);
	CC_SYNTHESIZE(int, health, Health);

};

#endif