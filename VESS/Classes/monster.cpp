
#include "Monster.h"
#include "GameData.h"
#include "FightLayer.h"
#include "MonsterAnimation.h"
#include "MonsterInfo.h"
#include "MonsterBehaviorPattern.h"

using namespace std;

Monster::Monster() {}

Monster::~Monster() {
	delete anim;
	delete behavior;
}

void Monster::init(FightLayer* layer, Monster::Kind kind, int health){
	if (Unit::init())
	{
		this->kind = kind;
		field = layer;
		initWindowSize();
		initImage();
		initBehavior();
		initHp(health);
		this->scheduleUpdate();
	}	
}

void Monster::initWindowSize() {
	this->windowSize = fightLayerSize;
	this->origin = fightLayerOrigin;
}

void Monster::initImage() {
	timeline::ActionTimeline* action;
	switch (kind) {
	case Tauren:
		image = CSLoader::createNode("animation/Tauren.csb");
		this->addChild(image);
		action = CSLoader::createTimeline("animation/Tauren.csb");
		image->setPosition(0, 0);
		image->runAction(action);
		action->gotoFrameAndPlay(26, 32, true);
		this->setPosition(Vec2(windowSize.width * 0.7f, windowSize.height * 0.38f));
		break;
	case Slime:
		anim = new MonsterAnimation(this);
		image = Sprite::create("animation/basic_slime/stand/basic_slime_stand_00.png");
		image->setPosition(Vec2(0,0));
		image->setScale(2.8f);
		this->addChild(image);
		anim->playStand();
		this->setPosition(Vec2(windowSize.width * 0.6f, windowSize.height * 0.41f));
		break;
	}
}

void Monster::initBehavior() {
	behavior = new MonsterBehaviorPattern(this);
}

//예시 함수.
void sangTeaESangUpdate() {}

void Monster::update(float delta) {

	sangTeaESangUpdate();	//ex 상태이상.

	//행동패턴 업데이트 부분.
	//나중에 추가될 상태이상 처리라던지의 내용은 행동패턴에 들어가기 알맞지 않으므로.
	//몬스터의 업데이트에서 behavior 로 update 를 전달함으로써
	//프로그래머가 직관적으로 무엇이 먼저 실행될지를 알 수 있다.
	behavior->update(delta);	
}

void Monster::initHp(int health) {
	this->hp = health;
	this->fullHp = health;
	auto currentHp = Label::createWithTTF("0", "fonts/arial.ttf", 40);
	currentHp->setPosition(Vec2(30, 80));
	currentHp->setColor(Color3B(0, 0, 0)); //black
	currentHp->setString(StringUtils::format("%d / %d", hp, fullHp));
	this->addChild(currentHp, 1);
	currentHp->setTag(3);
  
	hpBarDecreasing->setType(kCCProgressTimerTypeBar);
	hpBarDecreasing->setPercentage(100.0f);
	hpBarDecreasing->setPosition(Vec2(40, 80));
	hpBarDecreasing->setMidpoint(Vec2(0, 1));
	hpBarDecreasing->setBarChangeRate(Vec2(1,0));
	this->addChild(hpBarDecreasing);
}

Monster* Monster::create(FightLayer* layer, Monster::Kind kind, int health)
{
	Monster *monster = new Monster();
	monster->init(layer, kind, health);
	monster->autorelease();
	return monster;
}

void Monster::dropItem()
{
}

void Monster::damage(int dam) {
	hp -= dam;
	log("%f", 100 *hp / fullHp);
	hpBarDecreasing->setPercentage(100*hp/fullHp);
	auto currentHp = (Label*)getChildByTag(3);
	currentHp->setString(StringUtils::format("%d / %d", hp, fullHp));

	log("monster HP is : %d", hp);
	if (hp <= 0) {
		int currentGold = GameData::getInstance()->getGold();
		int currentStageLevel = GameData::getInstance()->getStageLevel();
		int monsterGold = GameData::getInstance()->getStageList()->at(currentStageLevel).getGold();
		GameData::getInstance()->setGold(currentGold + monsterGold);
		field->monsterDead();
	}
}



