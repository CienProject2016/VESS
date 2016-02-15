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
#include "Item.h"
class GameData
{
public:
	enum ItemMode { SWORD, SHIELD };	
	static GameData* getInstance();
	rapidjson::Document& getUpgradeSwordInfo();
	rapidjson::Document& getUpgradeShieldInfo();
	ItemMode getItemMode();
	ItemMode getUpgradeItemMode();
	void setItemMode(ItemMode);
private:
	ItemMode itemMode;
	static GameData* instance_;
	CC_SYNTHESIZE(Stage, stage_, Stage);
	CC_SYNTHESIZE(int, hero_hp_, HeroHp);
	CC_SYNTHESIZE(int, gold_, Gold);
	CC_SYNTHESIZE(int, costume_, Costume);
	CC_SYNTHESIZE(int, moving_distance_, MovingDistance);
	CC_SYNTHESIZE(vector<Dialog>*, dialogList_, DialogList);
	CC_SYNTHESIZE(int, needed_upgrade_gold_, NeededUpgradeGold);
	CC_SYNTHESIZE(int, needed_repair_gold_ , NeededRepairGold);
	CC_SYNTHESIZE(Sword, sword_, Sword);
	CC_SYNTHESIZE(Shield, shield_, Shield);

	rapidjson::Document upgradeSwordInfo;
	rapidjson::Document upgradeShieldInfo;
	GameData();
	~GameData();
	void setDialogInfo();
	void setUpgradeInfo();

};


