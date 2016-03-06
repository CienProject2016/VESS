#include "StageLevelController.h"
#include "GameData.h"
#include "SaveController.h"

void StageLevelController::setStageLevel(int level) {
	GameData::getInstance()->setStageLevel(level);	
}

void StageLevelController::initiateProperty() {
	GameData::getInstance()->getSword()->setDurability(GameData::getInstance()->getSword()->getMaxDurability());
	GameData::getInstance()->getShield()->setDurability(GameData::getInstance()->getShield()->getMaxDurability());
}

void StageLevelController::clearStage(int level) {
	GameData::getInstance()->getStageList()->at(level).setIsClear(true);
	if (GameData::getInstance()->getTopStage() <= level) {
		GameData::getInstance()->setTopStage(level+1);
		SaveController::save();
	}
}