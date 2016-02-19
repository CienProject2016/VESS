
#include "Monster.h"
#include "GameData.h"
#include "FightLayer.h"

using namespace std;

Monster::Monster(){
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
	
	auto currentHp = (Label*)getChildByTag(3);
	currentHp->setString(StringUtils::format("%d / %d", hp, fullHp));

	log("monster HP is : %d", hp);
	if (hp <= 0) {
		int currentGold = GameData::getInstance()->getGold();
		GameData::getInstance()->setGold(currentGold + 50);
		field->monsterDead();
	}
}

RepeatForever* Monster::makeAction(char* plist, int imageCount, char* imageName, float frameTime) {
	//star-ani_default.plist 를 읽어 각각의 이미지들, 즉 star01.png, star02.png...를 캐시에 넣는다.
	//ex) SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/basic_slime/stand/basic_slime_stand.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);

	// 여기서부터는 에니메이션을 만드는 과정    
	// animation을 만들 각각의 이미지를 담을 공간을 만들어 두자.
	cocos2d::Vector<SpriteFrame*> animFrames;

	// star01.png, star02.png 등 파일명을 가지고 있을 변수를 하나 만든다.
	char str[100] = { 0 };

	// 캐시 해놓은 이미지를 하나씩 가져와서 
	for (int i = 0; i < imageCount; i++) {
		sprintf(str, "%s%02d.png",imageName, i); // i 값에 따라 basic00.png, basic.png..등이 된다.
													   // 만들어진 파일명의 이미지를 캐시에서 가져와 
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		// animFrames 에다가 넣는다.
		animFrames.pushBack(frame);
	}
	// 에니메이션에 사용할 이미지들이 준비되었다.

	// 준비된 이미지 프레임들을 0.1초마다 바꿔보여주도록 설정해서 animation을 만든다.    
	Animation *animation = Animation::createWithSpriteFrames(animFrames, frameTime);

	// animation 설정을 이용해서 Animate 액션을 만든다.
	Animate *animate = Animate::create(animation);

	// 계속 움직이도록 RepeatForever 로 잡아준다.    
	return RepeatForever::create(animate);
}
