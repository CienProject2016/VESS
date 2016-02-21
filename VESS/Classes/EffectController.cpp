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
	return isOver;
}