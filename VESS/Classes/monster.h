#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "WindowSize.h"
#include "Unit.h"
#include <string>
#include "cocostudio\CocoStudio.h"
using namespace std;
using namespace cocostudio;



class Monster : public Unit , public EventSender{
private:
	Size window_size;
	Vec2 origin;
public:
	bool isDead();
	Monster();
	~Monster();
	void dropItem();
	virtual bool init();
	static Monster* create();
	void damage(int dam);


	CCSprite * hpBar = CCSprite::create("Images/monsterHpBar.png");
	CCProgressTimer* hpBarDecreasing = CCProgressTimer::create(hpBar);
};
#endif // __MONSTER_H__