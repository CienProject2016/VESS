#include "MonsterSpawnScheduler.h"

//�Ÿ������� �÷��̾��� �̵��Ÿ������� ��ġ�ϸ� TRUE�� �����Ѵ�.
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