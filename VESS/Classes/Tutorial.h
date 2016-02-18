#pragma once
#ifndef __TUTORIAL_H__
#define __TUTORIAL_H__
#include <string>
#include "cocos2d.h"

using namespace std;

/*
Ʃ�丮���� ���� Ŭ����
*/
class Tutorial
{
public:
	enum Position { LEFT, RIGHT };
	Tutorial();
	~Tutorial();
private:
	CC_SYNTHESIZE(Tutorial::Position, position, Position);
	CC_SYNTHESIZE(string, tutorial, Tutorial);
	
};

#endif 