#pragma once
#ifndef __TUTORIAL_INFO_H__
#define __TUTORIAL_INFO_H__
#include "cocos2d.h"
#include <string>
#include <map>
using namespace std;

class TutorialInfo {
private:
	TutorialInfo();
	~TutorialInfo();
	static TutorialInfo* instance;
	CC_SYNTHESIZE(string, currentEvent, CurrentEvent);
	CC_SYNTHESIZE(bool, DRAG_01, Drag01);
	CC_SYNTHESIZE(bool, EVADE_01, Evade01);
	map<string, bool>* tutorialCheckSheet;
public:
	static TutorialInfo* getInstance();
	void initTutorialInfo();
	map<string, bool>* getTutorialCheckSheet();
};


#endif // !__TUTORIAL_INFO_H__
