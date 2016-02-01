#include "Unit.h"
#include "WindowSize.h"
#include "cocostudio\CocoStudio.h"
#include "HeroMovementState.h"
#ifndef __HERO_H__
#define __HERO_H__

using namespace cocostudio;
class Hero: public Unit, public EventSender {
private:

	HeroMovementState* movement_state;
	Size window_size;				//레이어 윈도우 사이즈
	Vec2 origin;					//레이어의 위치 좌표
	timeline::ActionTimeline* action;

public:

	static Hero* create();
	virtual bool init();
	//void setPos(HeroState state);	//각 state 가 시작할 때 이 함수를 콜 함으로써, Hero 의 위치를 재설정한다.
	//Vec2 getStatePos(HeroState state);	//각 state 가 시작할 때 설정된 Hero 의 위치를 리턴한다. 이펙트가 펑펑 터질때를 대비하여 만들어 놓았다.

	virtual void update(float dt);
	bool isAvailableCommand();
	void attack();
	void jump();
	void avoid();
	void sitDown();
	void attackEffect();

	void setMovementState(HeroMovementState* state);
};
#endif