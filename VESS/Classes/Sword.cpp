#include "Sword.h"

Sword::Sword() {
	this->setName("wooden sword");
	this->damage = 10;
	this->setMaxDurability(10);
	this->setDurability(10); // ���� �׽��� ������ �Ϻη� 5�� �������
}

Sword::~Sword() {
}
