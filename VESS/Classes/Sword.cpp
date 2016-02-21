#include "Sword.h"

Sword::Sword() {
	this->setName("wooden sword");
	this->damage = 10;
	this->setMaxDurability(10);
	this->setDurability(10); // 현재 테스팅 용으로 일부러 5로 낮춰놓음
}

Sword::~Sword() {
}
