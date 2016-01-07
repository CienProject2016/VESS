#include "monster.h"
#include "unit.h"
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
		monsterHP = 10;
		break;
	case 2:
		monsterHP = 100;
		break;
	case 3:
		monsterHP = 1000;
		break;
	case 4:
		monsterHP = 10000;
		break;
	case 5:
		monsterHP = 20000;
		break;

	}
	cout <<monsterNumber<<"번 몬스터가 생성되었습니다"<<endl;
	showMonsterHP(init);


}
void Monster::showMonsterHP(double deal) 
{
	cout << "몬스터의 현재체력은 " << monsterHP-deal << " 입니다"<<endl;
	monsterHP -= deal;
}
void Monster::monsterState(double damage)
{
	if (damage >= monsterHP)
		eraseMonster();
	else
		showMonsterHP(damage);

}
void Monster::eraseMonster()
{
	cout << "몬스터가 죽었습니다";
}
