
#include "Monster.h"
#include "GameData.h"
#include "FightLayer.h"

using namespace std;

Monster::Monster() {}

Monster::~Monster() {}

void Monster::init(FightLayer* layer, Monster::Name name)
{
	if (Unit::init())
	{
		kind = name;
		field = layer;
		initWindowSize();
		initImage(name);
		initHp(name);
		this->scheduleUpdate();
	}	
}

void Monster::initWindowSize() {
	this->windowSize = fightLayerSize;
	this->origin = fightLayerOrigin;
}

void Monster::initImage(Monster::Name name) {

	image = CSLoader::createNode("animation/Tauren.csb");
	this->addChild(image); //get animation data 

	timeline::ActionTimeline* action = CSLoader::createTimeline("animation/Tauren.csb");
	image->setPosition(0, 0);
	image->runAction(action);
	action->gotoFrameAndPlay(26, 32, true);
	this->setPosition(Vec2(windowSize.width * 0.7f, windowSize.height * 0.4f));
}

void Monster::update(float delta) {

}

void Monster::initHp(Monster::Name name) {
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

Monster* Monster::create(FightLayer* layer, Monster::Name name)
{
	Monster *monster = new Monster();
	monster->init(layer, name);
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

int MonsterInfo::getHp(Monster::Name name) {
	return 100;
}

MonsterBehaviorPattern::MonsterBehaviorPattern() {}

void MonsterBehaviorPattern::update(float delta) {}

MonsterAnimation::MonsterAnimation(Monster* monster, Monster::Name) {

}

void MonsterAnimation::playAttack(int num) {}
void MonsterAnimation::playDamage() {}
void MonsterAnimation::playDead() {}

RepeatForever* MonsterAnimation::makeAction(char** plist, int plistCount, int imageCount, char* imageName, float frameTime) {
	//plist �� �о� ������ �̹�����, �� fdsa01.png, fdsa02.png...�� ĳ�ÿ� �ִ´�.
	//ex) SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/basic_slime/stand/basic_slime_stand.plist");
	for (int i = 0; i < plistCount; i++)
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist[i]);

	cocos2d::Vector<SpriteFrame*> animFrames;	// ������ �̹����� ���� ����

	// star01.png, star02.png �� ���ϸ��� ������ ���� ������ �ϳ� �����.
	char str[100] = { 0 };

	// ĳ�� �س��� �̹����� �ϳ��� �����ͼ� 
	for (int i = 0; i < imageCount; i++) {
		sprintf(str, "%s%02d.png",imageName, i); // i ���� ���� basic00.png, basic01.png..���� �ȴ�.
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);		// ������� ���ϸ��� �̹����� ĳ�ÿ��� �����ͼ� animFrames ���ٰ� �ִ´�.
	}

	// �ִϸ��̼ǿ� ����� �̹������� �غ�Ǿ���.
	Animation *animation = Animation::createWithSpriteFrames(animFrames, frameTime);	// �غ�� �̹��� �����ӵ��� frameTime (s) ���� �ٲ㺸���ֵ��� �����ؼ� animation�� �����.   
	Animate *animate = Animate::create(animation);	// animation ������ �̿��ؼ� Animate �׼��� �����.
	return RepeatForever::create(animate);	// ��� �����̵��� RepeatForever �� ����ش�.  
}
