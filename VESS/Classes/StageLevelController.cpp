#include "StageLevelController.h"
#include "GameData.h"
#include "SaveController.h"

void StageLevelController::setStageLevel(int level) {
	GameData::getInstance()->setStageLevel(level);
}

void StageLevelController::clearStage(int level) {
	GameData::getInstance()->getStageList()->at(level).setIsClear(true);
	if (GameData::getInstance()->getTopStage() <= level) {
		GameData::getInstance()->setTopStage(level+1);
		SaveController::save();
	}
}