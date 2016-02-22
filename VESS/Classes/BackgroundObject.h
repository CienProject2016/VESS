#include "cocos2d.h"
#include "WindowSize.h"
#ifndef __BACKGROUND_OBJECT_H__
#define __BACKGROUND_OBJECT_H__

USING_NS_CC;
using namespace std;
class BackgroundObject : public Node {
private:
	float speed;
	float* settingSpeed;
	float localSpeed;
	float accel;
	float accelTime;	//해당 스피드까지 도달하는데 걸리는 시간(단위 : 초)
	int imageWidth;
	BackgroundObject();
public:
	enum ScaleMode {FIGHTLAYER_WIDTH, FIGHTLAYER_HEIGHT, CUSTOMIZED_SIZE};
	enum AlignMode {CENTER, BOTTOM, TOP, LEFT, RIGHT, RIGHT_TOP, RIGHT_BOTTOM, LEFT_TOP, LEFT_BOTTOM};
	~BackgroundObject();
	void setSpeed(float* speed, float accel, float localSpeed);
	static BackgroundObject* create();
	virtual bool init();
	virtual void update(float dt);
	void setImage(string fileName);
	void setImage(string fileName, Vec2 position);
	void setImage(string fileName, Vec2 position, float scale);
	void setImage(string fileName, Vec2 position, float scale, BackgroundObject::AlignMode alignMode);
	void setImage(string fileName, Vec2 position, float scale, BackgroundObject::ScaleMode scaleMode);
	void setImage(string fileName, Vec2 position, float scale, BackgroundObject::ScaleMode scaleMode, BackgroundObject::AlignMode alignMode);
	void setImage(string fileName, Vec2 position, float scale, BackgroundObject::ScaleMode scaleMode, BackgroundObject::AlignMode alignMode, Vec2 pixel_of_TR);
};
#endif // __BACKGROUND_OBJECT_H__