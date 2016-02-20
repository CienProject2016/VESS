#include "Hero.h"
#include "FightLayer.h"
#include "Resources.h"
#include "EffectController.h"

#define ANIMATION 10000

bool Hero::init()
{
	if (Unit::init())
	{
		effectEnd = false;
		numGetDamage = 0;
		windowSize = fightLayerSize;
		origin = fightLayerOrigin;
		Node* node = CSLoader::createNode("Hero.csb");
		node->setScale(0.8f);
		this->addChild(node); //get animation data 
		action = CSLoader::createTimeline("Hero.csb");
		action->setTag(ANIMATION);
		node->setPosition(0, 0);
		node->runAction(action);
		action->gotoFrameAndPlay(0, 16, true);
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
	if (effectEnd) {
		effectTime += delta;
		if (effectTime > 5) {
			this->removeChild(effectController);
			effectTime = 0;
		}
	}
	//여기에 시간이 지나면 removeChild 하게 만들어주면됨.
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
	action->gotoFrameAndPlay(75, 95, true);//대기 모션
}
void Hero::startAttack() {
	if (isAvailableCommand()) {
		setMovementState(new AttackMovementState(this));
		action->gotoFrameAndPlay(198, 211, false);//공격1 
	}
}
void Hero::startAvoid() {
	if (isAvailableCommand()) {
		setMovementState(new AvoidMovementState(this));
		action->gotoFrameAndPlay(175, 187, false);//중간회피 
	}
}
void Hero::startSitDown() {
	if (isAvailableCommand()) {
		setMovementState(new SitdownMovementState(this));
		action->gotoFrameAndPlay(116, 128, false);//아래회피(sit 대신 dodge
	}
}
void Hero::startJump() {
	if (isAvailableCommand()) {
		setMovementState(new JumpMovementState(this));
		action->gotoFrameAndPlay(97, 113, false);//위회피
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioResources::SOUND_JUMP_PATH.c_str());
	}
}

void Hero::attackDamage() {
	if (field->getMonster() != NULL) {
		field->getMonster()->damage(30);
		attackEffect(30);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioResources::SOUND_ATTACK_PATH.c_str());
	}
}

void Hero::attackEffect(int attackDamage) {
	effectController = EffectController::create(this, "animation/Tauren.csb", 5, Vec2(50, 50), 1);
	//EffectFactory::makeEffect(this, "animation/MainScene.csb",40,Vec2(50,50),1);
	effectController->setName("effectController");
	this->addChild(effectController);
	effectEnd = true;
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
	action->gotoFrameAndPlay(0, 16, true);//달리는 모션
}
