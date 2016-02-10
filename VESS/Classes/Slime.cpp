#include "Slime.h"
#include "FightLayer.h"


Slime::Slime() {

}
Slime::~Slime() {
}

void Slime::changeState(SlimeState state) {
	if (state != currState) {
		if (currState == STAND)			image->stopAction(stand);
		else if (currState == ATTACK0)	image->stopAction(attack_00);	
		else if (currState == ATTACK1) 	image->stopAction(attack_01);

		if (state == STAND)			image->runAction(stand);
		else if (state == ATTACK0)	image->runAction(attack_00);
		else if (state == ATTACK1) 	image->runAction(attack_01);

		currState = state;
	}
}

void Slime::initImage() {
	stand = makeAction("animation/basic_slime/stand/basic_slime_stand.plist", 8, "basic_slime_stand_", 0.1f);
	attack_00 = makeAction("animation/basic_slime/attack1/basic_slime_attack0.plist", 20, "basic_slime_attack0_", 0.05f);
	attack_01 = makeAttack1();
	image = Sprite::create("animation/basic_slime/stand/basic_slime_stand_00.png");
	image->setPosition(Vec2(window_size.width * 0.7f - 190, window_size.height * 0.4f + 110));
	image->setScale(2.8f);

	this->addChild(image);
	image->runAction(stand);
}

bool Slime::init() {
	if (Monster::init())
	{
		//타입이 Slime 일 때에만 해당상태를 초기화.
		if (!strcmp(typeid(this).name(), "class Slime *"))	currState = SlimeState::STAND; 
		return true;
	}
	return false;
}
Slime* Slime::create() {
	Slime *monster = new Slime();
	if (monster && monster->init())
	{
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return nullptr;
}

void Slime::update(float delta) {

}

RepeatForever* Slime::makeAttack1() {
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/basic_slime/attack2/basic_slime_attack1_0.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/basic_slime/attack2/basic_slime_attack1_1.plist");
	cocos2d::Vector<SpriteFrame*> animFrames;
	char str[100] = { 0 };
	for (int i = 0; i < 42; i++) {
		sprintf(str, "basic_slime_attack1_%02d.png", i);
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	} 
	Animation *animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate *animate = Animate::create(animation); 
	return RepeatForever::create(animate);
}