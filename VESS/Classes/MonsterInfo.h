#pragma once
#ifndef __MONSTER_INFO_H__
#define __MONSTER_INFO_H__


#include "Monster.h"

class HitArea {
private:
	int area;
public:
	HitArea();
	HitArea(int area);
	enum Area { center = 1, up = 10, down = 100, left = 1000, right = 10000 };
	void setArea(Area area);
	void setArea(int area);
	int getArea();
	static bool isIn(int heroArea, int hitArea);
};

class MakeAnimationInfo {
public:
	int imageCount;
	char* imageName;
	float frameTime;
	MakeAnimationInfo(int imageCount, char* imageName, float frameTime) {
		this->imageCount = imageCount;
		this->imageName = imageName;
		this->frameTime = frameTime;
	}
};

class CsbFrameTimeInfo {
public:
	int start;
	int end;
	CsbFrameTimeInfo(int start, int end) {
		this->start = start;
		this->end = end;
	}
};

//객체를 생성하지 않음. 그냥 리턴만 함. (Controller)
class MonsterInfo {
private:
	MonsterInfo();
public:
	enum AnimName { stand, attack0, attack1, attack2, attack3, dead, damage };
	static int getHp(Monster::Kind kind);
	static MakeAnimationInfo* getAnimationInfo(Monster::Kind monster, AnimName anim);
	static CsbFrameTimeInfo* getCsbActionInfo(Monster::Kind monster, AnimName anim);
};

#endif // __MONSTER_INFO_H__