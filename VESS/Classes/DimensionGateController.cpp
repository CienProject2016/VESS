#include "DimensionGateController.h"
#include "GameData.h"

void DimensionGateController::changeItemPosition() {
	switch (GameData::getInstance()->getItemMode()) {
	case GameData::ItemMode::SWORD:
		GameData::getInstance()->setItemMode(GameData::ItemMode::SHIELD);
		CCLOG("ItemMode - SHIELD");
		break;
	case GameData::ItemMode::SHIELD:
		GameData::getInstance()->setItemMode(GameData::ItemMode::SWORD);
		CCLOG("ItemMode - SWORD");
		break;
	default:
		CCLOG("DimensionGateController - ItemMode 정보 오류");
		break;
	}
}