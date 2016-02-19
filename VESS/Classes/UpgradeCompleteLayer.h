#pragma once

#ifndef __UPGRADE_COMPLETE_LAYER_H__
#define __UPGRADE_COMPLETE_LAYER_H__

#include <string>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class UpgradeCompleteLayer : public Layer
{
private:
	void updateUpgradeInfo();
	void updateRepairInfo();
public:
	static cocos2d::Scene* createScene();
	void confirmCallback(cocos2d::Ref*);
	void showUpgradeInfo();
	CREATE_FUNC(UpgradeCompleteLayer);
	virtual bool init();
	virtual void update(float);
};

#endif