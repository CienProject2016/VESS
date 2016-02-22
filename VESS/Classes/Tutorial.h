#pragma once
#ifndef __TUTORIAL_H__
#define __TUTORIAL_H__
#include <string>
#include "cocos2d.h"

using namespace std;

/*
튜토리얼을 위한 클래스
*/
class Tutorial
{
public:
	enum Position { LEFT, RIGHT };
	Tutorial();
	~Tutorial();
private:
	CC_SYNTHESIZE(Tutorial::Position, position, Position);
	CC_SYNTHESIZE(string, lines, Lines);
	CC_SYNTHESIZE(string, eventType, EventType);
	
};

#endif 