#pragma once
#ifndef __EFFECT_CONTROLLER_H__
#define __EFFECT_CONTROLLER_H__

#include "cocostudio\CocoStudio.h"
#include <string.h>
#include "GameData.h"
#include "cocos2d.h"
USING_NS_CC;

class EffectController : public Node {
private:
	EffectController();
	~EffectController();
	Node* object;
	Node* particle;
	float timer;
	float max_timer;
	virtual void update(float delta);
public:
	static EffectController* create(Node* parent, String path, float timer, Vec2 pos, float scale);
	virtual bool init();

};

#endif // __EFFECT_CONTROLLER_H__