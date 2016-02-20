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
	verticalVelocity = maxTime * gravity / 2;	//수직 속도를 설정
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
	maxTime = 0.5f;
	timer = movingDistance = 0;
	setGravity();
	setVerticalVelocity();

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

}

void AttackMovementState::update(float delta) {
	if (maxTime <= timer) {
		if (direction < 0) {
			parent->setMovementState(new StayMovementState(this->parent));

			return;
		}
		else {
			//effectTime += delta;
			timer = 0;
			direction = -1;
			attackEvent();
			setVerticalVelocity();
		}
	}
	verticalVelocity -= delta * gravity;
	//parent->setPositionY(parent->getPositionY() + verticalVelocity);
	//parent->setPositionX(parent->getPositionX() + direction * delta * moveDistance / maxTime);
	parent->setPositionY(parent->getPositionY() + verticalVelocity);
	parent->setPositionX(parent->getPositionX() + direction * delta * movingDistance / maxTime);
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