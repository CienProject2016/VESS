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
	//���⿡ �ƽ� Ÿ�̸Ӹ�ŭ �ð��� ������ �ڱ� �ڽ��� ����� �ڵ� �߰�
}

void EffectFactory::makeEffect(Node* parent, Effect::Name name) {
	SelfDestroyEffect* effect = SelfDestroyEffect::create();
	effect->init(fdas, fdsa, fdsa, fdsa, fdsa);		// Effect::Name �� ���� �ʱⰪ ����, ������ ����Ʈ�� ����.

}


