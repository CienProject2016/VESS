#pragma once
#include <string>

class Sword {
private:
	char* name;
	int damage;
public:
	Sword();
	~Sword();
	char* getName();
	void setName(char name[]);
	int getDamage();
	void setDamage(int damage);
};

class Shield {
private:
	char* name;
	int defense;
public:
	Shield();
	~Shield();
	char* getName();
	void setName(char name[]);
	int getDefense();
	void setDefense(int defense);
};