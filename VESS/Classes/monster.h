#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__
#include "Unit.h"
#include <string>
using namespace std;

class Monster : public Unit {
public:
	bool isDead();
	Monster();
	~Monster();
	static Monster* create(const std::string&);
	virtual bool init(const std::string&);
	virtual bool init();
};
#endif // __MONSTER_H__