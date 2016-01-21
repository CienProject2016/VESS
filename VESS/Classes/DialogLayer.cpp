#include "DialogLayer.h"

bool DialogLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	auto textLayer = CCLayerColor::create(ccc4(0, 0, 0, 255 * 0.7), winSize.width, winSize.height * 0.25);
	textLayer->setPosition(Vec2(0,0));
	this->addChild(textLayer);

	auto string = CCString::createWithFormat("VESS(Very Expensive Sword & Shield)", 30);
	

	CCLabelTTF* textLabel = CCLabelTTF::create(string->getCString(), "", 30);
	textLabel->setAnchorPoint(ccp(0, 0));
	textLabel->setColor(Color3B::WHITE);
	textLabel->setPosition(ccp(30, textLayer->getContentSize().height - textLabel->getContentSize().height - 30));
	textLayer->addChild(textLabel);
	return true;
}