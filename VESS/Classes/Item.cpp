#include "Item.h"

Sword::Sword() {
	name = "wooden sword";
	damage = 10;
}

Sword::~Sword() {
}

char* Sword::getName() {
	return name;
}

void Sword::setName(char val[]) {
	name = val;
}

int Sword::getDamage() {
	return damage;
}

void Sword::setDamage(int val) {
	damage = val;
}

Shield::Shield() {
	name = "wooden shield";
	defense = 10;
}

Shield::~Shield() {
}

char* Shield::getName() {
	return name;
}

void Shield::setName(char val[]) {
	name = val;
}

int Shield::getDefense() {
	return defense;
}

void Shield::setDefense(int val) {
	defense = val;
}