#pragma once
#ifndef __FIGHT_LAYER_H__
#define __FIGHT_LAYER_H__

#include "cocos2d.h"
#include "BattleOperator.h"

USING_NS_CC;

class FightLayer : public Layer
{
private : 
	BattleOperator* controller;

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void setTouchListener();

public :
	virtual bool init();
	CREATE_FUNC(FightLayer);
	void monsterAction();

};

#endif