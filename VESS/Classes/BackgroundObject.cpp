#include "BackgroundObject.h"

BackgroundObject::BackgroundObject() {}
BackgroundObject::~BackgroundObject() {}

void BackgroundObject::setSpeed(float* speed, float accel, float localSpeed) {
	this->settingSpeed = speed;
	this->accel = accel;
	this->localSpeed = localSpeed;
}

void BackgroundObject::setNoAccelSpeed() {
	speed = *settingSpeed * localSpeed;
}

float BackgroundObject::initBackgroundObject(float exObjectPos, float interval) {
	Vec2 pos = this->getPosition();
	int xx = (exObjectPos)* fightLayerSize.width;
	pos.x = xx + imageWidth;
	this->setPosition(pos);
	return ((float)(xx - scale * interval * imageWidth))/((float)fightLayerSize.width);
}

BackgroundObject* BackgroundObject::create() {
	BackgroundObject *background = new BackgroundObject();
	if (background && background->init()){
		background->autorelease();
		return background;
	}
	CC_SAFE_DELETE(background);
	return nullptr;
}

bool BackgroundObject::init() {
	if (Node::init()){
		speed = accel = imageWidth = 0;
		this->scheduleUpdate();
		return true;
	}
	return false;
}

void BackgroundObject::update(float delta) {
	Vec2 pos = this->getPosition();
	pos.x += delta * speed;
	this->setPosition(pos);


	if (getPosition().x < -imageWidth/2) {
		settingSpeed = NULL;
		this->removeFromParent();
	}
	else {
		if (speed < *settingSpeed * localSpeed * 0.98f)
			speed += accel * delta * localSpeed;
		if (speed > *settingSpeed * localSpeed * 1.02f)
			speed -= accel * delta * localSpeed;
	}
}


void BackgroundObject::setImage(string fileName) {	setImage(fileName, Vec2(0, 0));	}
void BackgroundObject::setImage(string fileName, Vec2 position) {	setImage(fileName, position, 1);	}
void BackgroundObject::setImage(string fileName, Vec2 position, float scale) {	setImage(fileName, position, scale, CUSTOMIZED_SIZE);	}
void BackgroundObject::setImage(string fileName, Vec2 position, float scale, BackgroundObject::AlignMode alignMode) {	setImage(fileName, position, scale, CUSTOMIZED_SIZE, alignMode);	}
void BackgroundObject::setImage(string fileName, Vec2 position, float scale, BackgroundObject::ScaleMode scaleMode) {	setImage(fileName, position, scale, scaleMode, CENTER);}
void BackgroundObject::setImage(string fileName, Vec2 position, float scale, BackgroundObject::ScaleMode scaleMode, BackgroundObject::AlignMode alignMode) {	setImage(fileName, position, scale, scaleMode, alignMode, Vec2(0, 0));	}
void BackgroundObject::setImage(string fileName, Vec2 position, float scale, BackgroundObject::ScaleMode scaleMode, BackgroundObject::AlignMode alignMode, Vec2 pixel_of_TR) {
	auto image = Sprite::create(fileName);
	Vec2 size = Vec2(image->getTexture()->getPixelsWide(), image->getTexture()->getPixelsHigh());
	float rate;
	Vec2 localPosition;
	Vec2 screenPosition;
	switch (scaleMode) {
	case FIGHTLAYER_WIDTH:
		rate = scale * fightLayerSize.width / size.x;
		break;
	case FIGHTLAYER_HEIGHT:
		rate = scale * fightLayerSize.height / size.y;
		break;
	case CUSTOMIZED_SIZE:
		rate = scale;
		break;
	}
	image->setScale(rate);
	size *= rate;
	switch (scaleMode) {
	case CENTER:
		localPosition = Vec2(0, 0);
		break;
	case BOTTOM:
		localPosition = Vec2(0, size.y / 2);
		break;
	case TOP:
		localPosition = Vec2(0, -size.y / 2);
		break;
	case LEFT:
		localPosition = Vec2(size.x / 2, 0);
		break;
	case RIGHT:
		localPosition = Vec2(-size.x / 2, 0);
		break;
	case RIGHT_TOP:
		localPosition = Vec2(-size.x / 2, -size.y / 2);
		break;
	case RIGHT_BOTTOM:
		localPosition = Vec2(-size.x / 2, size.y / 2);
		break;
	case LEFT_TOP:
		localPosition = Vec2(size.x / 2, -size.y / 2);
		break;
	case LEFT_BOTTOM:
		localPosition = Vec2(size.x / 2, size.y / 2);
		break;
	}
	imageWidth = size.x / 2;
	screenPosition = Vec2(position.x * fightLayerSize.width, position.y * fightLayerSize.height);
	this->scale = rate;
	this->setPosition(screenPosition + localPosition + pixel_of_TR);
	this->addChild(image);
}