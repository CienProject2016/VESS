
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
		initWindowSize();
		initImage();
		initHp(100);
		this->scheduleUpdate();

		
		return true;
	}	
	return false;
}

void Monster::initWindowSize() {
	this->windowSize = fightLayerSize;
	this->origin = fightLayerOrigin;
}

void Monster::initImage() {

	image = CSLoader::createNode("animation/Tauren.csb");
	this->addChild(image); //get animation data 

	timeline::ActionTimeline* action = CSLoader::createTimeline("animation/Tauren.csb");
	image->setPosition(0, 0);
	image->runAction(action);
	action->gotoFrameAndPlay(26, 32, true);
	this->setPosition(Vec2(windowSize.width * 0.7f, windowSize.height * 0.4f));
}

void Monster::update(float delta) {
	if (isStarted) {
		damageEffectTimer -= delta;
		if (damageEffectTimer <= 0) {
			isStarted = false;
			this->removeChildByTag(4);
		}
	}

	//checkEffectEnd();

}

void Monster::initHp(int hp) {
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

bool Monster::isDead()
{
	if (this->hp <= 0)
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
	hp -= dam;
	attackDamageEffect(dam);
	//attackEffect();
	auto currentHp = (Label*)getChildByTag(3);
	currentHp->setString(StringUtils::format("%d / %d", hp, fullHp));

	log("monster HP is : %d", hp);
	if (hp <= 0) {
		int currentGold = GameData::getInstance()->getGold();
		GameData::getInstance()->setGold(currentGold + 50);
		field->monsterDead();
	}
}

// ���� �� ��Ÿ���� effect
void Monster::attackEffect() {
	effectController = EffectController::create(this, "animation/Tauren.csb", 3, Vec2(50, 50), 1);
	this->addChild(effectController);
}

// ���� �� ������ ��ġ�� ��Ÿ���� effect
void Monster::attackDamageEffect(int attackDamage) {
	auto currentDamage = Label::createWithTTF("0", "fonts/arial.ttf", 50);
	currentDamage->setPosition(Vec2(0, 200));
	currentDamage->setColor(ccc3(0, 0, 0)); //black
	currentDamage->setString(StringUtils::format("%d", attackDamage));
	this->addChild(currentDamage, 1);
	currentDamage->setTag(4);
	isStarted = true;
	//EffectFactory::makeEffect(this, "animation/MainScene.csb",40,Vec2(50,50),1);
	//effectController->setName("effectController23");

}
void Monster::checkEffectEnd() {
	if (effectController != NULL) {
		if (effectController->checkIsOver()) {
			this->removeChild(effectController);
			effectController = NULL;
		}
	}
}

RepeatForever* Monster::makeAction(char* plist, int imageCount, char* imageName, float frameTime) {
	//star-ani_default.plist �� �о� ������ �̹�����, �� star01.png, star02.png...�� ĳ�ÿ� �ִ´�.
	//ex) SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/basic_slime/stand/basic_slime_stand.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);

	// ���⼭���ʹ� ���ϸ��̼��� ����� ����    
	// animation�� ���� ������ �̹����� ���� ������ ����� ����.
	cocos2d::Vector<SpriteFrame*> animFrames;

	// star01.png, star02.png �� ���ϸ��� ������ ���� ������ �ϳ� �����.
	char str[100] = { 0 };

	// ĳ�� �س��� �̹����� �ϳ��� �����ͼ� 
	for (int i = 0; i < imageCount; i++) {
		sprintf(str, "%s%02d.png",imageName, i); // i ���� ���� basic00.png, basic.png..���� �ȴ�.
													   // ������� ���ϸ��� �̹����� ĳ�ÿ��� ������ 
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		// animFrames ���ٰ� �ִ´�.
		animFrames.pushBack(frame);
	}
	// ���ϸ��̼ǿ� ����� �̹������� �غ�Ǿ���.

	// �غ�� �̹��� �����ӵ��� 0.1�ʸ��� �ٲ㺸���ֵ��� �����ؼ� animation�� �����.    
	Animation *animation = Animation::createWithSpriteFrames(animFrames, frameTime);

	// animation ������ �̿��ؼ� Animate �׼��� �����.
	Animate *animate = Animate::create(animation);

	// ��� �����̵��� RepeatForever �� ����ش�.    
	return RepeatForever::create(animate);
}
