#include "Settings.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Settings::Settings(){
	
}

Settings::~Settings() {

}

Scene* Settings::createScene()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgm.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("effect.wav");
	auto scene = Scene::create();
	auto layer = Settings::create();
	scene->addChild(layer);
	
	return scene;
}

bool Settings::init()
{
	if (!CCLayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto bgm = MenuItemFont::create("배경음악 ON/OFF", CC_CALLBACK_1(Settings::emptymenuClicked,this));
	bgm->setScale(1.5f);
	bgm->setColor(Color3B(255, 0, 0));  //ccc3가 deprecate인 관계로 글씨를 이미지파일로 바꾸던지, 다른 api이용이 필요함.
	auto bgmOn = MenuItemImage::create("Images/play.png", "Images/play.png", CC_CALLBACK_1(Settings::bgmClicked, this));
	bgmOn->setScale(1.5f);
	auto bgmOff = MenuItemImage::create("Images/stop.png", "Images/stop.png", CC_CALLBACK_1(Settings::bgmoffClicked, this));
	bgmOff->setScale(1.5f);

	auto bgmSound = MenuItemFont::create("배경음악 조절", CC_CALLBACK_1(Settings::emptymenuClicked, this));
	bgmSound->setScale(1.5f);
	bgmSound->setColor(Color3B(255, 0, 0));
	auto bgmSoundUp = MenuItemImage::create("Images/volume_up.png", "Images/volume_up.png", CC_CALLBACK_1(Settings::bgmSoundUpClicked, this));
	bgmSoundUp->setScale(0.4f);
	auto bgmSoundDown = MenuItemImage::create("Images/volume_down.png", "Images/volume_down.png", CC_CALLBACK_1(Settings::bgmSoundDownClicked, this));
	bgmSoundDown->setScale(0.4f);

	auto effect = MenuItemFont::create("이펙트 ON/OFF", CC_CALLBACK_1(Settings::emptymenuClicked, this));
	effect->setScale(1.5f);
	effect->setColor(Color3B(255, 0, 0));
	auto effectOn = MenuItemImage::create("Images/play.png", "Images/play.png", CC_CALLBACK_1(Settings::effectClicked, this));
	effectOn->setScale(1.5f);
	auto effectOff = MenuItemImage::create("Images/stop.png", "Images/stop.png", CC_CALLBACK_1(Settings::effectoffClicked, this));
	effectOff->setScale(1.5f);

	auto effectSound = MenuItemFont::create("이펙트 조절", CC_CALLBACK_1(Settings::emptymenuClicked, this));
	effectSound->setScale(1.5f);
	effectSound->setColor(Color3B(255, 0, 0));
	auto effectSoundUp = MenuItemImage::create("Images/volume_up.png", "Images/volume_up.png", CC_CALLBACK_1(Settings::effectSoundUpClicked, this));
	effectSoundUp->setScale(0.4f);
	auto effectSoundDown = MenuItemImage::create("Images/volume_down.png", "Images/volume_down.png", CC_CALLBACK_1(Settings::effectSoundDownClicked, this));
	effectSoundDown->setScale(0.4f);

	auto exit = MenuItemImage::create("Images/exit.png", "Images/exit.png", CC_CALLBACK_1(Settings::exitClicked, this));

	auto nameMenu = Menu::create(bgm, bgmSound, effect, effectSound, NULL);
	nameMenu->setPosition(Vec2(origin.x + visibleSize.width*0.15f, origin.y + visibleSize.height*0.5f));
	nameMenu->alignItemsVertically();
	nameMenu->alignItemsVerticallyWithPadding(visibleSize.width*0.05f);

	auto onMenu = Menu::create(bgmOn, bgmSoundUp, effectOn, effectSoundUp, NULL);
	onMenu->setPosition(Vec2(origin.x + visibleSize.width*0.55f, origin.y + visibleSize.height*0.5f));
	onMenu->alignItemsVertically();
	onMenu->alignItemsVerticallyWithPadding(visibleSize.width*0.05f);

	auto offMenu = Menu::create(bgmOff, bgmSoundDown, effectOff, effectSoundDown, NULL);
	offMenu->setPosition(Vec2(origin.x + visibleSize.width*0.75f, origin.y + visibleSize.height*0.5f));
	offMenu->alignItemsVertically();
	offMenu->alignItemsVerticallyWithPadding(visibleSize.width*0.05f);

	//auto bgmOnMenu = Menu::create(bgm, bgmOn, bgmOff, bgmSoundUp, bgmSoundDown, effect, effectOn,effectOff, effectSoundUp, effectSoundDown, exit, NULL);
	
	
	this->addChild(nameMenu,1);
	this->addChild(onMenu, 2);
	this->addChild(offMenu, 3);
	
	return true;
}

void Settings::bgmClicked(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.wav", true);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.7f);
}

void Settings::bgmoffClicked(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("bgm.wav");
}

void Settings::bgmSoundUpClicked(Ref* pSender) 
{
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume();
}

void Settings::bgmSoundDownClicked(Ref* pSender) 
{
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume();
}

void Settings::effectClicked(Ref* pSender) {

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.7f);
}

void Settings::effectoffClicked(Ref* pSender) {

	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}

void Settings::effectSoundUpClicked(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(float volume);
}

void Settings::effectSoundDownClicked(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(float volume);
}

void Settings::exitClicked(Ref* pSender){
	Scene *startScene2 = StartScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, startScene2, Color3B(0, 255, 255)));
	log("Touched");
}

void Settings::emptymenuClicked(Ref* pSender){
}