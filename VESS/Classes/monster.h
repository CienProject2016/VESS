#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "WindowSize.h"
#include "Unit.h"
#include <string>
#include "cocostudio\CocoStudio.h"
using namespace std;
using namespace cocostudio;


class FightLayer;

class Monster : public Unit{

private :
	int fdsafdsa;
protected:
	Size window_size;
	Vec2 origin;
	FightLayer* field;
	void initHp(int hp);
	void initWindowSize();
	virtual void initImage();
	Node* image;
	RepeatForever* makeAction(char* plist, int imageCount, char* imageName, float frameTime);
public:
	bool isDead();
	Monster();
	~Monster();
	void dropItem();
	virtual bool init();
	void setParentLayer(FightLayer* layer);
	static Monster* create();
	void damage(int dam);
	virtual void update(float delta);


	CCSprite * hpBar;
	CCProgressTimer* hpBarDecreasing;
};
#endif // __MONSTER_H__