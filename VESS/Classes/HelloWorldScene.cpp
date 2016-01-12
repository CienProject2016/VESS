#include "HelloWorldScene.h"

USING_NS_CC;
#define Num 1000
#define Print 2000
Scene* HelloWorldScene::createScene()
{
	auto scene = Scene::create();

	auto layer = HelloWorldScene::create();
	scene->addChild(layer);
	return scene;
}


bool HelloWorldScene::init()
{

	if (!Layer::init())
	{
		return false;
	}
	srand((int)time(NULL));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//auto	listener = EventListenerTouchOneByOne::create();
	///listener->onTouchBegan = CC_CALLBACK_2(HelloWorldScene::onTouchBegan, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorldScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	//auto label = Label::createWithTTF("HelloWorldScene", "fonts/Marker Felt.ttf", 14);

  //  label->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//	origin.y + visibleSize.height - label->getContentSize().height));

//	this->addChild(label, 1);
	
	for (int i = 0; i < 4; i++){
		number[i] = i;//rand() % 4;

	}

	
	
	
	auto show = Label::createWithTTF("a", "fonts/Marker Felt.ttf", 15);
	show->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - show->getContentSize().height));
	show->enableOutline(Color4B::WHITE, 1);
	

	show->setTag(Print);
	this->addChild(show);
	sprite();
	showNum(number);
	setLife();

	return true;
}

bool HelloWorldScene::onTouchBegan(Touch *touch, Event * event){
	Vec2 location = touch->getLocation();
	for (int i = 0; i < 4; i++){
		auto card = (Sprite*)this->getChildByTag(Num + i);
		Rect rectCard = card->getBoundingBox();
		if (rectCard.containsPoint(location))
		{

			if (i == number[count]){
				count++;
				DelayTime *action_1 = DelayTime::create(2.0f);
				FadeOut *action_2 = FadeOut::create(2.0f);
				Action* action_3 = card->runAction(action_2);
				Sequence* actioin_4 = Sequence::create(action_1, action_2, action_3, NULL);
			}
			else{
				life--;
			}
		}

	}
	score();
	setLife();


	return true;
}
void HelloWorldScene::sprite()
{
	for (int i = 0; i < 4; i++){


		auto card = Sprite::create(StringUtils::format("/game/card_%d.png", i + 1));
		card->setPosition(Vec2(80 + (i * 100), 160));
		card->setTag(Num + i);

		this->addChild(card);
	}
}
void HelloWorldScene::showNum(int number[]){
	
	auto show = (Label*)this->getChildByTag(Print);
	show->setString(StringUtils::format("%d-%d-%d-%d", number[0]+1, number[1]+1, number[2]+1, number[3]+1 ));
}
void HelloWorldScene::score()
{
	auto show = (Label*)this->getChildByTag(Print);
	show->setString(StringUtils::format("%d", count*25));
}
void HelloWorldScene::setLife(){
	if (life == 0){
		auto life= (Label*)this->getChildByTag(Print);
		life->setString(StringUtils::format("NO MORE CHANCE"));
	
	}
}
void HelloWorldScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
