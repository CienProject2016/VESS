#include "MonsterBehaviorPattern.h"
#include "MonsterAnimation.h"
#include "FightLayer.h"
#include "MonsterInfo.h"
#include "TutorialController.h"

MonsterBehaviorPattern::MonsterBehaviorPattern(Monster* parent) {
	timer = 0;
	monster = parent;
	setStateAndTimer(stand, 3);
	playAnimationForState();
}
bool MonsterBehaviorPattern::isStandState() {
	return true;
}

MonsterBehaviorPattern::MonsterBehaviorPattern() {}

void MonsterBehaviorPattern::setStateAndTimer(MonsterState state, float maxTimer) {
	setStateAndTimer(state, maxTimer, 10000);
}

void MonsterBehaviorPattern::setStateAndTimer(MonsterState state, float maxTimer, float attackTimer) {
	setStateAndTimer(state, maxTimer, attackTimer, 10000);
}

void MonsterBehaviorPattern::setStateAndTimer(MonsterState state, float maxTimer, float attackTimer, float effectTimer) {
	this->state = state;
	this->maxTimer = maxTimer;
	this->attackTimer = attackTimer;
	this->effectTimer = effectTimer;
	isOneAnimationAttack = false;
	isOneAttackEffect = false;
}

void MonsterBehaviorPattern::decisionBehavior() {
	switch (monster->kind) {
	case Monster::Tauren:
		if (state == stand)		setStateAndTimer(attack0, 1, 0.7f);
		else if (state == attack0)	setStateAndTimer(attack1, 0.7f, 0.4f);
		else if (state == attack1)	setStateAndTimer(attack2, 0.7f, 0.4f);
		else if (state == attack2)	setStateAndTimer(stand, 1);
		break;
	case Monster::Slime:
		if (state == stand)		setStateAndTimer(attack0, 1, 0.5f, 0.1f);
		else if (state == attack0)	setStateAndTimer(attack1, 3.36f, 2);
		else if (state == attack1)	setStateAndTimer(stand, 1);
		break;
	}
	playAnimationForState();
}

void MonsterBehaviorPattern::playAnimationForState() {
	switch (state) {
	case stand:
		monster->anim->playStand();
		break;
	case attack0:
		monster->anim->playAttack(0);
		break;
	case attack1:
		monster->anim->playAttack(1);
		break;
	case attack2:
		monster->anim->playAttack(2);
		break;
	case attack3:
		monster->anim->playAttack(3);
		break;
	case dead:
		monster->anim->playDead();
		break;
	}
}

void MonsterBehaviorPattern::attackToHero() {
	switch (monster->kind) {
	case Monster::Tauren:
		if (state == attack0)		monster->field->getDaughter()->monsterAttackToHero(new HitArea(HitArea::center + HitArea::right));
		else if (state == attack1)	monster->field->getDaughter()->monsterAttackToHero(new HitArea(HitArea::center + HitArea::right));
		else if (state == attack2)	monster->field->getDaughter()->monsterAttackToHero(new HitArea(HitArea::center + HitArea::right));
		break;
	case Monster::Slime:
		if (state == attack0)	monster->field->getDaughter()->monsterAttackToHero(new HitArea(HitArea::center + HitArea::right));
		else if (state == attack1) {
			monster->field->getDaughter()->monsterAttackToHero(new HitArea(HitArea::center + HitArea::right));
			if (!TutorialController::checkTutorialEvent("evade_01")) {
				TutorialController::checkTutorialEvent("evade_02");
			}
		}
		break;
	}
}

void MonsterBehaviorPattern::createEffect() {
	switch (monster->kind) {
	case Monster::Tauren:
		break;
	case Monster::Slime:
		if (state == attack0) {
			EffectFactory* effect = EffectFactory::create(EffectFactory::SlimeAttack0, Vec2(0, 0));
			monster->addChild(effect);
		}
		break;
	}

}

void MonsterBehaviorPattern::update(float delta) {
	if (GameData::getInstance()->getIsInTutorial() == false) {
		timer += delta;
	}	
	if (maxTimer < timer) {
		timer = 0;
		decisionBehavior();
	}

	if (!isOneAnimationAttack && attackTimer < timer) {
		isOneAnimationAttack = true;
		attackToHero();
	}

	if (!isOneAttackEffect && attackTimer < timer) {
		isOneAttackEffect = true;
		createEffect();
	}
}