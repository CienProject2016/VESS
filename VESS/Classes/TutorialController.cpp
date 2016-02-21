#include "TutorialController.h"
#include "TutorialInfo.h"

bool TutorialController::checkTutorialEvent(string eventType) {
	if (GameData::getInstance()->getIsTutorial()) {
		string currentEvent = TutorialInfo::getInstance()->getCurrentEvent();
		if (currentEvent == eventType) {
			if (TutorialInfo::getInstance()->getTutorialCheckSheet()->find(eventType)->second == false) {
				TutorialInfo::getInstance()->getTutorialCheckSheet()->insert(pair<string, bool>(eventType, true));
				auto gameScene = (GameScene*)Director::getInstance()->getRunningScene();
				auto tutorialLayer = (TutorialLayer*)gameScene->getChildByName("tutorialLayer");
				tutorialLayer->setVisible(true);
				tutorialLayer->setTouchEnabled(true);
				tutorialLayer->showNextTutorial();				
				return true;
			}
		}
	}
	return false;
}