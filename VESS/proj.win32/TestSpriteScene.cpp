#include "TestSpriteScene.h"

USING_NS_CC;


Scene* TestSpriteScene::createScene()
{
	auto scene = Scene::create(); //scene����
	auto layer = TestSpriteScene::create();//TestSpriteScene layer����
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


	auto label = Label::create("���� ȭ��", "Arial", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));


	// add the label as a child to this layer
	this->addChild(label, 1);

	auto Mario = Sprite::create("Images/Mario.png");//Mario��� sprite�� �ܺο��� png������ �޾ƿ� ����
	auto Land1 = Sprite::create("Images/Land.png"); //Mario�� �����ؼ� ���� ������ ����
	auto Land2 = Sprite::create("Images/Land.png"); //
	auto Hazard = Sprite::create("Biohazard.png");  //Mario�� ����� ������ ǥ���� Hazard��� ��������Ʈ ����

	Mario->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)); //�� ��������Ʈ�� ��ġ ����
	Land1->setPosition(Vec2(visibleSize.width / 2 + origin.x + 50, visibleSize.height / 2 + origin.y - 5));
	Land2->setPosition(Vec2(visibleSize.width / 2 + origin.x + 100, visibleSize.height / 2 + origin.y - 5));
	Hazard->setPosition(Vec2(visibleSize.width / 2 + origin.x + 150, visibleSize.height / 2 + origin.y + 20));

	Mario->setScale(0.05f);
	Land1->setScale(0.1f);
	Land2->setScale(0.1f);
	Hazard->setScale(0.13f);

	this->addChild(Mario, 0); //moving pic���̾ Mario���, ���̴� ������ ���� ���� 0
	this->addChild(Land1, 2);
	this->addChild(Land2, 3);
	this->addChild(Hazard, 1);

	auto MarioJump1 = MoveTo::create(1, Point(50, 25)); //n�ʵ��� �ش���ǥ�� �̵��ϴ� MoveTo 
	auto MarioJump2 = MoveTo::create(1, Point(100, 0));
	auto MarioJump3 = MoveTo::create(1, Point(150, 25));
	auto MarioDie1 = RotateBy::create(2.0f, 180); //n�ʵ��� �ش�z������ ȸ���ϴ� RotateBy
	auto MarioDie2 = Blink::create(1.5f, 10);//n�ʵ��� x�� ��ü�� �����̰� ��
	auto MarioDie3 = FadeOut::create(1.5f);//n�ʵ��� ������ 255���� 0���� ���ϰ� ��
	//�׼��� ���� ���� �� ��������Ʈ�� ����Ű�� ��
	Mario->runAction(MarioJump1);
	Mario->runAction(MarioJump2);
	Mario->runAction(MarioJump3);
	Mario->runAction(MarioDie1);
	Mario->runAction(MarioDie2);
	Mario->runAction(MarioDie3);
	Mario->setVisible(false); //Mario ��������Ʈ�� �Ⱥ��̰� ��

	return true;
}

void TestSpriteScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}