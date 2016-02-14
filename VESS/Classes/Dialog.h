#pragma once
#ifndef __DIALOG_H__
#define __DIALOG_H__
#include <string>
#include "cocos2d.h"

using namespace std;

/*
	대화를 위한 클래스
*/
class Dialog
{
public:
	enum Position { LEFT, RIGHT };
	Dialog();
	~Dialog();
private:
	CC_SYNTHESIZE(Dialog::Position, position, Position);
	CC_SYNTHESIZE(string, name, Name);
	CC_SYNTHESIZE(string, dialogue, Dialogue);
	CC_SYNTHESIZE(string, background, Background);
	CC_SYNTHESIZE(string, image, Image);
};

#endif // __DIALOG_H__