
#include "Chest.h"
#include "GameData.h"
#include "FightLayer.h"

using namespace std;

Chest::Chest() {
}

Chest::~Chest() {
}

bool Chest::init()
{
	if (Unit::init())
	{
		initWindowSize();
		initImage();
		initHp(10);
		this->scheduleUpdate();


		return true;
	}
	return false;
}

void Chest::initWindowSize() {
	this->windowSize = fightLayerSize;
	this->origin = fightLayerOrigin;
}

void Chest::initImage() {

	image = Sprite::create("Images/chest.png");
	this->addChild(image); //get animation data 
	image->setPosition(0, 0);
	this->setPosition(Vec2(windowSize.width * 0.7f, windowSize.height * 0.4f));
}


void Chest::update(float delta) {

}

void Chest::initHp(int hp) {
	this->hp = hp;
	this->fullHp = hp;
	auto currentHp = Label::createWithTTF("0", "fonts/arial.ttf", 50);
	currentHp->setPosition(Vec2(0, -40));
	currentHp->setColor(ccc3(0, 0, 0)); //black
	currentHp->setString(StringUtils::format("%d / %d", hp, fullHp));
	this->addChild(currentHp, 1);
	currentHp->setTag(3);
	//hpBar = CCSprite::create("Images/chestHpBar.png");
	//hpBarDecreasing = CCProgressTimer::create(hpBar);
}

bool Chest::isDead()
{
	if (this->hp <= 0)
	{
		dropItem();
		return true;
	}
	return false;
}

Chest* Chest::create()
{
	Chest *chest = new Chest();
	if (chest && chest->init())
	{
		chest->autorelease();
		return chest;
	}
	CC_SAFE_DELETE(chest);
	return nullptr;
}

void Chest::dropItem()
{
	auto key = Sprite::create("Images/key.jpg");
	this->addChild(key);
	image->setPosition(0, 0);
	this->setPosition(Vec2(windowSize.width * 0.7f, windowSize.height * 0.4f));

	// key »ý¼º
}

void Chest::setParentLayer(FightLayer* layer) {
	field = layer;
}

void Chest::damage(int dam) {
	hp -= dam;

	auto currentHp = (Label*)getChildByTag(3);
	currentHp->setString(StringUtils::format("%d / %d", hp, fullHp));

	log("chest HP is : %d", hp);
	if (hp <= 0) {
		int currentGold = GameData::getInstance()->getGold();
		GameData::getInstance()->setGold(currentGold + 50);
		field->chestDead();
	}
}
