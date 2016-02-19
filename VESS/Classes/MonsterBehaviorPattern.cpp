#include "MonsterBehaviorPattern.h"
#include "MonsterAnimation.h"
#include "FightLayer.h"
#include "MonsterInfo.h"

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
	this->state = state;
	this->maxTimer = maxTimer;
	this->attackTimer = attackTimer;
	isOneAnimationAttack = false;
}

void MonsterBehaviorPattern::decisionBehavior() {
	switch (monster->kind) {
	case Monster::Tauren:
		break;
	case Monster::Slime:
		if (state == stand)		setStateAndTimer(attack0, 1, 0.5f);
		else if (state == attack0)	setStateAndTimer(attack1, 3.36f, 2);
		else if (state == attack1)	setStateAndTimer(stand, 1);
		playAnimationForState();
		break;
	}
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

void MonsterBehaviorPattern::AttackToHero() {
	switch (monster->kind) {
	case Monster::Tauren:
		break;
	case Monster::Slime:
		if (state == attack0)	monster->field->getDaughter()->monsterAttackToHero(new HitArea(HitArea::center + HitArea::left));
		else if (state == attack1)	monster->field->getDaughter()->monsterAttackToHero(new HitArea(HitArea::center + HitArea::left));
		break;
	}
}

void MonsterBehaviorPattern::update(float delta) {
	timer += delta;
	if (maxTimer < timer) {
		timer = 0;
		decisionBehavior();
	}

	if (!isOneAnimationAttack && attackTimer < timer) {
		isOneAnimationAttack = true;
		AttackToHero();
	}
}