#include "Settings.h"

USING_NS_CC;

Settings::Settings()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgm.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("effect.wav");
}

Settings::~Settings() {

}

Scene* Settings::createScene()
{
	auto scene = Scene::create();
	auto layer = Settings::create();
	scene->addChild(layer);
	layer->setScale(0.7f);
	return scene;
}

bool Settings::init()
{
	if (!Layer::init())
	{
		return false;
	}	


	MenuItemFont* bgm = MenuItemFont::create("BGM", NULL, NULL);
	MenuItemImage* bgm_on = MenuItemImage::create("CloseNormal.png", "CloseSelected", CC_CALLBACK_1(Settings::menuClicked, this));

	MenuItemFont* effect = MenuItemFont::create("Effect", NULL, NULL);
	MenuItemImage* effect_on = MenuItemImage::create("CloseNormal.png", "CloseSelected", CC_CALLBACK_1(Settings::menuClicked, this));

	bgm_on->setTag(1);
	effect_on->setTag(2);


	Menu* menu = Menu::create(bgm, bgm_on, NULL);
	menu->alignItemsHorizontally();
	Menu* menu2 = Menu::create(effect, effect_on, NULL);
	menu2->alignItemsHorizontally();

	this->addChild(menu);
	this->addChild(menu2);
	
	return true;
}

void Settings::menuClicked(Ref* pSender)
{

	log("id : %d", pSender->_ID);
	switch (pSender->_ID)
	{
	case 1:CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.wav", true);
		break;
	case 2:CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect.wav");
		break;

	}
}
