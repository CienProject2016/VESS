#include "GameoverPopupLayer.h"
#include "ResourcePath.h"

GameoverPopupLayer::GameoverPopupLayer() {

}
GameoverPopupLayer::~GameoverPopupLayer() {

}

GameoverPopupLayer* GameoverPopupLayer::create(string createMessage) {

	GameoverPopupLayer* gameoverPopupLayer = new GameoverPopupLayer();
	if (gameoverPopupLayer && gameoverPopupLayer->init(createMessage))
	{
		gameoverPopupLayer->autorelease();
		return gameoverPopupLayer;
	}
	CC_SAFE_DELETE(gameoverPopupLayer);
	return nullptr;
}
bool GameoverPopupLayer::init(string createMessage) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto gameoverPopupFrameImage = Sprite::create(ImagePath::MINI_POPUP_IMAGE);
	gameoverPopupFrameImage->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	this->addChild(gameoverPopupFrameImage);

	auto gameoverMessage = Label::createWithSystemFont("", "Arial", 50);
	gameoverMessage->setString("Game Over.");
	gameoverMessage->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	this->addChild(gameoverMessage);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameoverPopupLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

bool GameoverPopupLayer::onTouchBegan(Touch* touch_, Event* event_)
{
	this->setVisible(false);
	return true;
}