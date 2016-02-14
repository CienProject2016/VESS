#include "Hero.h"
#include "FightLayer.h"

bool Hero::init()
{
	if (Unit::init())
	{
		windowSize = fightLayerSize;
		origin = fightLayerOrigin;
		Node* node = CSLoader::createNode("Hero.csb");
		node->setScale(0.8f);
		this->addChild(node); //get animation data 
		action = CSLoader::createTimeline("Hero.csb");
		node->setPosition(0, 0);
		node->runAction(action);
		action->gotoFrameAndPlay(0, 28, true);
		this->scheduleUpdate();
		avoidDistance = windowSize.width * 0.2f;
		attackDistance = windowSize.width * 0.4f;
		
		
		setMovementState(new StayMovementState(this));
		return true;
	}
	return false;
}

void Hero::update(float delta) {
	if (movementState != NULL) {
		movementState->update(delta);
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
	if (movementState == NULL)	return true;
	return movementState->isAvailableCommand();
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
	Sprite** heart = (Sprite**)malloc(sizeof(Sprite*)*SIZE_OF_LIFE);
	for (int i = 0;i < SIZE_OF_LIFE;i++)
	{
		heart[i] = Sprite::create();
		heart[i] = (Sprite*)getChildByTag(10000 + i);
	}
	if (numGetDamage == 0) { heart[0]->setOpacity(0); numGetDamage++; }
	else if (numGetDamage == 1) { heart[1]->setOpacity(0); numGetDamage++; }
	else if (numGetDamage == 2) { heart[2]->setOpacity(0); numGetDamage++;free(heart);}
}

void Hero::setParentLayer(FightLayer* layer) {
	field = layer;
}

void Hero::setMovementState(HeroMovementState* state) {
	if (this->movementState != NULL) {
		delete movementState;
	}
	movementState = state;
}
