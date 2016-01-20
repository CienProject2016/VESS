#include "Item.h"


Sword::Sword() {
	name_ = "wooden sword";
	damage_ = 10;
}

Sword::~Sword() {
}

char* Sword::getName() {
	return name_;
}

void Sword::setName(char val[]) {
	name_ = val;
}

int Sword::getDamage() {
	return damage_;
}

void Sword::setDamage(int val) {
	damage_ = val;
}

Shield::Shield() {
	name_ = "wooden shield";
	defense_ = 10;
}

Shield::~Shield() {
}

char* Shield::getName() {
	return name_;
}

void Shield::setName(char val[]) {
	name_ = val;
}

int Shield::getDefense() {
	return defense_;
}

void Shield::setDefense(int val) {
	defense_ = val;
}