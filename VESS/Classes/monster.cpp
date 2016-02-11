
#include "Monster.h"
#include "GameData.h"
#include "FightLayer.h"
using namespace std;

Monster::Monster() {
}

Monster::~Monster() {

}

bool Monster::init()
{
	if (Unit::init())
	{
		hp_ = 100;
		fullHp_ = hp_;

		window_size = fightLayerSize;
		origin = fightLayerOrigin;
		Node* node = CSLoader::createNode("animation/Tauren.csb");
		this->addChild(node); //get animation data 

		timeline::ActionTimeline* action = CSLoader::createTimeline("animation/Tauren.csb");
		node->setPosition(0, 0);
		node->runAction(action);
		action->gotoFrameAndPlay(26 , 32, true);
		this->setPosition(Vec2(window_size.width * 0.7f, window_size.height * 0.4f));

		auto currentHp = Label::createWithTTF("0", "fonts/arial.ttf", 50);
		currentHp->setPosition(Vec2(0, -40));
		currentHp->setColor(ccc3(0, 0, 0)); //black
		currentHp->setString(StringUtils::format("%d / %d", hp_,fullHp_));
		this->addChild(currentHp, 1);
		currentHp->setTag(3);
		return true;
	}	
	return false;
}

bool Monster::isDead()
{
	if (this->hp_ <= 0)
	{
		return true;
	}
	return false;
}

Monster* Monster::create()
{
	Monster *monster = new Monster();
	if(monster && monster->init())
	{
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return nullptr;
}

void Monster::dropItem()
{
}

void Monster::setParentLayer(FightLayer* layer) {
	field = layer;
}

void Monster::damage(int dam) {
	hp_ -= dam;
	
	auto currentHp = (Label*)getChildByTag(3);
	currentHp->setString(StringUtils::format("%d / %d", hp_, fullHp_));

	log("monster HP is : %d", hp_);
	if (hp_ <= 0) {
		field->monsterDead();
	}
}
