#pragma once
#include "cocos2d.h"
#include "Stage.h"
#include "Hero.h"
#include "Dialog.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"

class GameData
{
private:
	static GameData* instance_;
	CC_SYNTHESIZE(Stage, stage_, Stage);
	CC_SYNTHESIZE(int, hero_hp_, HeroHp);
	CC_SYNTHESIZE(int, gold_, Gold);
	CC_SYNTHESIZE(int, costume_, Costume);
	CC_SYNTHESIZE(int, moving_distance_, MovingDistance);
	CC_SYNTHESIZE(vector<Dialog>*, dialogList_, DialogList);
	
	GameData();
	~GameData();
public:
	static GameData* getInstance();
};