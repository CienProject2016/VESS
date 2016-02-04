#pragma once
#ifndef __DIALOG_LAYER__
#define __DIALOG_LAYER__
#include "cocos2d.h"
#include "Dialog.h"

USING_NS_CC;
using namespace std;
class DialogLayer : public Layer
{
private:
	unsigned char* textJson;
	vector<Dialog> *dialogData;
	Layer* textLayer;
public:
	virtual bool init();	
	void nextScene();
	CREATE_FUNC(DialogLayer);
}; 

#endif // __DIALOG_LAYER__