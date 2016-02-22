#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "cocos2d.h"
#include "UpgradeLayer.h"
#include "FightLayer.h"
#include "TutorialLayer.h"
#include "GameData.h"
#include "Stage.h"
#include "WindowSize.h"

using namespace rapidjson;

class GameScene : public cocos2d::Layer
{
private:
	static int stage;
	UpgradeLayer* upgradeLayer;
	FightLayer* fightLayer;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
