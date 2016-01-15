#pragma once

#include "cocos2d.h"

USING_NS_CC;

class BattleOperatorMenu : public Node {
private:
	Vec2 pos, local_pos;

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
	void createMenus();
	void initMainImage();
	void setMenu();
	Sprite *main_image;

	enum MenuState { CANCEL, ATTACK, JUMP, AVOID, SIT};
	MenuState menu_state;
	bool is_open;
public:
	Vec2 pos, first_touch;
	BattleOperator();
	~BattleOperator();
	void startController(Vec2 first_touch);
	void setTouchPos(Vec2 touch_pos);
	void endController();
};