#ifndef __UNIT_H__
#define __UNIT_H__

class Unit {
protected:
	int hp;
public:
	virtual int getHP();
	virtual void setHP(int);
};
#endif