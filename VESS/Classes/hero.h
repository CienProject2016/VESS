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
	Size window_size;				//���̾� ������ ������
	Vec2 origin;					//���̾��� ��ġ ��ǥ
	timeline::ActionTimeline* action;

public:

	static Hero* create();
	virtual bool init();
	//void setPos(HeroState state);	//�� state �� ������ �� �� �Լ��� �� �����ν�, Hero �� ��ġ�� �缳���Ѵ�.
	//Vec2 getStatePos(HeroState state);	//�� state �� ������ �� ������ Hero �� ��ġ�� �����Ѵ�. ����Ʈ�� ���� �������� ����Ͽ� ����� ���Ҵ�.

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