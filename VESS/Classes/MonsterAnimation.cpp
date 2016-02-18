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
	//plist �� �о� ������ �̹�����, �� fdsa01.png, fdsa02.png...�� ĳ�ÿ� �ִ´�.
	//ex) SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/basic_slime/stand/basic_slime_stand.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
}

RepeatForever* MonsterAnimation::makeAction(int imageCount, char* imageName, float frameTime) {
	cocos2d::Vector<SpriteFrame*> animFrames;	// ������ �̹����� ���� ����

												// star01.png, star02.png �� ���ϸ��� ������ ���� ������ �ϳ� �����.
	char str[100] = { 0 };

	// ĳ�� �س��� �̹����� �ϳ��� �����ͼ� 
	for (int i = 0; i < imageCount; i++) {
		sprintf(str, "%s%02d.png", imageName, i); // i ���� ���� basic00.png, basic01.png..���� �ȴ�.
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);		// ������� ���ϸ��� �̹����� ĳ�ÿ��� �����ͼ� animFrames ���ٰ� �ִ´�.
	}

	// �ִϸ��̼ǿ� ����� �̹������� �غ�Ǿ���.
	Animation *animation = Animation::createWithSpriteFrames(animFrames, frameTime);	// �غ�� �̹��� �����ӵ��� frameTime (s) ���� �ٲ㺸���ֵ��� �����ؼ� animation�� �����.   
	Animate *animate = Animate::create(animation);	// animation ������ �̿��ؼ� Animate �׼��� �����.
	return RepeatForever::create(animate);	// ��� �����̵��� RepeatForever �� ����ش�.  
}
