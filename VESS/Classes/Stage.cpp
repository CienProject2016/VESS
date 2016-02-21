#include "Stage.h"

Stage::Stage(): isClear(false), key(false), monsterLengthInfo({100, 300, 530, 730, 900, 1200, 1500, 1700, 2000, 2500}), gold(50), health(50)
{
	
}

Stage::~Stage() 
{

}

int Stage::getFinalDistance() {
	return monsterLengthInfo.back();
}