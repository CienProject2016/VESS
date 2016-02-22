#include "DefenseMovementState.h"
#include "Hero.h"

DefenseMovementState::DefenseMovementState(Hero* parent, ActionFrameValue* actionFrameValue) {
	this->parent = parent;
	this->actionFrameValue = actionFrameValue;
	maxTime = 0.5f;
	timer = 0;
	setGravity();
	state = defence;
}

DefenseMovementState::~DefenseMovementState() {

}

void DefenseMovementState::update(float delta) {
	if (maxTime <= timer) {
		parent->setMovementState(new StayMovementState(this->parent));
		return;
	}
	timer += delta;
}

DefenseMovementState::DefenseMovementState(Hero* parent) {
	*this = DefenseMovementState(parent, new ActionFrameValue(18, 25));
}