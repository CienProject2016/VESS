#include "Hero.h"
#include "cocostudio\CocoStudio.h"


using namespace cocostudio;
bool Hero::init()
{
	if (Unit::init())
	{
		//Size visibleSize = Director::getInstance()->getVisibleSize();
		//Vec2 origin = Director::getInstance()->getVisibleOrigin();

		window_size = fightLayerSize;
		origin = fightLayerOrigin;
		Node* node = CSLoader::createNode("Hero.csb");
		this->addChild(node); //get animation data 
		timeline::ActionTimeline* action = CSLoader::createTimeline("Hero.csb");
		node->setPosition(0, 0);
		node->runAction(action);
		action->gotoFrameAndPlay(26, 32, true);

		this->scheduleUpdate();
		setPos(STAY);

		avoidDistance = window_size.width * 0.2f;
		attackDistance = window_size.width * 0.4f;

		return true;
	}
	return false;
}

void Hero::update(float dt) {
	if (state == STAY) {
	}
	else {
		work_timer += dt;
		float currPosX;
		switch (state) {
		case STAY:
			break;
		case ATTACK_S:
			if (work_timer < max_attack_time) {
				vertical_velocity -= dt * window_size.height * 0.2f;
				currPosX = this->getPositionX();
				this->setPositionX(currPosX + dt * attackDistance / max_attack_time);
				this->setPositionY(this->getPositionY() + vertical_velocity);
			}
			else {
				vertical_velocity = max_attack_time * window_size.height * 0.2f / 2;
				state = ATTACK_E;
				setPos(state);
				work_timer = 0;
			}
			break;
		case JUMP_S:
			if (work_timer < max_jump_time) {
				vertical_velocity -= dt * window_size.height * 0.2f;
				this->setPositionY(this->getPositionY() + vertical_velocity);
			}
			else {
				vertical_velocity = max_jump_time * window_size.height * 0.2f / 2;
				state = JUMP_E;
				setPos(state);
				work_timer = 0;
			}
			break;
		case AVOID_S:
			if (work_timer < max_avoid_time) {
				vertical_velocity -= dt * window_size.height * 0.2f;
				currPosX = this->getPositionX();
				this->setPositionX(currPosX - dt * avoidDistance / max_avoid_time);
				this->setPositionY(this->getPositionY() + vertical_velocity);
			}
			else {
				vertical_velocity = max_avoid_time * window_size.height * 0.2f / 2;
				state = AVOID_E;
				setPos(state);
				work_timer = 0;
			}
			break;
		case SIT_S:
			state = STAY;
			setPos(STAY);
			break;
		case ATTACK_E:
			if (work_timer < max_attack_time) {
				vertical_velocity -= dt * window_size.height * 0.2f;
				currPosX = this->getPositionX();
				this->setPositionX(currPosX - dt * attackDistance / max_attack_time);
				this->setPositionY(this->getPositionY() + vertical_velocity);
			}
			else {
				state = STAY;
				setPos(STAY);
			}
			break;
		case JUMP_E:
			state = STAY;
			setPos(STAY);
			break;
		case AVOID_E:
			if (work_timer < max_avoid_time) {
				vertical_velocity -= dt * window_size.height * 0.2f;
				currPosX = this->getPositionX();
				this->setPositionX(currPosX + dt * avoidDistance / max_avoid_time);
				this->setPositionY(this->getPositionY() + vertical_velocity);
			}
			else {
				state = STAY;
				setPos(STAY);
			}
			break;
		case SIT_E:
			break;
		}
	}
}

void Hero::setPos(HeroState state) {
	switch (state) {
	case STAY:
		this->setPosition( Vec2(window_size.width * 0.3f, window_size.height * 0.4f));
		break;
	case ATTACK_S:
		break;
	case JUMP_S:
		break;
	case AVOID_S:
		break;
	case SIT_S:
		break;
	case ATTACK_E:
		break;
	case JUMP_E:
		break;
	case AVOID_E:
		break;
	case SIT_E:
		break;
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
	if (state == STAY)	return true;
	else return false;
}

void Hero::attack() {
	if (isAvailableCommend()) {
		state = ATTACK_S;
		work_timer = 0;
		vertical_velocity = max_attack_time * window_size.height * 0.2f / 2;
	}
}
void Hero::avoid() {
	if (isAvailableCommend()) {
		state = AVOID_S;
		work_timer = 0;
		vertical_velocity = max_avoid_time * window_size.height * 0.2f / 2;
	}
}
void Hero::sitDown() {
	if (isAvailableCommend()) {
		state = SIT_S;
		work_timer = 0;
	}
}
void Hero::jump() {
	if (isAvailableCommend()) {
		state = JUMP_S;
		work_timer = 0;
		vertical_velocity = max_jump_time * window_size.height * 0.2f / 2;
	}
}
