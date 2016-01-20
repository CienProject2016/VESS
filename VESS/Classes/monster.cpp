#include "Monster.h"


Monster::Monster() {
}

Monster::~Monster() {

}

bool Monster::init()
{
	if (Unit::init())
	{
		hp_ = 100;
		window_size = fightLayerSize;
		origin = fightLayerOrigin;
		Node* node = CSLoader::createNode("Tauren.csb");
		this->addChild(node); //get animation data 
		timeline::ActionTimeline* action = CSLoader::createTimeline("Tauren.csb");
		node->setPosition(0, 0);
		node->runAction(action);
		action->gotoFrameAndPlay(26, 32, true);
		this->setPosition(Vec2(window_size.width * 0.7f, window_size.height * 0.4f));
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

void Monster::damage(int dam) {
	hp_ -= dam;
	log("monster HP is : %d", hp_);
	if (hp_ <= 0) {
		this->reciever->send(EVENT::MonsterDead);
	}
}

