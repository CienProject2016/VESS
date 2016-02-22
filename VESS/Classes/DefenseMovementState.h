#pragma once
#ifndef __DEFENSE_MOVEMENT_STATE_H__
#define __DEFENSE_MOVEMENT_STATE_H__
#include "HeroMovementState.h"
#include "ActionFrameValue.h"
class DefenseMovementState : public HeroMovementState {
private:
public:
	DefenseMovementState(Hero* parent, ActionFrameValue* actionFrame);
	~DefenseMovementState();
	DefenseMovementState(Hero* parent);
	virtual void update(float delta);
};

#endif