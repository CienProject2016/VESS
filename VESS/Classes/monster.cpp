#include "monster.h"
#include "unit.h"
#include <iostream>
using namespace std;

Monster::Monster()
{
	cout << "���� ������ ��ȣ�� �Է�(1������ 5������):";
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
	cout <<monsterNumber<<"�� ���Ͱ� �����Ǿ����ϴ�"<<endl;
	showMonsterHP(init);


}
void Monster::showMonsterHP(double deal) 
{
	cout << "������ ����ü���� " << monsterHP-deal << " �Դϴ�"<<endl;
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
	cout << "���Ͱ� �׾����ϴ�";
}
