#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <string>

USING_NS_CC;

class Settings : public cocos2d::CCLayerColor
{
public:
	Settings();
	~Settings();
	static cocos2d::Scene* createScene();
	virtual bool init();
	
	CREATE_FUNC(Settings);
private:	
	void bgmClicked(Ref* pSender);
	void bgmoffClicked(Ref* pSender);
	void bgmSoundUpClicked(Ref* pSender);
	void bgmSoundDownClicked(Ref* pSender);
	void effectClicked(Ref* pSender);
	void effectoffClicked(Ref* pSender);
	void effectSoundUpClicked(Ref* pSender);
	void effectSoundDownClicked(Ref* pSender);
	void exitClicked(Ref* pSender);
	void emptymenuClicked(Ref* pSender);
};

#endif // __SETTINGS_H__
