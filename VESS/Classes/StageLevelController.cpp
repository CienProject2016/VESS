#include "StageLevelController.h"
#include "GameData.h"

void StageLevelController::setStageLevel(int level) {
	GameData::getInstance()->setStageLevel(level);
}

void StageLevelController::clearStage(int level) {
	GameData::getInstance()->getStageList()->at(level).setIsClear(true);
}