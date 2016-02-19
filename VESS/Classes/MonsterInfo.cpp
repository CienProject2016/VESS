#include "MonsterInfo.h"
#include "MonsterAnimation.h"

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
	int buf = area;		//� ���ۿ� �μ����� �ް�.
	buf %= 10;			//�ش� �ڸ�����ŭ �����,
	buf /= 1;			//�ش� �ڸ�����ŭ ������,
	return (0 < buf);	//���� ���ϴ� ������ ������ ���Եȴ�.
}
bool HitArea::isUp(int area) {
	int buf = area;		//� ���ۿ� �μ����� �ް�.
	buf %= 100;			//�ش� �ڸ�����ŭ �����,
	buf /= 10;			//�ش� �ڸ�����ŭ ������,
	return (0 < buf);	//���� ���ϴ� ������ ������ ���Եȴ�.
}
bool HitArea::isDown(int area) {
	int buf = area;		//� ���ۿ� �μ����� �ް�.
	buf %= 1000;		//�ش� �ڸ�����ŭ �����,
	buf /= 100;			//�ش� �ڸ�����ŭ ������,
	return (0 < buf);	//���� ���ϴ� ������ ������ ���Եȴ�.
}
bool HitArea::isLeft(int area) {
	int buf = area;		//� ���ۿ� �μ����� �ް�.
	buf %= 10000;		//�ش� �ڸ�����ŭ �����,
	buf /= 1000;		//�ش� �ڸ�����ŭ ������,
	return (0 < buf);	//���� ���ϴ� ������ ������ ���Եȴ�.
}
bool HitArea::isRight(int area) {
	int buf = area;		//� ���ۿ� �μ����� �ް�.
	buf /= 10000;		//�ش� �ڸ�����ŭ ������,
	return (0 < buf);	//���� ���ϴ� ������ ������ ���Եȴ�.
}
bool HitArea::isIn(int heroArea, int hitArea) {
	int buf = heroArea + hitArea;
	int iljaritsu = 0;
	while (0 < buf) {							//���۰� 0���� ũ�ٸ� ������ ����.
		iljaritsu = buf % 10;					//������ ���� �ڸ����� ���ϰ�,
		if (1 < iljaritsu)	return true;		//���� �ڸ����� 2�̸� ���� Ʈ��
		buf /= 10;								//2�� �ƴ϶�� ���۸� 10���� ������ �����ϰ� ������ �ٽ� ����.
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
