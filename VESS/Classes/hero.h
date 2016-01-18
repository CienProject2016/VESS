#include "Unit.h"
#include "WindowSize.h"
#ifndef __HERO_H__
#define __HERO_H__

class Hero: public Unit{
private:
	enum HeroState {STAY = 0, ATTACK_S = 1,  JUMP_S = 2,  AVOID_S = 3,  SIT_S = 4		//START
							, ATTACK_E = 11, JUMP_E = 12, AVOID_E = 13, SIT_E = 14};	//END
	HeroState state = STAY;
	float work_timer = 0;
	float max_avoid_time = 0.2f;	//수정해도 좋음(변수), 피하는 시간을 뜻함(단위 : s), 값이 커질수록 피하는데 오래 걸리고, 높이 뜀.
	float max_jump_time = 0.42f;	//수정해도 좋음(변수), 점프하는 시간을 뜻함(단위 : s), 값이 커질수록 높이 뜀.
	float max_attack_time = 0.2f;	//수정해도 좋음(변수), 공격하는 시간을 뜻함(단위 : s), 값이 커질수록 공격하는데 오래 걸리고, 높이 뜀.
	float vertical_velocity = 0;
	Size window_size;
	Vec2 origin;

	//어디까지 피하고 점프할지의 거리
	float avoidDistance;
	float attackDistance;
public:

	static Hero* create();
	virtual bool init();

	void setPos(HeroState state);

	virtual void update(float dt);
	bool isAvailableCommend();
	void attack();
	void jump();
	void avoid();
	void sitDown();
};
#endif