#include "Hero.h"
#include "FightLayer.h"
#include "MonsterInfo.h"
#include "Monster.h"
#include "ResourcePath.h"
#include "DefenseMovementState.h"

#define ANIMATION 10000

bool Hero::init()
{
	if (Unit::init())
	{
		windowSize = fightLayerSize;
		origin = fightLayerOrigin;
		Node* node = CSLoader::createNode("character.csb");
		node->setScale(0.8f);
		node->setName("actionNode");
		this->addChild(node); //get animation data 
		action = CSLoader::createTimeline("character.csb");
		action->setTag(ANIMATION);
		node->setPosition(0, 0);
		node->runAction(action);
		action->gotoFrameAndPlay(0, 16, true);


		itemNode = CSLoader::createNode("weapon_sword.csb");
		itemNode->setName("itemNode");
		itemNode->setScale(0.8f);
		this->addChild(itemNode);
		itemAction = CSLoader::createTimeline("weapon_sword.csb");
		itemNode->setPosition(0, 0);
		itemNode->runAction(itemAction);
		itemAction->gotoFrameAndPlay(0, 16, true);

		this->scheduleUpdate();
		avoidDistance = windowSize.width * 0.2f;
		attackDistance = windowSize.width * 0.4f;
		heroPosition = new HitArea();
		fullHp = 3;
		hp = fullHp;
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

void Hero::changeAction(string actionPath, int startFrame, int endFrame) {
	Node* node = (Node*)getChildByName("actionNode");
	node = CSLoader::createNode(actionPath);
	action = CSLoader::createTimeline(actionPath);
	action->gotoFrameAndPlay(startFrame, endFrame, true);
	node->runAction(action);	
}

void Hero::changeItemAction(Item::Type itemType) {
	this->removeChild(itemNode);
	if (itemType == Item::Type::SWORD) {		
		itemNode = CSLoader::createNode(ActionPath::SWORD_PATH);
		itemNode->setScale(0.8f);
		itemAction = CSLoader::createTimeline(ActionPath::SWORD_PATH);	
		this->addChild(itemNode);
		itemNode->runAction(itemAction);
		itemAction->gotoFrameAndPlay(0, 16, true);		
	}
	else if (itemType == Item::Type::SHIELD) {
		itemNode = CSLoader::createNode(ActionPath::SHIELD_PATH);
		itemNode->setScale(0.8f);
		itemAction = CSLoader::createTimeline(ActionPath::SHIELD_PATH);	
		this->addChild(itemNode);
		itemNode->runAction(itemAction);
		itemAction->gotoFrameAndPlay(0, 16, true);		
	}	
}

//몬스터가 히어로를 때리려고 할 때 콜되는 함수.
void Hero::monsterAttackToHero(HitArea* attackArea) {
	if (HitArea::isIn(heroPosition->getArea(), attackArea->getArea())) //몬스터가 때렸는데 그 범위 안에 히어로가 있을 경우.
	{
		if (GameData::getInstance()->getItemMode() == GameData::ItemMode::SHIELD) {
			int durability = GameData::getInstance()->getShield()->getDurability();
			if (durability != 0) {
				this->startDefense();
				GameData::getInstance()->getShield()->setDurability(durability - 1);
				log("start Defense");
			}
			else {
				decreaseHp(1);
			}			
		}
		else {
			decreaseHp(1);
		}	
	}
}

void Hero::setHitArea(int area) {
	this->heroPosition->setArea(area);
}

//Hero 가 운동(회피, 공격, 점프, 앉기)중에는 다른 명령을 받지 않도록 만든다.
bool Hero::isAvailableCommand() {
	if (movementState == NULL)	return true;
	return movementState->isAvailableCommand();
	action->gotoFrameAndPlay(75, 95, true);//대기 모션
	itemAction->gotoFrameAndPlay(75, 95, true);
}

void Hero::startAttack() {
	if (GameData::getInstance()->getItemMode() == GameData::ItemMode::SWORD) {
		if (isAvailableCommand()) {
			setMovementState(new AttackMovementState(this));
			action->gotoFrameAndPlay(198, 211, false);//공격1
			itemAction->gotoFrameAndPlay(198, 211, false);
		}
	}	
}
void Hero::startAvoid() {
	if (isAvailableCommand()) {
		setMovementState(new AvoidMovementState(this));
		action->gotoFrameAndPlay(175, 187, false);//중간회피 
		itemAction->gotoFrameAndPlay(175, 187, false);
	}
}
void Hero::startSitDown() {
	if (isAvailableCommand()) {
		setMovementState(new SitdownMovementState(this));
		action->gotoFrameAndPlay(116, 128, false);//아래회피(sit 대신 dodge
		itemAction->gotoFrameAndPlay(116, 128, false);//아래회피(sit 대신 dodge
	}
}
void Hero::startJump() {
	if (isAvailableCommand()) {
		setMovementState(new JumpMovementState(this));
		action->gotoFrameAndPlay(97, 113, false);//위회피
		itemAction->gotoFrameAndPlay(97, 113, false);//위회피
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioPath::SOUND_JUMP_PATH.c_str());
	}
}

void Hero::startDefense() {
	if (isAvailableCommand()) {
		setMovementState(new DefenseMovementState(this));
		action->gotoFrameAndPlay(18, 25, false);//위회피
		itemAction->gotoFrameAndPlay(18, 25, false);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioPath::SOUND_BLOCK.c_str());
	}
}

void Hero::attackDamage() {
	if (field->getMonster() != NULL) {
		if (GameData::getInstance()->getSword()->getDurability() > 0) {
			int damage = GameData::getInstance()->getSword()->getDamage();
			field->getMonster()->damage(damage);
			attackEffect(damage);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioPath::SOUND_ATTACK_PATH.c_str());
		}		
	}
	else if (field->getChest() != NULL) {
		field->getChest()->damage(30);
		attackEffect(30);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioPath::SOUND_ATTACK_PATH.c_str());
	}
}

void Hero::attackEffect(int attackDamage) {
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
	itemAction->gotoFrameAndPlay(0, 16, true);
}

void Hero::decreaseHp(int hpSize)
{
	this->hp -= hpSize;
	
}
