#include "EffectFactory.h"


SelfDestroyEffect::SelfDestroyEffect() {}
SelfDestroyEffect::~SelfDestroyEffect() {}
SelfDestroyEffect* SelfDestroyEffect::create() {

}
void SelfDestroyEffect::init(Node* parent, String path, float timer, Vec2 pos, float scale) {
	this->parent = parent;
	maxTimer = timer;
	this->timer = 0;
	this->scheduleUpdate();
}

void SelfDestroyEffect::update(float delta) {
	//여기에 맥스 타이머만큼 시간이 지나면 자기 자신을 지우는 코드 추가
}

void EffectFactory::makeEffect(Node* parent, Effect::Name name) {
	SelfDestroyEffect* effect = SelfDestroyEffect::create();
	effect->init(fdas, fdsa, fdsa, fdsa, fdsa);		// Effect::Name 에 따른 초기값 설정, 지금은 디폴트로 진행.

}


