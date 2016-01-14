#pragma once
#ifndef __FIGHT_LAYER_H__
#define __FIGHT_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class FightLayer : public Layer
{
public :
	virtual bool init();
	CREATE_FUNC(FightLayer);
	void monsterAction();

};

#endif