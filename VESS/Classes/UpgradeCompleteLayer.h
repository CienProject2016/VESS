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
	const char* SWORD_NAME = "무기 이름";
	const char* SHIELD_NAME = "방패 이름";
	const char* DURABILITY_NAME = "내구도";
	const char* MAX_DURABILITY_NAME = "최대 내구도";
	const char* DEFENSE_NAME = "방어력";
	const char* ATTACK_NAME = "공격력";
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