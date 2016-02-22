#pragma once
#ifndef __PAUSELAYER_H_
#define __PAUSELAYER_H_
#include "cocos2d.h"
#include "GameScene.h"
#include "GameData.h"
#include "WindowSize.h"
USING_NS_CC;
using namespace std;

class PauseLayer : public Layer
{
private:
	Size visibleSize;
	Vec2 origin;
	bool effectSoundOnOff;
	float effectVolume;
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void setTouchListener();
public:
	enum ZOrder { SMELTING_IMAGE, HAMMERING_IMAGE, QUENCHING_IMAGE, UPGRADE_IMAGE, REPAIR_IMAGE, COMPLETE_UPGRADE_BUTTON, COMPLETE_REPAIR_BUTTON, DIMENSION_GATE_IMAGE, ITEM_IMAGE, ITEM_NAME, UPGRADE_COMPLETE_LAYER, MINI_POPUP_LAYER, GRAY_LAYER, PAUSE_BUTTON };
	PauseLayer();
	~PauseLayer();
	virtual bool init();
	void PauseLayer::initBackground();
	void PauseLayer::initButton();
	void resumeButtonCallback(cocos2d::Ref* pSender, ui::Widget::TouchEventType type);
	void restartButtonCallback(cocos2d::Ref* pSender, ui::Widget::TouchEventType type);
	void bgmSoundButtonCallback(cocos2d::Ref* pSender, ui::Widget::TouchEventType type);
	void effectSoundButtonCallback(cocos2d::Ref* pSender, ui::Widget::TouchEventType type);
	Sprite* pauseBackground, *bgmSoundBackground, *effectSoundBackground;
	cocos2d::ui::Button* bgmSoundButton,*effectSoundButton, *resumeGameButton, *restartGameButton;

	
	CREATE_FUNC(PauseLayer);

};

#endif