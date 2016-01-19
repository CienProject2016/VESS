#include "Settings.h"
#include "StartScene.h"
USING_NS_CC;

Settings::Settings()
{
	
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
	if (!Layer::init())
	{
		return false;
	}	


	MenuItemFont* bgm = MenuItemFont::create("Back Ground Music", NULL, NULL);
	MenuItemImage* bgm_on = MenuItemImage::create("CloseNormal.png", "CloseSelected", CC_CALLBACK_1(Settings::bgmClicked, this));

	MenuItemFont* effect = MenuItemFont::create("Effect Sound", NULL, NULL);
	MenuItemImage* effect_on = MenuItemImage::create("CloseNormal.png", "CloseSelected", CC_CALLBACK_1(Settings::effectClicked, this));

	MenuItemFont* exit = MenuItemFont::create("Exit", CC_CALLBACK_1(Settings::exitClicked, this));
	bgm_on->setTag(1);
	effect_on->setTag(2);


	Menu* menu = Menu::create(bgm, bgm_on, effect, effect_on, exit, NULL);
	menu->alignItemsVertically();
	

	this->addChild(menu);
	
	
	return true;
}

void Settings::bgmClicked(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.wav", true);
}
void Settings::effectClicked(Ref* pSender) {

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect.wav");
}
void Settings::exitClicked(Ref* pSender)
{
	Scene *startScene2 = StartScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, startScene2, Color3B(0, 255, 255)));
	log("Touched");
}