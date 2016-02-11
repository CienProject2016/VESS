#pragma once
#include <string>


class Item {
private:
	char* name_;
	int durability_;
	int max_durability_;
	bool inUse;
public:
	virtual char* getName();
	virtual void setName(char name[]);
	virtual int getDurability();
	virtual void setDurability(int durabillity);
	virtual int getMaxDurability();
	virtual void setMaxDurability(int maxDurabillity);
	bool isInUse();
	void setInUse(bool);
};
class Sword : public Item {
private:
	int damage_;

public:
	Sword();
	~Sword();
	int getDamage();
	void setDamage(int damage);

};

class Shield : public Item {
public:
	Shield();
	~Shield();
};