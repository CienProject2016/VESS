#include "EffectController.h"

EffectController::EffectController():isOver(false), max_timer(0), timer(0) {}
EffectController::~EffectController() {}
EffectController* EffectController::create(Node* parent, String path, float timer, Vec2 pos, float scale) {

	EffectController *effect = new EffectController();
	if (effect && effect->init(timer))
	{
		effect->autorelease();
		return effect;
	}
	CC_SAFE_DELETE(effect);
	return nullptr;
}
bool EffectController::init(int timer)
{
	if (Node::init())
	{
		max_timer = timer;
		timer = 0;

		particle = CSLoader::createNode("animation/Tauren.csb");
		this->addChild(particle);
		timeline::ActionTimeline* action = CSLoader::createTimeline("animation/Tauren.csb");
		particle->setPosition(0, 0);
		this->particle->runAction(action);
		action->gotoFrameAndPlay(0, 40, true);
		this->scheduleUpdate();
	}
	
	return true;
}

void EffectController::update(float delta) {
	checkEraseEffect(delta);
	//log("%f",this->timer);

}

void EffectController::checkEraseEffect(float delta) {
	timer += delta;
	log("delta : %f",timer);

	if (timer > max_timer) {
		//field->removeEffect();
		isOver = true;
	}
}

bool EffectController::checkIsOver() {
	return isOver; //현재 Hero.cpp와 Monster.cpp 둘 다 이 변수를 사용하기로 되어있다. 둘 다 사용중이 아니라서 현재는 오류가 없다. 현재는 주석처리가 되어있지만, 만약 둘 다 이펙트를 사용하게 된다면 오류가 발생할 수 있으니, 두개로 나눠서 사용하는 방법 등을 사용하길 바란다.
}