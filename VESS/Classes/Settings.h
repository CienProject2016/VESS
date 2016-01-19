#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#include "SimpleAudioEngine.h"
#include "cocos2d.h"

using namespace cocos2d;
class Settings : public cocos2d::CCLayer
{
public:
	Settings();
	~Settings();
	static cocos2d::Scene* createScene();
	void menuClicked(Ref*);
	virtual bool init();

	CREATE_FUNC(Settings);
};

#endif // __SETTINGS_H__
