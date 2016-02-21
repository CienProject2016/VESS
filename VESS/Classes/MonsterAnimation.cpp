#include "MonsterAnimation.h"



MonsterAnimation::MonsterAnimation(Monster* monster) {
	this->monster = monster;
	switch (monster->kind) {
	case Monster::Tauren:
		break;
	case Monster::Slime:
		ReadyForPlist("animation/basic_slime/stand/basic_slime_stand.plist");
		ReadyForPlist("animation/basic_slime/attack1/basic_slime_attack0.plist");
		ReadyForPlist("animation/basic_slime/attack2/basic_slime_attack1_0.plist");
		ReadyForPlist("animation/basic_slime/attack2/basic_slime_attack1_1.plist");
		break;
	}
}

void MonsterAnimation::changePlistAction(MonsterInfo::AnimName anim) {
	monster->image->stopAllActions();	
	monster->image->runAction(makeAction(MonsterInfo::getAnimationInfo(monster->kind, anim)));
}

void MonsterAnimation::playAttack(int num) {
	switch (monster->kind) {
	case Monster::Tauren:
		break;
	case Monster::Slime:
		if (num == 0)	changePlistAction(MonsterInfo::attack0);
		if (num == 1)	changePlistAction(MonsterInfo::attack1);
		if (num == 2)	changePlistAction(MonsterInfo::attack2);
		if (num == 3)	changePlistAction(MonsterInfo::attack3);
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
		changePlistAction(MonsterInfo::stand);
		break;
	}
}

void MonsterAnimation::ReadyForPlist(char* plist) {
	//plist 를 읽어 각각의 이미지들, 즉 fdsa01.png, fdsa02.png...를 캐시에 넣는다.
	//ex) SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/basic_slime/stand/basic_slime_stand.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
}

RepeatForever* MonsterAnimation::makeAction(MakeAnimationInfo* info) {
	cocos2d::Vector<SpriteFrame*> animFrames;	// 각각의 이미지를 담을 공간
	char str[100] = { 0 };						// 파일명 변수.

	for (int i = 0; i < info->imageCount; i++) {
		sprintf(str, "%s%02d.png", info->imageName, i); // i 값에 따라 basic00.png, basic01.png..등이 된다.
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);		// 만들어진 파일명의 이미지를 캐시에서 가져와서 animFrames 에다가 넣는다.
	}

	Animation *animation = Animation::createWithSpriteFrames(animFrames, info->frameTime);	// 준비된 이미지 프레임들을 frameTime (s) 마다 바꿔보여주도록 설정해서 animation을 만든다.   
	Animate *animate = Animate::create(animation);	// animation 설정을 이용해서 Animate 액션을 만든다.
	delete info;
	return RepeatForever::create(animate);	// 계속 움직이도록 RepeatForever 로 잡아준다.  
}
