#include "DialogLayer.h"
#include "GameData.h"


bool DialogLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	dialogData = GameData::getInstance()->getDialogList();


	auto textLayer = CCLayerColor::create(ccc4(0, 0, 0, 255 * 0.7), winSize.width, winSize.height * 0.25);
	textLayer->setPosition(Vec2(0,0));
	this->addChild(textLayer);

	auto dialogue = CCString::createWithFormat(dialogData->at(0).getDialogue().c_str(), 30);
	
	CCLabelTTF* textLabel = CCLabelTTF::create(dialogue->getCString(), "Arial", 30);
	textLabel->setAnchorPoint(ccp(0, 0));
	textLabel->setColor(Color3B::WHITE);
	textLabel->setPosition(ccp(30, textLayer->getContentSize().height - textLabel->getContentSize().height - 30));
	textLayer->addChild(textLabel);
	return true;
}