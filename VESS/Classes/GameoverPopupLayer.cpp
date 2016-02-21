#include "GameoverPopupLayer.h"
#include "ResourcePath.h"
#include "StartScene.h"

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
	gameoverPopupFrameImage->setPosition(0, 0);
	this->addChild(gameoverPopupFrameImage);
	gameEnd = false;

	auto gameoverMessage = Label::createWithSystemFont("", "Arial", 50);
	gameoverMessage->setString("Game Over");
	gameoverMessage->setPosition(0,0);
	this->addChild(gameoverMessage);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameoverPopupLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
	
}
void GameoverPopupLayer::setGameEnd(bool isEnd) {
	this->gameEnd = isEnd;
}

bool GameoverPopupLayer::onTouchBegan(Touch* touch_, Event* event_)
{
	if (gameEnd) {
		Scene* startScene = StartScene::createScene();
		Director::getInstance()->replaceScene(startScene);
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		return true;
	}
	
}