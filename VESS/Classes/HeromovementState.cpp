
#include "Hero.h"
#include "HeroMovementState.h"
HeroMovementState::HeroMovementState() {}
void HeroMovementState::update(float delta) {}
void HeroMovementState::setGravity() {
	gravity = fightLayerSize.height * 0.2f;
}
bool HeroMovementState::isAvailableCommand() {
	return false;
}
void HeroMovementState::initPos() {
	parent->setPosition(Vec2(fightLayerSize.width * 0.3f, fightLayerSize.height * 0.4f));
}
void HeroMovementState::setVerticalVelocity() {
	vertical_velocity = max_time * gravity / 2;	//수직 속도를 설정
}

StayMovementState::StayMovementState(Hero* parent) {
	this->parent = parent;
	initPos();
}
bool StayMovementState::isAvailableCommand() {
	return true;
}

JumpMovementState::JumpMovementState(Hero* parent) {
	this->parent = parent;
	max_time = 0.42f;
	timer = move_distance = 0;
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
	move_distance = fightLayerSize.width * 0.4f;
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
	parent->setPositionX(parent->getPositionX() + direction * delta * move_distance / max_time);
	timer += delta;
}
void AttackMovementState::attackEvent() {
	parent->attackDamage();
}

AvoidMovementState::AvoidMovementState(Hero* parent) {
	this->parent = parent;
	max_time = 0.2f;
	timer = 0;
	direction = 1;
	move_distance = fightLayerSize.width * 0.2f;
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
	parent->setPositionX(parent->getPositionX() - direction * delta * move_distance / max_time);
	timer += delta;
}

SitdownMovementState::SitdownMovementState(Hero* parent) {
	this->parent = parent;
	max_time = 0.4f;
	timer = move_distance = 0;
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