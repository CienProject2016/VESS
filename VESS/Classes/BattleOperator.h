#pragma once

#include "cocos2d.h"

USING_NS_CC;

class BattleOperatorMenu : public Node {
private:
	Vec2 pos, localPosition;

public:
	Sprite* image;
	BattleOperatorMenu();
	BattleOperatorMenu(Sprite *image, Vec2 pos);
	~BattleOperatorMenu();
	void setController(Sprite *image, Vec2 pos);
	void setVisible(bool vis);
	void setPosition(Vec2 pos);
};

class BattleOperator : public Node {
private:
	BattleOperatorMenu jump, avoid, attack, sit;
	void createMenu();
	void initMainImage();
	void setMenu();
	Sprite *mainImage;
	enum OperatorState { CANCEL = 0, ATTACK = 1, JUMP = 2, AVOID = 3, SIT = 4};
	OperatorState menuState;
	bool isUsing;
public:
	Vec2 pos, first_touch;
	BattleOperator();
	~BattleOperator();
	void startController(Vec2 first_touch);
	void setTouchPos(Vec2 touch_pos);
	void endController();
	int getState();
};