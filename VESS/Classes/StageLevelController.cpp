#include "StageLevelController.h"
#include "GameData.h"

void StageLevelController::setStageLevel(int level) {
	GameData::getInstance()->setStageLevel(level);
}