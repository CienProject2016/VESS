#pragma once
#ifndef __TutorialLayer_H_
#define __TutorialLayer_H_
#include "cocos2d.h"
#include "WindowSize.h"
#include <vector>
#include "GameData.h"
#include "GameScene.h"

USING_NS_CC;

class TutorialLayer : public Layer
{
	private:
		virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event_);
		virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
		virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
		virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);

		vector<Tutorial> *tutorialData;
		vector<Tutorial>::iterator tutorialIterator;

		void setTouchListener();

	public:
		bool init();
		bool hasNextTutorial();
		void showNextTutorial();
		CREATE_FUNC(TutorialLayer);
};
#endif
