#include "EffectFactory.h"


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

	log("%f",this->timer);
	//여기에 맥스 타이머만큼 시간이 지나면 자기 자신을 지우는 코드 추가
	//if (this->isRunning()) {
	//	if (this->max_timer <= this->timer) {
	//		this->removeChild(
	//		log("!@!!@!@!@!@!@!@!@!@!@!@!@!@!@!@!@!@");
	//		return;
	//	}
	//	else {
	//		this->timer = this->timer + delta;
	//	}
	//}
	
	//parent->setPositionY(parent->getPositionY() + verticalVelocity);

}

//void EffectFactory::makeEffect(Node* scene, String path, float timer, Vec2 pos, float scale) {
//	EffectController* effect = EffectController::create(scene, path, timer, pos, scale);
//	//effect->init(fdsa, fdsa, fdsa, fdsa, fdsa);		// Effect::Name 에 따른 초기값 설정, 지금은 디폴트로 진행.
//	effect->init();
//
//
//	// 현재 시간을 따로 정할수 가 없다.
//
//	/*effect->setobject(scene);
//	effect->setmaxTimer(timer);
//	effect->settimer(0);
//
//
//	effect->setparticle(CSLoader::createNode("animation/MainScene.csb"));
//	effect->getobject()->addChild(effect->getparticle());
//	timeline::ActionTimeline* action = CSLoader::createTimeline("animation/MainScene.csb");
//	effect->getparticle()->setPosition(0, 0);
//	effect->getparticle()->runAction(action);
//	action->gotoFrameAndPlay(0, 40, true);
//	effect->getobject()->setPosition(pos.x, pos.y);*/
//	
//	//parent = scene;
//	//maxTimer = timer;
//	//timer = 0;
//
//
//	//particle = CSLoader::createNode("animation/MainScene.csb");  // 이 부분은 좀더 고민해봐야겠다.
//	//parent->addChild(particle);
//	//timeline::ActionTimeline* action = CSLoader::createTimeline("animation/MainScene.csb");
//	//particle->setPosition(0, 0);
//	//particle->runAction(action);
//	//action->gotoFrameAndPlay(0, 10, true);
//	//parent->setPosition(pos.x, pos.y);
//
//}

//void EffectFactory::update(float delta) {
//	if (40 <= effect_timer_) {
//
//
//		return;
//	}
//	log("dfdfdfdfdf");
//	//parent->setPositionY(parent->getPositionY() + verticalVelocity);
//	this->settimer(this->gettimer() + delta);
//
//}


