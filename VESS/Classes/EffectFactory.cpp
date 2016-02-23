

#include "EffectFactory.h"
#include "MonsterInfo.h"
#include "FightLayer.h"



EffectFactory::EffectFactory() {}
EffectFactory::~EffectFactory() {}


void EffectFactory::init(EffectKind effect, Vec2 pos) {
	image = Sprite::create("animation/basic_slime/stand/basic_slime_stand_00.png");
	image->setPosition(pos);
	image->setScale(1.0f);
	this->addChild(image);
	this->kind = effect;
	timer = 0;
	this->scheduleUpdate();
	stopOnce = false;
	if (effect == SlimeDeadAnimation) {
		image->runAction(EffectFactory::makeAction(new MakeAnimationInfo(11, "basic_slime_dead_", 0.1f)));
		maxTimer = 3;
		image->setScale(2.8f);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioPath::SOUND_SLIME_DEAD.c_str());
	}
	else if (effect == SlimeAttack0) {
		image->runAction(EffectFactory::makeAction(new MakeAnimationInfo(6, "slime_attack_effect_0_", 0.05f)));
		maxTimer = 0.3f;
		image->setScale(2.8f);
		//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioPath::SOUND_SLIME_DEAD.c_str());
	}
	else if (effect == DamageEffect0) {
		image->runAction(EffectFactory::makeAction(new MakeAnimationInfo(6, "damage_effect_", 0.1f)));
		maxTimer = 0.6f;
		image->setScale(1.5f);
	}
	else if (effect == DamageEffect1) {
		image->runAction(EffectFactory::makeAction(new MakeAnimationInfo(6, "damage_effect_1_", 0.05f)));
		maxTimer = 0.3f;
		image->setScale(30);
	}
}
void EffectFactory::update(float delta) {
	timer += delta;
	if (maxTimer <= timer) {
		removeFromParent();
		
		EffectFactory* newEfxFactory = create(SlimeDeadAnimation, Vec2(0, 0));
		EffectFactory* effectFactory = new EffectFactory();
		effectFactory = newEfxFactory;
	}
	else {
		if (kind == SlimeDeadAnimation) {
			Vec2 pos = getPosition();
			pos.x -= delta * 500;
			setPosition(pos);
			if (1.1f < timer) {	//�ִϸ��̼� ������ ������.
				if (!stopOnce) {
					stopOnce = true;
					image->stopAllActions();
				}
				image->setOpacity(255 * (1- ( (timer-1.1f)/(maxTimer-1.1f) )));
			}
		}
	}
}

EffectFactory* EffectFactory::create(EffectKind effect, Vec2 pos) {
	EffectFactory* effectFactory = new EffectFactory();
	effectFactory->init(effect, pos);
	effectFactory->autorelease();
	return effectFactory;
}

RepeatForever* EffectFactory::makeAction(MakeAnimationInfo* info) {
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