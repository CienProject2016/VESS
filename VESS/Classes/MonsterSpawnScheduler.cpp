#include "MonsterSpawnScheduler.h"

//거리정보와 플레이어의 이동거리정보가 일치하면 TRUE를 리턴한다.
bool MonsterSpawnScheduler::isMonsterSpawnTime(int moving_distance, vector<int> distance_data)
{
	vector<int>::iterator iterator;
	for (iterator = distance_data.begin(); iterator != distance_data.end(); ++iterator){
		if (*iterator == moving_distance) {
			return true;
		}
	}
	return false;
}