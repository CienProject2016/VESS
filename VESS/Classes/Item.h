#pragma once
#include <string>
using namespace std;
#include "cocos2d.h"

class Item {
public:
	enum Type { SWORD, SHIELD };
	Item();
	~Item();
	virtual string getName();
	virtual void setName(string name);
	virtual int getDurability();
	virtual void setDurability(int durabillity);
	virtual int getMaxDurability();
	virtual void setMaxDurability(int maxDurabillity);
	bool isInUse();
	void setInUse(bool);
protected :
	CC_SYNTHESIZE(int, upgradeId, UpgradeId);
	string name_;
	int durability_;
	int max_durability_;
	bool inUse;
	Type itemType;	
};

class Sword : public Item {
private:
	int damage_;
	CC_SYNTHESIZE(int, speed, Speed);
public:
	enum SwordType { °Ë };
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