#include "Shield.h"


Shield::Shield() :upgradePercent(0), repairPercent(0) {
	this->setName("wooden shield");
	this->setDurability(15);
	this->setMaxDurability(20);
}

Shield::~Shield() {
}