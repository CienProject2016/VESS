#include "AnimationScene.h"
#include "cocostudio\CocoStudio.h"



using namespace cocos2d;

USING_NS_CC;

Scene* AnimationScene::createScene()
{
	auto scene = Scene::create();

	auto layer = AnimationScene::create();
	scene->addChild(layer);
	return scene;
}


bool AnimationScene::init()
{

	if (!Layer::init())
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	
	Node* node = CSLoader::createNode("animation/Hero.csb"); 
	this->addChild(node); //get animation data 
	cocostudio::timeline::ActionTimeline* action = CSLoader::createTimeline("animation/Hero.csb");
	node->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y ));
	
	node->runAction(action); 
	action->gotoFrameAndPlay(0,32, true);



	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(AnimationScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	//auto label = Label::createWithTTF("AnimationScene", "fonts/Marker Felt.ttf", 14);

  //  label->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//	origin.y + visibleSize.height - label->getContentSize().height));

//	this->addChild(label, 1);
	
	
	return true;
}

void AnimationScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
