#include "Settings.h"
#include "StartScene.h"
#include "EnterScene.h"
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
	if (!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)))
	{
		return false;
	}

	
	MenuItemFont* bgm = MenuItemFont::create("Back Ground Music", CC_CALLBACK_1(Settings::emptymenuClicked,this));
	bgm->setColor(ccc3(0, 0, 0));
	MenuItemImage* bgm_on = MenuItemImage::create("play.png", "play.png", CC_CALLBACK_1(Settings::bgmClicked, this));
	MenuItemImage* bgm_off = MenuItemImage::create("stop.png", "stop.png", CC_CALLBACK_1(Settings::bgmoffClicked, this));
	
	
	MenuItemFont* effect = MenuItemFont::create("Effect Sound", CC_CALLBACK_1(Settings::emptymenuClicked, this));
	effect->setColor(ccc3(0, 0, 0));
	MenuItemImage* effect_on = MenuItemImage::create("play.png", "play.png", CC_CALLBACK_1(Settings::effectClicked, this));
	MenuItemImage* effect_off = MenuItemImage::create("stop.png", "stop.png", CC_CALLBACK_1(Settings::effectoffClicked, this));
	
	

	MenuItemImage* exit = MenuItemImage::create("exit.png", "exit.png", CC_CALLBACK_1(Settings::exitClicked, this));
	


	Menu* menu = Menu::create(bgm, bgm_on, bgm_off,effect, effect_on,effect_off, exit, NULL);
	menu->alignItemsInColumns(3, 3, 1);
	
	

	this->addChild(menu);
	
	
	return true;
}

void Settings::bgmClicked(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AudioPath::BGM_NEO_ROCK.c_str(), true);
}
void Settings::bgmoffClicked(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(AudioPath::BGM_NEO_ROCK.c_str());
}
void Settings::effectClicked(Ref* pSender) {

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect.wav");
}
void Settings::effectoffClicked(Ref* pSender) {

	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}
void Settings::exitClicked(Ref* pSender){
	Scene *startScene2 = StartScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, startScene2, Color3B(0, 255, 255)));
	log("Touched");
}
void Settings::emptymenuClicked(Ref* pSender){
}