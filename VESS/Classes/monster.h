#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__
#include "Unit.h"
#include <string>
using namespace std;

class Monster : public Unit {
private:

public:
	Monster();
	~Monster();
	static Monster* create(const std::string&);
	virtual bool init(const std::string&);
	virtual bool init();
};
#endif