#pragma once
#ifndef __Upgrade_LAYER_H__
#define __Upgrade_LAYER_H__

#include "cocos2d.h"
#include "Reinforce.h"

USING_NS_CC;

class UpgradeLayer : public Layer
{
private:
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void setTouchListener();

	char attribute;
public :
	virtual bool init();
	CREATE_FUNC(UpgradeLayer);
	

};

#endif