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
	float max_avoid_time = 0.2f;	//�����ص� ����(����), ���ϴ� �ð��� ����(���� : s), ���� Ŀ������ ���ϴµ� ���� �ɸ���, ���� ��.
	float max_jump_time = 0.42f;	//�����ص� ����(����), �����ϴ� �ð��� ����(���� : s), ���� Ŀ������ ���� ��.
	float max_attack_time = 0.2f;	//�����ص� ����(����), �����ϴ� �ð��� ����(���� : s), ���� Ŀ������ �����ϴµ� ���� �ɸ���, ���� ��.
	float vertical_velocity = 0;	//�����ӵ�.
	Size window_size;				//���̾� ������ ������
	Vec2 origin;					//���̾��� ��ġ ��ǥ

	float avoidDistance;			//���Ҷ� ������ �������� �Ÿ�
	float attackDistance;			//������ ����� �������� �Ÿ�
public:

	static Hero* create();
	virtual bool init();

	void setPos(HeroState state);	//�� state �� ������ �� �� �Լ��� �� �����ν�, Hero �� ��ġ�� �缳���Ѵ�.
	Vec2 getStatePos(HeroState state);	//�� state �� ������ �� ������ Hero �� ��ġ�� �����Ѵ�. ����Ʈ�� ���� �������� ����Ͽ� ����� ���Ҵ�.

	virtual void update(float dt);
	bool isAvailableCommend();
	void attack();
	void jump();
	void avoid();
	void sitDown();
};
#endif