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
	float vertical_velocity = 0;	//수직속도.
	Size window_size;				//레이어 윈도우 사이즈
	Vec2 origin;					//레이어의 위치 좌표

	float avoidDistance;			//피할때 어디까지 피할지의 거리
	float attackDistance;			//때릴때 어디쯤 때릴지의 거리
public:

	static Hero* create();
	virtual bool init();

	void setPos(HeroState state);	//각 state 가 시작할 때 이 함수를 콜 함으로써, Hero 의 위치를 재설정한다.
	Vec2 getStatePos(HeroState state);	//각 state 가 시작할 때 설정된 Hero 의 위치를 리턴한다. 이펙트가 펑펑 터질때를 대비하여 만들어 놓았다.

	virtual void update(float dt);
	bool isAvailableCommend();
	void attack();
	void jump();
	void avoid();
	void sitDown();
};
#endif