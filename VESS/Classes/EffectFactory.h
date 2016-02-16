#pragma once
#ifndef __EFFECT_FACTORY_H__
#define __EFFECT_FACTORY_H__

#include "cocostudio\CocoStudio.h"
#include <string.h>
USING_NS_CC;

class Effect : public Node{
public:
	enum Name { default_ };

};

class SelfDestroyEffect : public Effect {
private:
	SelfDestroyEffect();
	~SelfDestroyEffect();
	float timer;
	float maxTimer;
	Node* parent;
	virtual void update(float delta);
public:
	static SelfDestroyEffect* create();
	void init(Node* parent, String path, float timer, Vec2 pos, float scale);
};

class EffectFactory {
public:
	static void makeEffect(Node* parent, Effect::Name name);

};




#endif // __EFFECT_FACTORY_H__