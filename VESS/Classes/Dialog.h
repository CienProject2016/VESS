#pragma once
#ifndef __DIALOG_H__
#define __DIALOG_H__
#include <string>
#include "cocos2d.h"

using namespace std;
class Dialog
{
public:
	enum Position { LEFT, RIGHT };
	Dialog();
	~Dialog();
private:
	CC_SYNTHESIZE(Dialog::Position, position_, Position);
	CC_SYNTHESIZE(string, name_, Name);
	CC_SYNTHESIZE(string, dialogue_, Dialogue);
	CC_SYNTHESIZE(string, background_, Background);
};

#endif // __DIALOG_H__