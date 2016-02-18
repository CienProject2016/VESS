#include "MonsterAnimation.h"



MonsterAnimation::MonsterAnimation(Monster* monster) {
	this->monster = monster;
	switch (monster->kind) {
	case Monster::Tauren:
		break;
	case Monster::Slime:
		attackCount = 3;
		attack = (RepeatForever**)malloc(sizeof(RepeatForever*) * attackCount);
		ReadyForPlist("animation/basic_slime/stand/basic_slime_stand.plist");
		ReadyForPlist("animation/basic_slime/attack1/basic_slime_attack0.plist");
		ReadyForPlist("animation/basic_slime/attack2/basic_slime_attack1_0.plist");
		ReadyForPlist("animation/basic_slime/attack2/basic_slime_attack1_1.plist");

		stand = makeAction(8, "basic_slime_stand_", 0.1f);
		attack[0] = makeAction(20, "basic_slime_attack0_", 0.05f);
		attack[1] = makeAction(42, "basic_slime_attack1_", 0.08f);
		break;
	}
}

void MonsterAnimation::changeAction(animKind kind) {
	monster->image->stopAllActions();
	//monster->image->runAction(animation);
	monster->removeChild(monster->image);

	
	monster->image = Sprite::create("animation/basic_slime/stand/basic_slime_stand_00.png");
	monster->image->setPosition(Vec2(fightLayerSize.width * 0.7f - 190, fightLayerSize.height * 0.4f + 110));
	monster->image->setScale(2.8f);
	monster->addChild(monster->image);
	
	monster->image->runAction(makeAction(20, "basic_slime_attack0_", 0.05f));


}

void MonsterAnimation::playAttack(int num) {
	int number = 0;
	if (num < attackCount && 0 <= num) number = num;
	switch (monster->kind) {
	case Monster::Tauren:
		break;
	case Monster::Slime:
		changeAction(attack[num]);
		break;
	}
}
void MonsterAnimation::playDamage() {}
void MonsterAnimation::playDead() {}
void MonsterAnimation::playStand() {
	switch (monster->kind) {
	case Monster::Tauren:
		break;
	case Monster::Slime:
		changeAction(stand);
		break;
	}
}

RepeatForever* makeAction(animKind kind) {

}

void MonsterAnimation::ReadyForPlist(char* plist) {
	//plist 를 읽어 각각의 이미지들, 즉 fdsa01.png, fdsa02.png...를 캐시에 넣는다.
	//ex) SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/basic_slime/stand/basic_slime_stand.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
}

RepeatForever* MonsterAnimation::makeAction(int imageCount, char* imageName, float frameTime) {
	cocos2d::Vector<SpriteFrame*> animFrames;	// 각각의 이미지를 담을 공간

												// star01.png, star02.png 등 파일명을 가지고 있을 변수를 하나 만든다.
	char str[100] = { 0 };

	// 캐시 해놓은 이미지를 하나씩 가져와서 
	for (int i = 0; i < imageCount; i++) {
		sprintf(str, "%s%02d.png", imageName, i); // i 값에 따라 basic00.png, basic01.png..등이 된다.
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);		// 만들어진 파일명의 이미지를 캐시에서 가져와서 animFrames 에다가 넣는다.
	}

	// 애니메이션에 사용할 이미지들이 준비되었다.
	Animation *animation = Animation::createWithSpriteFrames(animFrames, frameTime);	// 준비된 이미지 프레임들을 frameTime (s) 마다 바꿔보여주도록 설정해서 animation을 만든다.   
	Animate *animate = Animate::create(animation);	// animation 설정을 이용해서 Animate 액션을 만든다.
	return RepeatForever::create(animate);	// 계속 움직이도록 RepeatForever 로 잡아준다.  
}
