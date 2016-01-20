
#include "BattleOperator.h"


BattleOperatorMenu::BattleOperatorMenu() {}
BattleOperatorMenu::BattleOperatorMenu(Sprite* image, Vec2 pos) {
	setController(image, pos);
}
BattleOperatorMenu::~BattleOperatorMenu() {
	delete image;
}

void BattleOperatorMenu::setController(Sprite *image, Vec2 pos) {
	this->image = image;
	this->local_pos = pos;
	this->pos = local_pos;
	this->image->setPosition(this->pos);
	this->image->setScale(1.0f);
	this->image->setVisible(false);
}

void BattleOperatorMenu::setVisible(bool vis) {
	this->image->setVisible(vis);
}

void BattleOperatorMenu::setPosition(Vec2 pos) {
	this->pos = pos + local_pos;
	this->image->setPosition(this->pos);
}

void BattleOperator::createMenus() {
	attack.setController(Sprite::create("Images/attackControllerImage.png"), Vec2(101, 0));
	jump.setController(Sprite::create("Images/jumpControllerImage.png"), Vec2(0, 101));
	avoid.setController(Sprite::create("Images/avoidControllerImage.png"), Vec2(-101, 0));
	sit.setController(Sprite::create("Images/sitdownControllerImage.png"), Vec2(0, -101));
	this->addChild(attack.image);
	this->addChild(jump.image);
	this->addChild(avoid.image);
	this->addChild(sit.image);
}

void BattleOperator::initMainImage() {
	main_image = Sprite::create("Images/baseBattleController.png");
	main_image->setPosition(first_touch);
	main_image->setScale(1.0f);
	main_image->setVisible(false);
	this->addChild(main_image);
}

BattleOperator::BattleOperator() : is_open(false) {
	menu_state = CANCEL;
	is_open = false;
	first_touch.x = first_touch.y = 0;
	pos.x = pos.y = 0;
	initMainImage();
	createMenus();
}
BattleOperator::~BattleOperator() {

}

void BattleOperator::setMenu() {
	attack.setVisible(false);
	jump.setVisible(false);
	avoid.setVisible(false);
	sit.setVisible(false);
	switch (menu_state) {
	case CANCEL :
		break;
	case ATTACK :
		attack.setVisible(true);
		break;
	case JUMP :
		jump.setVisible(true);
		break;
	case AVOID :
		avoid.setVisible(true);
		break;
	case SIT :
		sit.setVisible(true);
		break;
	}
}

int BattleOperator::getState() {
	return menu_state;
}

void BattleOperator::startController(Vec2 first_touch) {
	is_open = true;
	this->first_touch = first_touch;
	main_image->setPosition(first_touch);
	main_image->setVisible(true);
	attack.setPosition(first_touch);
	jump.setPosition(first_touch);
	avoid.setPosition(first_touch);
	sit.setPosition(first_touch);
}
void BattleOperator::setTouchPos(Vec2 touch_pos) {
	this->pos = touch_pos;
	Vec2 direction = pos - first_touch;
	if (direction.x * direction.x + direction.y * direction.y < 600) {
		menu_state = CANCEL;
	} else {
		if (direction.y > direction.x) {
			if (direction.y > -direction.x) { menu_state = JUMP; }
			else {							 menu_state = AVOID; }
		} else {
			if (direction.y > -direction.x) { menu_state = ATTACK; }
			else { menu_state = SIT; }
		}
	}
	setMenu();
}
void BattleOperator::endController() {
	is_open = false;
	main_image->setVisible(false);
	attack.setVisible(false);
	jump.setVisible(false);
	avoid.setVisible(false);
	sit.setVisible(false);
}