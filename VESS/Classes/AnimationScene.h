#ifndef __AnimationScene_SCENE_H__
#define __AnimationScene_SCENE_H__

#include "cocos2d.h"
#define locationx  5001


class AnimationScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	



	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(AnimationScene);
	

};

#endif 
