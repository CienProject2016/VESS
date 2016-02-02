#pragma once
#ifndef _STAGE_CLEAR_LAYER_H__
#define __STAGE_CLEAR_LAYER_H__

#include "WindowSize.h"
#include "GameData.h"
#include "Stage.h"



USING_NS_CC; 

class StageClearLayer : public Layer
{
private:
	void nextStageCallback(cocos2d::Ref* pSender);
	void stageSelectCallback(cocos2d::Ref* pSender);
public:
	virtual bool init();
	//CREATE_FUNC(DialogLayer);
};

#endif 