#include "ActionFrameValue.h"
ActionFrameValue::ActionFrameValue() :startFrame(0), endFrame(0) {

}
ActionFrameValue::~ActionFrameValue() {

}

ActionFrameValue::ActionFrameValue(int startFrame, int endFrame) :startFrame(startFrame), endFrame(endFrame) {

}

void ActionFrameValue::changeFrame(int startFrame, int endFrame) {
	this->startFrame = startFrame;
	this->endFrame = endFrame;
}