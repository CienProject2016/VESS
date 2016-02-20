#pragma once
#ifndef __EFFECT_FACTORY_H__
#define __EFFECT_FACTORY_H__

#include "cocostudio\CocoStudio.h"
#include <string.h>
#include "GameData.h"
#include "cocos2d.h"
USING_NS_CC;

//class Effect : public Node{
//public:
//	enum Name { default_ };
//
//};

class EffectController : public Node {
private:
	EffectController();
	~EffectController();
	
	Node* object;
	Node* particle;
	float timer;
	float max_timer;

	//CC_SYNTHESIZE(Node*, object_, object);
	//CC_SYNTHESIZE(Node*, particle_, particle);
	//CC_SYNTHESIZE(float, timer_, timer);
	//CC_SYNTHESIZE(float, max_timer_, maxTimer);

	virtual void update(float delta);
public:
	
	static EffectController* create(Node* parent, String path, float timer, Vec2 pos, float scale);
	virtual bool init();
	//void init(Node* parent, String path, float timer, Vec2 pos, float scale);
};

//class EffectFactory {
//private:
//	virtual void update(float delta);
//	CC_SYNTHESIZE(float, effect_timer_, effectTimer);
//public:
//	static void makeEffect(Node* parent,String path, float timer, Vec2 pos, float scale);
//};




#endif // __EFFECT_FACTORY_H__