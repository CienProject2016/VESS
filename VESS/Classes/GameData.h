#pragma once
#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__

#include "cocos2d.h"
#include "Stage.h"
#include "Hero.h"
#include "Dialog.h"
#include "Tutorial.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "Shield.h"
#include "Sword.h"

class GameData
{
public:
	enum ItemMode { SWORD, SHIELD };
	enum UpgradePhase { UPGRADE, REPAIR};
	static GameData* getInstance();
	ItemMode getItemMode();
	ItemMode getUpgradeItemMode();
	void setItemMode(ItemMode);
private:
	ItemMode itemMode;
	static GameData* instance_;
	CC_SYNTHESIZE(vector<Tutorial>*, tutorialList, TutorialList);
	CC_SYNTHESIZE(vector<Stage>*, stageList, StageList);
	void setTutorialInfo();
	CC_SYNTHESIZE(int, stageLevel, StageLevel);
	CC_SYNTHESIZE(Stage, stage, Stage);
	CC_SYNTHESIZE(int, hero_hp, HeroHp);
	CC_SYNTHESIZE(int, gold, Gold);
	CC_SYNTHESIZE(int, costume, Costume);
	CC_SYNTHESIZE(int, moving_distance, MovingDistance);
	CC_SYNTHESIZE(vector<Dialog>*, dialogList, DialogList);
	CC_SYNTHESIZE(vector<Sword*>*, swordList, SwordList);
	CC_SYNTHESIZE(vector<Shield*>*, shieldList, ShieldList);
	CC_SYNTHESIZE(int, needed_upgrade_gold, NeededUpgradeGold);
	CC_SYNTHESIZE(int, needed_repair_gold , NeededRepairGold);
	CC_SYNTHESIZE(Sword*, sword, Sword);
	CC_SYNTHESIZE(Shield*, shield, Shield);
	CC_SYNTHESIZE(UpgradePhase, recentUpgradePhase, RecentUpgradePhase);
	GameData();
	~GameData();
	void setDialogInfo();
	void setUpgradeInfo();
	void setStageInfo();

};

#endif // __GAME_DATA_H__


