 #include "StageScene.h"
#include "GameScene.h"
#include "DialogLayer.h"
USING_NS_CC;

Scene* StageScene::createScene()
{
	auto scene = Scene::create(); //Scene생성
	auto layer = StageScene::create();//Layer생성
	auto dialogLayer = DialogLayer::create();
	scene->addChild(dialogLayer);
	scene->addChild(layer);//Layer을 Scene의 자식으로 함
	return scene;
}

bool StageScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(StageScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label


	auto label = Label::createWithTTF("Vess", "fonts/arial.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	auto touchLabel = Label::createWithSystemFont("시작하시려면 화면을 터치하세요", "Arial", 18);
	touchLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 + 10,
		origin.y + visibleSize.height - touchLabel->getContentSize().height + 10));

	// add the label as a child to this layer
	this->addChild(label, 1);
	this->addChild(touchLabel, 2);

	// add "StageScene" splash screen"
	auto sprite = Sprite::create("Images/daughter.jpg");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setScale(0.2f);


	setTouchListener();

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	
	return true;
}



void StageScene::setTouchListener()
{
	// make touch listener

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(StageScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(StageScene::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(StageScene::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(StageScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

bool StageScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}

void StageScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void StageScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void StageScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	Scene *gameScene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameScene, Color3B(0, 255, 255)));
	log("Touched");
}


void StageScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
