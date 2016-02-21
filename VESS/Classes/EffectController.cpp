#include "EffectController.h"
#include "FightLayer.h"

EffectController::EffectController() {}
EffectController::~EffectController() {}
EffectController* EffectController::create(Node* scene, String path, float timer, Vec2 pos, float scale) {

	EffectController *effect = new EffectController();
	if (effect && effect->init())
	{
		effect->object = scene;
		effect->max_timer = timer;
		effect->timer = 0;


		effect->particle = CSLoader::createNode("animation/Tauren.csb");
		effect->object->addChild(effect->particle);
		timeline::ActionTimeline* action = CSLoader::createTimeline("animation/Tauren.csb");
		effect->particle->setPosition(0, 0);
		effect->particle->runAction(action);
		action->gotoFrameAndPlay(0, 40, true);
		effect->object->setPosition(pos.x, pos.y);
		effect->autorelease();
		return effect;
	}
	
	CC_SAFE_DELETE(effect);
	return nullptr;
}
bool EffectController::init()
{
	//this->parent = parent;
	//maxTimer = timer;
	//this->timer = 0;

	//
	//this->particle =CSLoader::createNode("animation/MainScene.csb");  // 이 부분은 좀더 고민해봐야겠다.
	//this->parent->addChild(particle);
	//timeline::ActionTimeline* action = CSLoader::createTimeline("animation/MainScene.csb");
	//this->particle->setPosition(0,0);
	//this->particle->runAction(action);
	//action->gotoFrameAndPlay(0, 10, true);
	//this->parent->setPosition(pos.x, pos.y);
	this->scheduleUpdate();

	log("dfdfgrngrnrgnkrgn");
	return true;
}

void EffectController::update(float delta) {
	//eraseEffect(delta);
	//log("%f",this->timer);

}

void EffectController::setParentLayer(Hero* layer) {
	field = layer;
}

void EffectController::eraseEffect(float delta) {
	timer += delta;
	log("%f",timer);

	if (timer > max_timer) {
		//field->removeEffect();
		timer = 0;
		this->setVisible(false);

	}
}