#include "Monster.h"
#include <iostream>
using namespace std;

Monster::Monster()
{
	cout << "���� ������ ��ȣ�� �Է�(1������ 5������):";
	cin >> monster_number;
	createMonster(monster_number);
}

Monster::~Monster()
{}

void Monster::createMonster(int monster_number)
{
	double init = 0;
	switch (monster_number)
	{
	case 1:
		hp_ = 10;
		break;
	case 2:
		hp_ = 100;
		break;
	case 3:
		hp_ = 1000;
		break;
	case 4:
		hp_ = 10000;
		break;
	case 5:
		hp_ = 20000;
		break;

	}
	cout << monster_number << "�� ���Ͱ� �����Ǿ����ϴ�" << endl;
}