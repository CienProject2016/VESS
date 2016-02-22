#pragma once
#ifndef __MINI_POPUP_H__
#define __MINI_POPUP_H__

#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;
class MiniPopupLayer : public Layer{
public:
	MiniPopupLayer();
	~MiniPopupLayer();
	virtual bool init(string);
	static MiniPopupLayer* create(string);
	void setMessage(string);
private:
	string createMessage;
	virtual bool onTouchBegan(Touch* touch_, Event* event_);
};

#endif