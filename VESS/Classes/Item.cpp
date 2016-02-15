#include "Item.h"

Item::Item() : upgradeId(1), name_(),speed() {
}

Item::~Item() {

}

string Item::getName() {
	return name_;
}

void Item::setName(string name) {
	name_ = name;
}

int Item::getDurability() {
	return durability_;
}
void Item::setDurability(int val) {
	durability_ = val;
}
int Item::getMaxDurability() {
	return max_durability_;
}
void Item::setMaxDurability(int val) {
	max_durability_ = val;
}


Sword::Sword() {
	setName("wooden sword");
	damage_ = 10;
	setMaxDurability(10);
	setDurability(5); // 현재 테스팅 용으로 일부러 5로 낮춰놓음
}

Sword::~Sword() {
}

int Sword::getDamage() {
	return damage_;
}

void Sword::setDamage(int val) {
	damage_ = val;
}

Shield::Shield() {
	Item::setName("wooden shield");
	Item::setDurability(15);
	Item::setMaxDurability(20);
}

Shield::~Shield() {
}