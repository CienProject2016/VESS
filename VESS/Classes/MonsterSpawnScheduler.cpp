#include "MonsterSpawnScheduler.h"

//거리정보와 플레이어의 이동거리정보가 일치하면 TRUE를 리턴한다.
bool MonsterSpawnScheduler::isMonsterSpawnTime(int movingDistance, vector<int> distanceData)
{
	vector<int>::iterator iterator;
	for (iterator = distanceData.begin(); iterator != distanceData.end(); ++iterator){
		if (*iterator == movingDistance) {
			return true;
		}
	}
	return false;
}