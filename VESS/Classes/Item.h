#pragma once
#include <string>

class Sword {
private:
	char* name_;
	int damage_;
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
	char* name_;
	int defense_;
public:
	Shield();
	~Shield();
	char* getName();
	void setName(char name[]);
	int getDefense();
	void setDefense(int defense);
};