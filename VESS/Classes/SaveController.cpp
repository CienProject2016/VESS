#include "SaveController.h"
#include "GameData.h"

void SaveController::save() {
	int topStageLevel = GameData::getInstance()->getTopStage();
	UserDefault::getInstance()->setIntegerForKey("topStageLevel", topStageLevel);
	UserDefault::getInstance()->flush();
}