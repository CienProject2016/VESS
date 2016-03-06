#pragma once
#ifndef __STAGE_LEVEL_CONTROLLER_H__
#define __STAGE_LEVEL_CONTROLLER_H__

class StageLevelController {
public:
	static void setStageLevel(int);
	static void clearStage(int);
	static void initiateProperty();
};

#endif