
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

void Monster::init(FightLayer* layer, Monster::Kind kind){
	if (Unit::init())
	{
		this->kind = kind;
		field = layer;
		initWindowSize();
		initImage();
		initBehavior();
		initHp();
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
		this->setPosition(Vec2(windowSize.width * 0.7f, windowSize.height * 0.4f));
		break;
	case Slime:
		anim = new MonsterAnimation(this);
		image = Sprite::create("animation/basic_slime/stand/basic_slime_stand_00.png");
		image->setPosition(Vec2(windowSize.width * 0.7f - 190, windowSize.height * 0.4f + 110));
		image->setScale(2.8f);
		this->addChild(image);
		anim->playStand();
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

void Monster::initHp() {
	this->hp = hp;
	this->fullHp = hp;
	auto currentHp = Label::createWithTTF("0", "fonts/arial.ttf", 50);
	currentHp->setPosition(Vec2(0, -40));
	currentHp->setColor(ccc3(0, 0, 0)); //black
	currentHp->setString(StringUtils::format("%d / %d", hp, fullHp));
	this->addChild(currentHp, 1);
	currentHp->setTag(3);
    //hpBar = CCSprite::create("Images/monsterHpBar.png");
	//hpBarDecreasing = CCProgressTimer::create(hpBar);
}

Monster* Monster::create(FightLayer* layer, Monster::Kind kind)
{
	Monster *monster = new Monster();
	monster->init(layer, kind);
	monster->autorelease();
	return monster;
}

void Monster::dropItem()
{
}

void Monster::damage(int dam) {
	hp -= dam;
	
	auto currentHp = (Label*)getChildByTag(3);
	currentHp->setString(StringUtils::format("%d / %d", hp, fullHp));

	log("monster HP is : %d", hp);
	if (hp <= 0) {
		int currentGold = GameData::getInstance()->getGold();
		GameData::getInstance()->setGold(currentGold + 50);
		field->monsterDead();
	}
}



