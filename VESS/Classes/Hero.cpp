#include "Hero.h"
#include "FightLayer.h"

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
		avoidDistance = window_size.width * 0.2f;
		attackDistance = window_size.width * 0.4f;
		
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
bool Hero::isAvailableCommand() {
	if (movement_state == NULL)	return true;
	return movement_state->isAvailableCommand();
}
void Hero::startAttack() {
	if (isAvailableCommand()) {
		setMovementState(new AttackMovementState(this));
	}
}
void Hero::startAvoid() {
	if (isAvailableCommand()) {
		setMovementState(new AvoidMovementState(this));
	}
}
void Hero::startSitDown() {
	if (isAvailableCommand()) {
		setMovementState(new SitdownMovementState(this));
	}
}
void Hero::startJump() {
	if (isAvailableCommand()) {
		setMovementState(new JumpMovementState(this));
	}
}

void Hero::attackDamage() {
	if (field->getMonster() != NULL) {
		field->getMonster()->damage(30);
		attackEffect();
	}
}

void Hero::attackEffect() {

}
void Hero::getDamage(bool damage) {

	auto heart1 = (Sprite*)getChildByTag(100000);
	auto heart2 = (Sprite*)getChildByTag(100001);
	auto heart3 = (Sprite*)getChildByTag(100002);
	if (numGetDamage == 0) { heart1->setOpacity(0); numGetDamage++; }
	else if (numGetDamage == 1) { heart2->setOpacity(0); numGetDamage++; }
	else if (numGetDamage == 2) { heart3->setOpacity(0); numGetDamage++; }
}

void Hero::setParentLayer(FightLayer* layer) {
	field = layer;
}

void Hero::setMovementState(HeroMovementState* state) {
	if (this->movement_state != NULL) {
		delete movement_state;
	}
	movement_state = state;
}
