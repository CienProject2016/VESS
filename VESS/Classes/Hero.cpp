#include "Hero.h"
#include "FightLayer.h"
#include "MonsterInfo.h"
#include "Monster.h"
#include "ResourcePath.h"
#include "DefenseMovementState.h"
#include "TutorialController.h"

#define ANIMATION 10000

bool Hero::init()
{
	if (Unit::init())
	{
		windowSize = fightLayerSize;
		origin = fightLayerOrigin;
		Node* node = CSLoader::createNode("hero_csb/character.csb");
		node->setScale(0.8f);
		node->setName("actionNode");
		this->addChild(node); //get animation data 
		action = CSLoader::createTimeline("hero_csb/character.csb");
		action->setTag(ANIMATION);
		node->setPosition(0, 0);
		node->runAction(action);
		action->gotoFrameAndPlay(0, 16, true);

		itemNode = CSLoader::createNode("hero_csb/weapon_sword.csb");
		itemNode->setName("itemNode");
		itemNode->setScale(0.8f);
		this->addChild(itemNode);
		itemAction = CSLoader::createTimeline("hero_csb/weapon_sword.csb");
		itemNode->setPosition(0, 0);
		itemNode->runAction(itemAction);
		itemAction->gotoFrameAndPlay(0, 16, true);

		this->scheduleUpdate();
		avoidDistance = windowSize.width * 0.2f;
		attackDistance = windowSize.width * 0.4f;
		heroPosition = new HitArea();
		fullHp = 3;
		hp = fullHp;
		attackCount = 0;
		setMovementState(new StayMovementState(this));
		return true;
	}
	return false;
}

void Hero::setAnimation(HeroMovementState::State anim) {
	switch(anim) {
	case HeroMovementState::attack0:{
		attackCount++;
		if (attackCount > 2) {
			attackCount = 0;
		}
		switch(attackCount){
		case 0:
			action->gotoFrameAndPlay(37, 49, false);//공격1
			itemAction->gotoFrameAndPlay(37, 49, false);
			break;
		case 1:
			action->gotoFrameAndPlay(198, 211, false);//공격1
			itemAction->gotoFrameAndPlay(198, 211, false);
			break;
		case 2:
			action->gotoFrameAndPlay(218, 228, false);//공격1
			itemAction->gotoFrameAndPlay(218, 228, false);
			break;
		}
	}
		break;
	case HeroMovementState::attack1:
		break;
	case HeroMovementState::avoid_up:
		action->gotoFrameAndPlay(97, 113, false);//위회피
		itemAction->gotoFrameAndPlay(97, 113, false);//위회피
		break;
	case HeroMovementState::avoid_left:
		action->gotoFrameAndPlay(175, 187, false);//중간회피 
		itemAction->gotoFrameAndPlay(175, 187, false);
		break;
	case HeroMovementState::avoid_down:
		action->gotoFrameAndPlay(116, 128, false);//아래회피(sit 대신 dodge
		itemAction->gotoFrameAndPlay(116, 128, false);//아래회피(sit 대신 dodge
		break;
	case HeroMovementState::run:
		action->gotoFrameAndPlay(0, 16, true);//달리는 모션
		itemAction->gotoFrameAndPlay(0, 16, true);
		break;
	case HeroMovementState::stay:
		action->gotoFrameAndPlay(75, 95, true);//대기 모션
		itemAction->gotoFrameAndPlay(75, 95, true);
		break;
	case HeroMovementState::defence:
		action->gotoFrameAndPlay(18, 25, false);//위회피
		itemAction->gotoFrameAndPlay(18, 25, false);
		break;

	}
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
		action->gotoFrameAndPlay(0, 16, true);
	}
	else if (itemType == Item::Type::SHIELD) {
		itemNode = CSLoader::createNode(ActionPath::SHIELD_PATH);
		itemNode->setScale(0.8f);
		itemAction = CSLoader::createTimeline(ActionPath::SHIELD_PATH);	
		this->addChild(itemNode);
		itemNode->runAction(itemAction);
		itemAction->gotoFrameAndPlay(0, 16, true);	
		action->gotoFrameAndPlay(0, 16, true);
	}	
}

//몬스터가 히어로를 때리려고 할 때 콜되는 함수.
void Hero::monsterAttackToHero(HitArea* attackArea) {
	if (HitArea::isIn(heroPosition->getArea(), attackArea->getArea())&&hp!=0) //몬스터가 때렸는데 그 범위 안에 히어로가 있을 경우. 그리고 피가 0이 아닌경우
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
	else if(hp==0){
		
			itemAction->gotoFrameAndPlay(145, 174, false);
			action->gotoFrameAndPlay(145, 174, false);

		
	}
}

void Hero::setHitArea(int area) {
	this->heroPosition->setArea(area);
}

void Hero::startAttack() {
	if (GameData::getInstance()->getItemMode() == GameData::ItemMode::SWORD) {
		if (movementState->state == HeroMovementState::stay) {
			setMovementState(new AttackMovementState(this));
			TutorialController::checkTutorialEvent("drag_01");
		} else if (movementState->state == HeroMovementState::avoid_up) {
			//점프시 공격을 눌렀을 때 attack1 발동 (두번째 공격방법)
			//이곳에 코드를 넣으면 된다.
		}
	}
}

void Hero::startAvoid() {
	if (movementState->state == HeroMovementState::stay) {
		setMovementState(new AvoidMovementState(this));
	}
}
void Hero::startSitDown() {
	if (movementState->state == HeroMovementState::stay) {
		setMovementState(new SitdownMovementState(this));
	}
}
void Hero::startJump() {
	if (movementState->state == HeroMovementState::stay) {
		setMovementState(new JumpMovementState(this));
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioPath::SOUND_JUMP_PATH.c_str());
	}
}

void Hero::startDefense() {
	if (movementState->state == HeroMovementState::stay) {
		setMovementState(new DefenseMovementState(this));
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioPath::SOUND_BLOCK.c_str());
	}
}

void Hero::attackDamage() {
	if (field->getMonster() != NULL) {
		int damage = GameData::getInstance()->getSword()->getDamage();
		if (GameData::getInstance()->getSword()->getDurability() <= 0) {
			damage *= 0.2;
		}
		field->getMonster()->damage(damage);
		attackEffect(damage);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioPath::SOUND_ATTACK_PATH.c_str());
	}
	else if (field->getChest() != NULL) {
		int damage = GameData::getInstance()->getSword()->getDamage();
		if (GameData::getInstance()->getSword()->getDurability() <= 0) {
			damage *= 0.2;
		}
		field->getChest()->damage(damage);
		attackEffect(damage);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioPath::SOUND_ATTACK_PATH.c_str());
	}
}
void Hero::attackEffect(int attackDamage) {
}


void Hero::setParentLayer(FightLayer* layer) {
	field = layer;
}

void Hero::setMovementState(HeroMovementState* state) {
	movementState = state;
	setAnimation(movementState->state);
}

void Hero::decreaseHp(int hpSize)
{
	this->hp -= hpSize;
	EffectFactory* effect0 = EffectFactory::create(EffectFactory::DamageEffect0, Vec2(0, 200));
	this->addChild(effect0);

	EffectFactory* effect1 = EffectFactory::create(EffectFactory::DamageEffect1, Vec2(500, 500));
	field->addChild(effect1);
	
}
