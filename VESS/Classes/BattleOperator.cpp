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
	this->localPosition = pos;
	this->pos = localPosition;
	this->image->setPosition(this->pos);
	this->image->setScale(1.0f);
	this->image->setVisible(false);
}

void BattleOperatorMenu::setVisible(bool visible) {
	this->image->setVisible(visible);
}

void BattleOperatorMenu::setPosition(Vec2 pos) {
	this->pos = pos + localPosition;
	this->image->setPosition(this->pos);
}

BattleOperator::BattleOperator() : isUsing(false) {
	menuState = CANCEL;
	isUsing = false;
	first_touch.x = first_touch.y = 0;
	pos.x = pos.y = 0;
	initMainImage();
	createMenu();
}
BattleOperator::~BattleOperator() {

}

void BattleOperator::initMainImage() {
	mainImage = Sprite::create("Images/base_battle_controller.png");
	mainImage->setPosition(first_touch);
	mainImage->setScale(1.0f);
	mainImage->setVisible(false);
	this->addChild(mainImage);
}

void BattleOperator::createMenu() {
	attack.setController(Sprite::create("Images/attack_controller_image.png"), Vec2(101, 0));
	jump.setController(Sprite::create("Images/jump_controller_image.png"), Vec2(0, 101));
	avoid.setController(Sprite::create("Images/avoid_controller_image.png"), Vec2(-101, 0));
	sit.setController(Sprite::create("Images/sitdown_controller_image.png"), Vec2(0, -101));
	this->addChild(attack.image);
	this->addChild(jump.image);
	this->addChild(avoid.image);
	this->addChild(sit.image);
}

void BattleOperator::setMenu() {
	attack.setVisible(false);
	jump.setVisible(false);
	avoid.setVisible(false);
	sit.setVisible(false);
	switch (menuState) {
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
	return menuState;
}

void BattleOperator::startController(Vec2 placeYouTouchedFirst) {
	isUsing = true;
	this->first_touch = placeYouTouchedFirst;
	mainImage->setPosition(placeYouTouchedFirst);
	mainImage->setVisible(true);
	attack.setPosition(placeYouTouchedFirst);
	jump.setPosition(placeYouTouchedFirst);
	avoid.setPosition(placeYouTouchedFirst);
	sit.setPosition(placeYouTouchedFirst);
}
void BattleOperator::setTouchPos(Vec2 touch_pos) {
	this->pos = touch_pos;
	Vec2 direction = pos - first_touch;
	if (direction.x * direction.x + direction.y * direction.y < 600) {
		menuState = CANCEL;
	} else {
		if (direction.y > direction.x) {
			if (direction.y > -direction.x) { menuState = JUMP; }
			else {							 menuState = AVOID; }
		} else {
			if (direction.y > -direction.x) { menuState = ATTACK; }
			else { menuState = SIT; }
		}
	}
	setMenu();
}

void BattleOperator::endController() {
	isUsing = false;
	mainImage->setVisible(false);
	attack.setVisible(false);
	jump.setVisible(false);
	avoid.setVisible(false);
	sit.setVisible(false);
}