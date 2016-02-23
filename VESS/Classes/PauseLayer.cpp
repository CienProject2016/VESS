#include "PauseLayer.h"
#include "UpgradeLayer.h"
#include "EnterScene.h"
#include "StartScene.h"
PauseLayer::PauseLayer()
{}
PauseLayer::~PauseLayer()
{}
bool PauseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	
	auto grayLayer = CCLayerColor::create(Color4B(0, 0, 0, 255 * 0.5), visibleSize.width, visibleSize.height);
	grayLayer->setPosition(Vec2(0, 0));
	this->addChild(grayLayer, GRAY_LAYER, "grayLayer");

	effectSoundOnOff = true;
	effectVolume = CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume();
	

	initBackground();
	initButton();
	
	setTouchListener();

	return true;
}
void PauseLayer::initBackground()
{
	
	
	pauseBackground = Sprite::create("Images/pausebackground.png");
	pauseBackground->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height*0.5));
	
	bgmSoundBackground = Sprite::create("Images/bgmbackground.png");
	bgmSoundBackground->setPosition(Vec2(origin.x + visibleSize.width*0.5, origin.y + visibleSize.height*0.4));
	bgmSoundBackground->setScale(0.8f);

	effectSoundBackground = Sprite::create("Images/effectsoundbackground.png");
	effectSoundBackground->setPosition(Vec2(origin.x + visibleSize.width*0.5, origin.y + visibleSize.height*0.3));
	effectSoundBackground->setScale(0.8f);

	
	this->addChild(pauseBackground, ZOrder::PAUSE_BUTTON);
	this->addChild(effectSoundBackground, ZOrder::PAUSE_BUTTON);
	this->addChild(bgmSoundBackground, ZOrder::PAUSE_BUTTON);
}
void PauseLayer::initButton()
{
	restartGameButton = ui::Button::create("Images/restartgame.png", "Images/restartgame.png", ImagePath::DISABLE_BUTTON_PATH);
	restartGameButton->setPosition(Vec2(origin.x + visibleSize.width*0.38, origin.y + visibleSize.height*0.62));
	restartGameButton->setScale(0.8f);
	restartGameButton->addTouchEventListener(CC_CALLBACK_2(PauseLayer::restartButtonCallback, this));
	restartGameButton->setName("restartGameButton");

	resumeGameButton = ui::Button::create("Images/resumegame.png", "Images/resumegame.png", ImagePath::DISABLE_BUTTON_PATH);
	resumeGameButton->setPosition(Vec2(origin.x + visibleSize.width*0.62, origin.y + visibleSize.height*0.62));
	resumeGameButton->setScale(0.8f);
	resumeGameButton->addTouchEventListener(CC_CALLBACK_2(PauseLayer::resumeButtonCallback, this));
	resumeGameButton->setName("resumeGameButton");

	bgmSoundButton = ui::Button::create("Images/soundon.png", "Images/soundon.png", ImagePath::DISABLE_BUTTON_PATH);
	bgmSoundButton->setPosition(Vec2(origin.x + visibleSize.width*0.7, origin.y + visibleSize.height*0.4));
	bgmSoundButton->setScale(0.8f);
	bgmSoundButton->addTouchEventListener(CC_CALLBACK_2(PauseLayer::bgmSoundButtonCallback, this));
	bgmSoundButton->setName("bgmSoundButton");

	effectSoundButton = ui::Button::create("Images/soundon.png", "Images/soundon.png", ImagePath::DISABLE_BUTTON_PATH);
	effectSoundButton->setPosition(Vec2(origin.x + visibleSize.width*0.7, origin.y + visibleSize.height*0.3));
	effectSoundButton->setScale(0.8f);
	effectSoundButton->addTouchEventListener(CC_CALLBACK_2(PauseLayer::effectSoundButtonCallback, this));
	effectSoundButton->setName("effectSoundButton");

	this->addChild(restartGameButton, ZOrder::PAUSE_BUTTON);
	this->addChild(resumeGameButton, ZOrder::PAUSE_BUTTON);
	this->addChild(bgmSoundButton, ZOrder::PAUSE_BUTTON);
	this->addChild(effectSoundButton, ZOrder::PAUSE_BUTTON);
}
void PauseLayer::restartButtonCallback(cocos2d::Ref* pSender, ui::Widget::TouchEventType type) {
	switch (type) {
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED: {
		Director::getInstance()->resume();
		Scene* startScene = StartScene::createScene();
		Director::getInstance()->replaceScene(startScene);
	}
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	}
}
void PauseLayer::resumeButtonCallback(cocos2d::Ref* pSender, ui::Widget::TouchEventType type) {
	switch (type) {
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED: {
		
			

	}
	break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	}
}
void PauseLayer::bgmSoundButtonCallback(cocos2d::Ref* pSender, ui::Widget::TouchEventType type) {
	switch (type) {
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED: {
		if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
			bgmSoundButton->loadTextures("Images/soundon.png", "Images/soundon.png", ImagePath::DISABLE_BUTTON_PATH);
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		}
		else
		{
			bgmSoundButton->loadTextures("Images/soundon.png", "Images/soundon.png", ImagePath::DISABLE_BUTTON_PATH);
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AudioPath::BGM_NEO_ROCK.c_str(), true);
		}
	}
											break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	}
}
void PauseLayer::effectSoundButtonCallback(cocos2d::Ref* pSender, ui::Widget::TouchEventType type) {
	switch (type) {
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED: {
		/*log("effect volume %f", CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume());
		if (CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume()!=0.0f) {
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
			effectSoundButton->loadTextures("Images/soundon.png", "Images/soundon.png", ImagePath::DISABLE_BUTTON_PATH);
			effectSoundOnOff = false;
		}
		else
		{
			effectSoundButton->loadTextures("Images/soundoff.png", "Images/soundoff.png", ImagePath::DISABLE_BUTTON_PATH);
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
			effectSoundOnOff = true;
		}*/
	}
											break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	}
}
void PauseLayer::setTouchListener()
{
	// make touch listener

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(PauseLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PauseLayer::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(PauseLayer::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(PauseLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

bool PauseLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}

void PauseLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}
void PauseLayer::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void PauseLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	
}