#include "Monster.h"
#include "Unit.h"
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
	cout << monsterNumber << "�� ���Ͱ� �����Ǿ����ϴ�" << endl;
}