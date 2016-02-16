#pragma once
#ifndef __MONSTER_SPAWN_SCHEDULER_H__
#define __MONSTER_SPAWN_SCHEDULER_H__
#include <vector>
using namespace std;
class MonsterSpawnScheduler
{
public:
	static bool isMonsterSpawnTime(int, const vector<int>);
};

#endif