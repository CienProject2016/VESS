#pragma once
#ifndef __CHEST_H__
#define __CHEST_H__

#include "WindowSize.h"
#include "Unit.h"
#include <string>
#include "cocostudio\CocoStudio.h"
using namespace std;
using namespace cocostudio;

class FightLayer;

class Chest : public Unit {
protected:
	FightLayer* field;
	void initHp(int hp);
	void initWindowSize();
	virtual void initImage();
	Node* chest;
	Node* newChest;
	Size windowSize;
	Vec2 origin;
public:
	bool isDead();
	Chest();
	~Chest();
	void dropItem();
	virtual bool init();
	void setParentLayer(FightLayer* layer);
	static Chest* create();
	void damage(int dam);
	virtual void update(float delta);
	//Sprite * hpBar = Sprite::create("Images/chestHpBar.png");
	//ProgressTimer* hpBarDecreasing = ProgressTimer::create(hpBar);
};

#endif // __CHEST_H__