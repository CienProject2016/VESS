

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
			if (1.1f < timer) {	//애니메이션 실행이 끝나면.
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