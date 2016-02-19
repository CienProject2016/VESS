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
	//plist �� �о� ������ �̹�����, �� fdsa01.png, fdsa02.png...�� ĳ�ÿ� �ִ´�.
	//ex) SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/basic_slime/stand/basic_slime_stand.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
}

RepeatForever* MonsterAnimation::makeAction(MakeAnimationInfo* info) {
	cocos2d::Vector<SpriteFrame*> animFrames;	// ������ �̹����� ���� ����
	char str[100] = { 0 };						// ���ϸ� ����.

	for (int i = 0; i < info->imageCount; i++) {
		sprintf(str, "%s%02d.png", info->imageName, i); // i ���� ���� basic00.png, basic01.png..���� �ȴ�.
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);		// ������� ���ϸ��� �̹����� ĳ�ÿ��� �����ͼ� animFrames ���ٰ� �ִ´�.
	}

	Animation *animation = Animation::createWithSpriteFrames(animFrames, info->frameTime);	// �غ�� �̹��� �����ӵ��� frameTime (s) ���� �ٲ㺸���ֵ��� �����ؼ� animation�� �����.   
	Animate *animate = Animate::create(animation);	// animation ������ �̿��ؼ� Animate �׼��� �����.
	delete info;
	return RepeatForever::create(animate);	// ��� �����̵��� RepeatForever �� ����ش�.  
}
