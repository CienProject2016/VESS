#include "Hero.h"
#include "HeroMovementState.h"
#include "MonsterInfo.h"
HeroMovementState::HeroMovementState() {
	state = run;
}
void HeroMovementState::update(float delta) {}
void HeroMovementState::setGravity() {
	gravity = fightLayerSize.height * 0.2f;
}
void HeroMovementState::initPos() {
	parent->setPosition(Vec2(fightLayerSize.width * 0.28f, fightLayerSize.height * 0.3f));
}
void HeroMovementState::setVerticalVelocity() {
	verticalVelocity = maxTime * gravity / 2;	//수직 속도를 설정
}

RunMovementState::RunMovementState(Hero* parent) {
	this->parent = parent;
	initPos();
	parent->setHitArea(HitArea::center);
	state = run;
}

StayMovementState::StayMovementState(Hero* parent) {
	this->parent = parent;
	initPos();
	parent->setHitArea(HitArea::center);
	state = stay;
}

JumpMovementState::JumpMovementState(Hero* parent) {
	this->parent = parent;
	maxTime = 0.5f;
	timer = movingDistance = 0;
	setGravity();
	setVerticalVelocity();
	parent->setHitArea(HitArea::up);
	state = avoid_up;
}

void JumpMovementState::update(float delta) {
	if (maxTime <= timer) {
		parent->setMovementState(new StayMovementState(this->parent));
		return;
	}
	verticalVelocity -= delta * gravity;
	//parent->setPositionY(parent->getPositionY() + verticalVelocity);
	timer += delta;
}

AttackMovementState::AttackMovementState(Hero* parent) {
	this->parent = parent;
	maxTime = 0.28f;
	timer = 0;
	direction = 1;
	movingDistance = fightLayerSize.width * 0.4f;
	setGravity();
	setVerticalVelocity();
	parent->setHitArea(HitArea::right);
	state = attack0;
}

void AttackMovementState::update(float delta) {
	if (maxTime <= timer) {
		if (direction < 0) {
			parent->setMovementState(new StayMovementState(this->parent));
			return;
		}
		else {
			timer = 0;
			direction = -1;
			attackEvent();
			setVerticalVelocity();
		}
	}
	verticalVelocity -= delta * gravity;
	//parent->setPositionY(parent->getPositionY() + verticalVelocity);
	//parent->setPositionX(parent->getPositionX() + direction * delta * moveDistance / maxTime);
	timer += delta;
}
void AttackMovementState::attackEvent() {
	parent->attackDamage();
}

AvoidMovementState::AvoidMovementState(Hero* parent) {
	this->parent = parent;
	maxTime = 0.2f;
	timer = 0;
	direction = 1;
	movingDistance = fightLayerSize.width * 0.2f;
	setGravity();
	setVerticalVelocity();
	parent->setHitArea(HitArea::left);
	state = avoid_left;
}
void AvoidMovementState::update(float delta) {
	if (maxTime <= timer) {
		if (direction < 0) {
			parent->setMovementState(new StayMovementState(this->parent));
			return;
		}
		else {
			timer = 0;
			direction = -1;
			setVerticalVelocity();
		}
	}
	verticalVelocity -= delta * gravity;
	//parent->setPositionY(parent->getPositionY() + verticalVelocity);
	//parent->setPositionX(parent->getPositionX() - direction * delta * moveDistance / maxTime);
	timer += delta;
}

SitdownMovementState::SitdownMovementState(Hero* parent) {
	this->parent = parent;

	maxTime = 0.4f;
	timer = movingDistance = 0;
	setGravity();
	setVerticalVelocity();
	parent->setHitArea(HitArea::down);
	state = avoid_down;
}
void SitdownMovementState::update(float delta) {
	if (maxTime <= timer) {
		parent->setMovementState(new StayMovementState(this->parent));
		return;
	}
	verticalVelocity -= delta * gravity;
	//parent->setPositionY(parent->getPositionY() + verticalVelocity);
	timer += delta;
}