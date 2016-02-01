#include "Hero.h"


bool Hero::init()
{
	if (Unit::init())
	{
		window_size = fightLayerSize;
		origin = fightLayerOrigin;
		Node* node = CSLoader::createNode("Hero.csb");
		node->setScale(0.8f);
		this->addChild(node); //get animation data 
		action = CSLoader::createTimeline("Hero.csb");
		node->setPosition(0, 0);
		node->runAction(action);
		action->gotoFrameAndPlay(0, 28, true);
		this->scheduleUpdate();
		setMovementState(new StayMovementState(this));
		return true;
	}
	return false;
}

void Hero::update(float dt) {

	if (movement_state != NULL) {
		movement_state->update(dt);
	}
}

Hero* Hero::create()
{
	Hero *hero = new Hero();
	if (hero && hero->init())
	{
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return nullptr;
}

//Hero 가 운동(회피, 공격, 점프, 앉기)중에는 다른 명령을 받지 않도록 만든다.
bool Hero::isAvailableCommend() {
	if (movement_state == NULL)	return true;
	return movement_state->isAvailableCommend();
}
void Hero::attack() {
	if (isAvailableCommend()) {
		setMovementState(new AttackMovementState(this));
	}
}
void Hero::avoid() {
	if (isAvailableCommend()) {
		setMovementState(new AvoidMovementState(this));
	}
}
void Hero::sitDown() {
	if (isAvailableCommend()) {
		setMovementState(new SitdownMovementState(this));
	}
}
void Hero::jump() {
	if (isAvailableCommend()) {
		setMovementState(new JumpMovementState(this));
	}
}

void Hero::attackEffect() {

}

void Hero::setMovementState(HeroMovementState* state) {
	if (this->movement_state != NULL) {
		delete movement_state;
	}
	movement_state = state;
}
