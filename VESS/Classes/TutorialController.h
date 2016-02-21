#pragma once
#ifndef __TUTORIAL_CONTROLLER_H__
#define __TUTORIAL_CONTROLLER_H__
#include <string>
#include "TutorialLayer.h"
using namespace std;
class TutorialController {
public:
	static bool checkTutorialEvent(string);
};

#endif // !__TUTORIAL_CONTROLLER_H__
