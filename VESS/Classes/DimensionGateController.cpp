#include "DimensionGateController.h"
#include "GameData.h"
#include "ResourcePath.h"

void DimensionGateController::changeItemPosition(Hero* daughter) {
	switch (GameData::getInstance()->getItemMode()) {
	case GameData::ItemMode::SWORD:
		GameData::getInstance()->setItemMode(GameData::ItemMode::SHIELD);
		daughter->changeItemAction(Item::Type::SHIELD);
		CCLOG("ItemMode - SHIELD");
		break;
	case GameData::ItemMode::SHIELD:
		GameData::getInstance()->setItemMode(GameData::ItemMode::SWORD);
		daughter->changeItemAction(Item::Type::SWORD);
		CCLOG("ItemMode - SWORD");
		break;
	default:
		CCLOG("DimensionGateController - ItemMode 정보 오류");
		break;
	}
}