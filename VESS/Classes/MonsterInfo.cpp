#include "MonsterInfo.h"
#include "MonsterAnimation.h"
#include "FightLayer.h"

HitArea::HitArea() {
	setArea(center);
}

HitArea::HitArea(int area) {
	setArea(area);
}

void HitArea::setArea(int area) {
	this->area = area;
}

void HitArea::setArea(Area area) {
	switch (area) {
	case center:
		this->area = center;
		break;
	case up:
		this->area = up;
		break;
	case down:
		this->area = down;
		break;
	case left:
		this->area = left;
		break;
	case right:
		this->area = right;
		break;
	}
}
int HitArea::getArea() {
	return this->area;
}
bool HitArea::isCenter(int area) {
	int buf = area;		//어떤 버퍼에 인수값을 받고.
	buf %= 10;			//해당 자릿수만큼 남기고,
	buf /= 1;			//해당 자릿수만큼 버리면,
	return (0 < buf);	//내가 원하는 지점의 지역만 남게된다.
}
bool HitArea::isUp(int area) {
	int buf = area;		//어떤 버퍼에 인수값을 받고.
	buf %= 100;			//해당 자릿수만큼 남기고,
	buf /= 10;			//해당 자릿수만큼 버리면,
	return (0 < buf);	//내가 원하는 지점의 지역만 남게된다.
}
bool HitArea::isDown(int area) {
	int buf = area;		//어떤 버퍼에 인수값을 받고.
	buf %= 1000;		//해당 자릿수만큼 남기고,
	buf /= 100;			//해당 자릿수만큼 버리면,
	return (0 < buf);	//내가 원하는 지점의 지역만 남게된다.
}
bool HitArea::isLeft(int area) {
	int buf = area;		//어떤 버퍼에 인수값을 받고.
	buf %= 10000;		//해당 자릿수만큼 남기고,
	buf /= 1000;		//해당 자릿수만큼 버리면,
	return (0 < buf);	//내가 원하는 지점의 지역만 남게된다.
}
bool HitArea::isRight(int area) {
	int buf = area;		//어떤 버퍼에 인수값을 받고.
	buf /= 10000;		//해당 자릿수만큼 버리면,
	return (0 < buf);	//내가 원하는 지점의 지역만 남게된다.
}
bool HitArea::isIn(int heroArea, int hitArea) {
	int buf = heroArea + hitArea;
	int iljaritsu = 0;
	while (0 < buf) {							//버퍼가 0보다 크다면 루프를 돈다.
		iljaritsu = buf % 10;					//버퍼의 일의 자릿수를 구하고,
		if (1 < iljaritsu)	return true;		//일의 자릿수가 2이면 리턴 트루
		buf /= 10;								//2가 아니라면 버퍼를 10으로 나누어 저장하고 루프를 다시 돈다.
	}
	return false;
}

int MonsterInfo::getHp(Monster::Kind kind) {
	switch (kind) {
	case Monster::Tauren:
		break;
	case Monster::Slime:
		break;
	}
	return 100;
}

MakeAnimationInfo* MonsterInfo::getAnimationInfo(Monster::Kind monster, AnimName anim) {
	switch (monster) {
	case Monster::Tauren:
		break;
	case Monster::Slime:
		if (anim == stand)	return new MakeAnimationInfo(8, "basic_slime_stand_", 0.1f);
		else if (anim == attack0)	return new MakeAnimationInfo(20, "basic_slime_attack0_", 0.05f);
		else if (anim == attack1)	return new MakeAnimationInfo(42, "basic_slime_attack1_", 0.08f);
		else if (anim == attack2) {}
		else if (anim == attack3) {}
		else if (anim == dead) {}
		else if (anim == damage) {}
		break;
	}
}
