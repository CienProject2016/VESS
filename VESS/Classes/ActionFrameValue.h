#pragma once
#ifndef __ACTION_FRAME_VALUE_H__
#define __ACTION_FRAME_VALUE_H__

#include "cocos2d.h"
class ActionFrameValue {
private:
	CC_SYNTHESIZE(int, startFrame, StartFrame);
	CC_SYNTHESIZE(int, endFrame, EndFrame);
public:
	ActionFrameValue();
	~ActionFrameValue();
	ActionFrameValue(int, int);
	void changeFrame(int, int);
};

#endif // !__ACTION_FRAME_VALUE_H__
