#include "MonsterSpawnScheduler.h"

//거리정보와 플레이어의 이동거리정보가 일치하면 TRUE를 리턴한다.
bool MonsterSpawnScheduler::isMonsterSpawnTime(int movingDistance, int number)
{
	vector<int> distanceData;
	for (int i = 1; i <= number-1; i++) {
		distanceData.push_back(i * 200); // 200 마다 몬스터 리스폰.
	}
	vector<int>::iterator iterator;
	for (iterator = distanceData.begin(); iterator != distanceData.end()-1; ++iterator){
		if (*iterator == movingDistance) {
			return true;
		}
	}
	return false;
}