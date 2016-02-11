#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class StartScene : public cocos2d::CCLayerColor
{
private:
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void setTouchListener();
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void settingClicked(cocos2d::Ref* pSender);

    
    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);
};

#endif // __START_SCENE_H__
