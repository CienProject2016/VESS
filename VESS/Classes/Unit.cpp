#include "Unit.h"

Unit::Unit() : hp(100){

}

Unit::~Unit() {

}

int Unit::getHP() 
{
	return this->hp;
}

void Unit::setHP(int hp) 
{
	this->hp = hp;
}
