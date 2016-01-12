#include "Monster.h"
#include "Unit.h"
#include <iostream>
using namespace std;

Monster::Monster()
{
	cout << "만들 몬스터의 번호를 입력(1번부터 5번까지):";
	cin >> monsterNumber;
	createMonster(monsterNumber);
}

Monster::~Monster()
{}

void Monster::createMonster(int monsterNumber)
{
	double init = 0;
	switch (monsterNumber)
	{
	case 1:
		hp = 10;
		break;
	case 2:
		hp = 100;
		break;
	case 3:
		hp = 1000;
		break;
	case 4:
		hp = 10000;
		break;
	case 5:
		hp = 20000;
		break;

	}
	cout << monsterNumber << "번 몬스터가 생성되었습니다" << endl;
}