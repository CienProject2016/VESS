#pragma once
#ifndef __DIALOG_LAYER__
#define __DIALOG_LAYER__
#include "cocos2d.h"

USING_NS_CC;
using namespace std;
class DialogLayer : public Layer
{
private:
	unsigned char* text_json;
public:
	virtual bool init();	
	CREATE_FUNC(DialogLayer);
}; 

#endif // __DIALOG_LAYER__