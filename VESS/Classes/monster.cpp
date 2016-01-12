#include "Monster.h"
using namespace std;

Monster::Monster() {

}

Monster::~Monster() {

}

bool Monster::init() {
	auto sprite = Sprite::create("Images/slime.png");
	return true;
}

bool Monster::init(const std::string& filename)
{
	CCLOG("fileName %s", filename);
	if (filename.empty())
	{
		CCLOG("Call Sprite::initWithFile with blank resource filename.");
		return false;
	}

	if (Unit::init())
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto sprite = Sprite::create("Images/" + filename + ".png");
		sprite->setPosition(Vec2(origin.x + visibleSize.width*0.5f, origin.y + visibleSize.height*0.5f));
		sprite->setScale(4.0f);
		sprite->setVisible(true);
		this->addChild(sprite);
		auto enemyMove = MoveTo::create(4, ccp(origin.x, origin.y + visibleSize.height*0.5f));
		auto enemyRelocate = MoveTo::create(0, ccp(origin.x + visibleSize.width*0.5f, origin.y + visibleSize.height*0.5f));

		auto seq = CCSequence::create(enemyMove, CCDelayTime::create(2), enemyRelocate, CCDelayTime::create(2), NULL);
		auto rep = CCRepeatForever::create(seq); //무한반복
		sprite->runAction(rep);
		return true;
	}	
	return false;
}

Monster* Monster::create(const std::string& filename)
{
	Monster *monster = new Monster();
	if(monster && monster->init(filename))
	{
		monster->autorelease();

		return monster;
	}
	CC_SAFE_DELETE(monster);
	return nullptr;
}

