#pragma once
#ifndef __EFFECT_FACTORY_H__
#define __EFFECT_FACTORY_H__

#include "WindowSize.h"
#include "Unit.h"
#include <string>
#include "cocostudio\CocoStudio.h"
#include "ResourcePath.h"


USING_NS_CC;

class MakeAnimationInfo;

class EffectFactory : public Node {
public:
	enum EffectKind { SlimeDeadAnimation, SlimeAttack0, DamageEffect0, DamageEffect1 };
	static EffectFactory* create(EffectKind effect, Vec2 pos);
private:
	EffectFactory();
	~EffectFactory();
	Node* image;
	EffectKind kind;
	bool stopOnce;	//애니메이션을 한번 멈추기위해 설정.
	float timer;
	float maxTimer;
	virtual void update(float delta);
	void init(EffectKind effect, Vec2 pos);
	RepeatForever* makeAction(MakeAnimationInfo* info);

};

#endif // __EFFECT_FACTORY_H__