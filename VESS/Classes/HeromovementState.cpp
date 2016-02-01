
#include "Hero.h"
#include "HeromovementState.h"
HeroMovementState::HeroMovementState() {}
void HeroMovementState::update(float delta) {}
void HeroMovementState::setGravity() {
	gravity = fightLayerSize.height * 0.2f;
}
bool HeroMovementState::isAvailableCommend() {
	return false;
}
void HeroMovementState::InitPos() {
	parent->setPosition(Vec2(fightLayerSize.width * 0.3f, fightLayerSize.height * 0.4f));
}
void HeroMovementState::setVerticalVelocity() {
	vertical_velocity = max_time * gravity / 2;	//수직 속도를 설정
}

StayMovementState::StayMovementState(Hero* parent) {
	this->parent = parent;
	InitPos();
}
bool StayMovementState::isAvailableCommend() {
	return true;
}

JumpMovementState::JumpMovementState(Hero* parent) {
	this->parent = parent;
	max_time = 0.42f;
	timer = moveDistance = 0;
	setGravity();
	setVerticalVelocity();
}

void JumpMovementState::update(float delta) {
	if (max_time <= timer) {
		parent->setMovementState(new StayMovementState(this->parent));
		return;
	}
	vertical_velocity -= delta * gravity;
	parent->setPositionY(parent->getPositionY() + vertical_velocity);
	timer += delta;
}

AttackMovementState::AttackMovementState(Hero* parent) {
	this->parent = parent;
	max_time = 0.2f;
	timer = 0;
	direction = 1;
	moveDistance = fightLayerSize.width * 0.4f;
	setGravity();
	setVerticalVelocity();
}
void AttackMovementState::update(float delta) {
	if (max_time <= timer) {
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
	vertical_velocity -= delta * gravity;
	parent->setPositionY(parent->getPositionY() + vertical_velocity);
	parent->setPositionX(parent->getPositionX() + direction * delta * moveDistance / max_time);
	timer += delta;
}
void AttackMovementState::attackEvent() {
	parent->reciever->send(EVENT::HeroAttack);
}

AvoidMovementState::AvoidMovementState(Hero* parent) {
	this->parent = parent;
	max_time = 0.2f;
	timer = 0;
	direction = 1;
	moveDistance = fightLayerSize.width * 0.2f;
	setGravity();
	setVerticalVelocity();
}
void AvoidMovementState::update(float delta) {
	if (max_time <= timer) {
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
	vertical_velocity -= delta * gravity;
	parent->setPositionY(parent->getPositionY() + vertical_velocity);
	parent->setPositionX(parent->getPositionX() - direction * delta * moveDistance / max_time);
	timer += delta;
}

SitdownMovementState::SitdownMovementState(Hero* parent) {
	this->parent = parent;
	max_time = 0.4f;
	timer = moveDistance = 0;
	setGravity();
	setVerticalVelocity();
}
void SitdownMovementState::update(float delta) {
	if (max_time <= timer) {
		parent->setMovementState(new StayMovementState(this->parent));
		return;
	}
	vertical_velocity -= delta * gravity;
	parent->setPositionY(parent->getPositionY() + vertical_velocity);
	timer += delta;
}