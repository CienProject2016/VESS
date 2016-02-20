#pragma once
#ifndef __GAMEOVER_POPUP_H__
#define __GAMEOVER_POPUP_H__

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;
class GameoverPopupLayer : public Layer {
public:
	
	GameoverPopupLayer();
	~GameoverPopupLayer();
	virtual bool init(string);
	static GameoverPopupLayer* create(string);
private:
	string createMessage;
	virtual bool onTouchBegan(Touch* touch_, Event* event_);
};

#endif