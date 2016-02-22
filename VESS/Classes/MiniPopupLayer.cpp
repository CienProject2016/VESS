#include "MiniPopupLayer.h"
#include "ResourcePath.h"

MiniPopupLayer::MiniPopupLayer() {

}
MiniPopupLayer::~MiniPopupLayer() {

}

MiniPopupLayer* MiniPopupLayer::create(string createMessage) {

	MiniPopupLayer* miniPopupLayer = new MiniPopupLayer();
	if (miniPopupLayer && miniPopupLayer->init(createMessage))
	{
		miniPopupLayer->autorelease();
		return miniPopupLayer;
	}
	CC_SAFE_DELETE(miniPopupLayer);
	return nullptr;
}

void MiniPopupLayer::setMessage(string message) {
	auto popupMessageLabel = (Label*)getChildByName("popupMessageLabel");
	popupMessageLabel->setString(StringUtils::format("%s", message.c_str()));
}

bool MiniPopupLayer::init(string createMessage) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto miniPopupFrameImage = Sprite::create(ImagePath::MINI_POPUP_IMAGE);
	miniPopupFrameImage->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	this->addChild(miniPopupFrameImage);

	auto popupMessage = Label::createWithSystemFont("", "Arial", 50);
	popupMessage->setString(createMessage);
	popupMessage->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	popupMessage->setName("popupMessageLabel");
	this->addChild(popupMessage);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MiniPopupLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

bool MiniPopupLayer::onTouchBegan(Touch* touch_, Event* event_)
{
	this->setVisible(false);
	return true;
}