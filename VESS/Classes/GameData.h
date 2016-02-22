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
#include <map>

class GameData
{
public:
	enum ItemMode { SWORD, SHIELD };
	enum UpgradePhase { UPGRADE, REPAIR};
	static GameData* getInstance();
	ItemMode getItemMode();
	ItemMode getUpgradeItemMode();
	void setItemMode(ItemMode);
	Stage getCurrentStageInfo();
	void loadSaveInfo();
	void resetInfo();
private:
	ItemMode itemMode;
	static GameData* instance_;
	void setTutorialInfo();
	CC_SYNTHESIZE(vector<Tutorial>*, tutorialList, TutorialList);
	CC_SYNTHESIZE(vector<Stage>*, stageList, StageList);	
	CC_SYNTHESIZE(int, topStage, TopStage);
	CC_SYNTHESIZE(int, stageLevel, StageLevel);
	CC_SYNTHESIZE(Stage, stage, Stage);
	CC_SYNTHESIZE(int, gold, Gold);
	CC_SYNTHESIZE(int, costume, Costume);
	CC_SYNTHESIZE(int, movingDistance, MovingDistance);
	CC_SYNTHESIZE(vector<Dialog>*, dialogList, DialogList);
	CC_SYNTHESIZE(int, key, Key);
	CC_SYNTHESIZE(vector<Sword*>*, swordList, SwordList);
	CC_SYNTHESIZE(vector<Shield*>*, shieldList, ShieldList);
	CC_SYNTHESIZE(Sword*, sword, Sword);
	CC_SYNTHESIZE(Shield*, shield, Shield);
	CC_SYNTHESIZE(UpgradePhase, recentUpgradePhase, RecentUpgradePhase);
	CC_SYNTHESIZE(bool, isTutorial, IsTutorial);
	CC_SYNTHESIZE(bool, isInTutorial, IsInTutorial);
	CC_SYNTHESIZE(bool, isPause, IsPause);
	CC_SYNTHESIZE(bool, isCheatMode, IsCheatMode);
	CC_SYNTHESIZE(Item::Grade, currentUpgradeGrade, CurrentUpgradeGrade);
	GameData();
	~GameData();
	void setDialogInfo();
	void setUpgradeInfo();
	void setStageInfo();

};

#endif // __GAME_DATA_H__


