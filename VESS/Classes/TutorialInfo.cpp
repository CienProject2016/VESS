#include "TutorialInfo.h"


TutorialInfo* TutorialInfo::instance = nullptr;

TutorialInfo::TutorialInfo() : currentEvent(""), DRAG_01(false), EVADE_01(false) {
	tutorialCheckSheet = new map<string, bool>();
	tutorialCheckSheet->insert(pair<string, bool>("drag_01", false));
	tutorialCheckSheet->insert(pair<string, bool>("evade_01", false));
	tutorialCheckSheet->insert(pair<string, bool>("evade_02", false));
}

TutorialInfo::~TutorialInfo() {

}

map<string, bool>* TutorialInfo::getTutorialCheckSheet() {
	return tutorialCheckSheet;
}

TutorialInfo* TutorialInfo::getInstance()
{
	if (instance == nullptr)
	{
		instance = new TutorialInfo();
	}
	return instance;
}

void TutorialInfo::initTutorialInfo() {
	this->currentEvent = "";
}

