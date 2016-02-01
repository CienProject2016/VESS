
#include "Unit.h"
#include "WindowSize.h"
#include "cocostudio\CocoStudio.h"

using namespace cocostudio;
class HeroMovementState {
protected:
	float max_time;
	float timer;
	float vertical_velocity;
	Node* parent;
	float gravity;
public:
	HeroMovementState() {}
	virtual void update(float delta) {}
	void setGravity() {
		gravity = fightLayerSize.height * 0.2f;
	}
	virtual bool isAvailableCommend() {
		return false;
	}
};

class StayMovementState : public HeroMovementState {
	virtual bool isAvailableCommend() {
		return true;
	}
};

class JumpMovementState : public HeroMovementState {
public:
	JumpMovementState(Node* parent) {
		this->parent = parent;
		max_time = 0.42f;
		timer = 0;
		setGravity();
		vertical_velocity = max_time * gravity / 2;	//수직 속도를 설정
	}

	virtual void update(float delta) {
		if (max_time <= timer) {
			state = stay;
		}
		vertical_velocity -= delta * gravity;
		parent->setPositionY(parent->getPositionY() + vertical_velocity);
	}
};

class AttackMovementState : public HeroMovementState {

};

class AvoidMovementState : public HeroMovementState {

};

class SitdownMovementState : public HeroMovementState {

};