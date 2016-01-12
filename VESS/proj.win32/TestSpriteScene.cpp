#include "TestSpriteScene.h"

USING_NS_CC;


Scene* TestSpriteScene::createScene()
{
	auto scene = Scene::create(); //scene생성
	auto layer = TestSpriteScene::create();//TestSpriteScene layer생성
	scene->addChild(layer);
	return scene;
}

bool TestSpriteScene::init()
{
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
		CC_CALLBACK_1(TestSpriteScene::menuCloseCallback, this));

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


	auto label = Label::create("게임 화면", "Arial", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));


	// add the label as a child to this layer
	this->addChild(label, 1);

	auto Mario = Sprite::create("Images/Mario.png");//Mario라는 sprite를 외부에서 png파일을 받아와 생성
	auto Land1 = Sprite::create("Images/Land.png"); //Mario가 점프해서 딛을 땅들을 만듬
	auto Land2 = Sprite::create("Images/Land.png"); //
	auto Hazard = Sprite::create("Biohazard.png");  //Mario가 사라질 지점을 표시한 Hazard라는 스프라이트 생성

	Mario->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)); //각 스프라이트들 위치 지정
	Land1->setPosition(Vec2(visibleSize.width / 2 + origin.x + 50, visibleSize.height / 2 + origin.y - 5));
	Land2->setPosition(Vec2(visibleSize.width / 2 + origin.x + 100, visibleSize.height / 2 + origin.y - 5));
	Hazard->setPosition(Vec2(visibleSize.width / 2 + origin.x + 150, visibleSize.height / 2 + origin.y + 20));

	Mario->setScale(0.05f);
	Land1->setScale(0.1f);
	Land2->setScale(0.1f);
	Hazard->setScale(0.13f);

	this->addChild(Mario, 0); //moving pic레이어에 Mario상속, 보이는 순서는 제일 앞인 0
	this->addChild(Land1, 2);
	this->addChild(Land2, 3);
	this->addChild(Hazard, 1);

	auto MarioJump1 = MoveTo::create(1, Point(50, 25)); //n초동안 해당좌표로 이동하는 MoveTo 
	auto MarioJump2 = MoveTo::create(1, Point(100, 0));
	auto MarioJump3 = MoveTo::create(1, Point(150, 25));
	auto MarioDie1 = RotateBy::create(2.0f, 180); //n초동안 해당z축으로 회전하는 RotateBy
	auto MarioDie2 = Blink::create(1.5f, 10);//n초동안 x번 객체를 깜박이게 함
	auto MarioDie3 = FadeOut::create(1.5f);//n초동안 투명도를 255에서 0으로 변하게 함
	//액션을 따로 만든 후 스프라이트가 가리키게 함
	Mario->runAction(MarioJump1);
	Mario->runAction(MarioJump2);
	Mario->runAction(MarioJump3);
	Mario->runAction(MarioDie1);
	Mario->runAction(MarioDie2);
	Mario->runAction(MarioDie3);
	Mario->setVisible(false); //Mario 스프라이트를 안보이게 함

	return true;
}

void TestSpriteScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}