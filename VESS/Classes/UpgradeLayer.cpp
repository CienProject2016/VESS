#include "UpgradeLayer.h"

bool UpgradeLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	currentUpgradePhase = NONE;
	completeButtonPhase = CANNOT_CLICK;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(UpgradeLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	makeUpgradeCompleteLayer();

	//키보드 입력
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(UpgradeLayer::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(UpgradeLayer::keyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto backgroundImage = Sprite::create("Images/background_image.png");
	auto background2Image = Sprite::create("Images/background2_image.png");
	auto smithImage = Sprite::create("Images/smith_image.png");
	smeltingButton = cocos2d::ui::Button::create(ImageResources::SMELTING_BUTTON, ImageResources::SMELTING_BUTTON_ACTIVE, ImageResources::DISABLE_BUTTON_PATH);
	hammeringButton = cocos2d::ui::Button::create(ImageResources::HAMMERING_BUTTON, ImageResources::HAMMERING_BUTTON_ACTIVE, ImageResources::DISABLE_BUTTON_PATH);
	quenchingButton = cocos2d::ui::Button::create(ImageResources::QUENCHING_BUTTON, ImageResources::QUENCHING_BUTTON_ACTIVE, ImageResources::DISABLE_BUTTON_PATH);
	
	

	upgradeImage = Sprite::create("Images/upgrade_button.png");
	repairImage = Sprite::create("Images/repair_button.png");
	// position the sprite on the center of the screen
	backgroundImage->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	backgroundImage->setScale(2.4f);

	background2Image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	background2Image->setScale(2.0f);

	smithImage->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	smithImage->setScale(2.0f);

	smeltingButton->setPosition(Vec2(origin.x + visibleSize.width * 0.12f, origin.y + visibleSize.height*0.4f));
	smeltingButton->setScale(1.0f);

	hammeringButton->setPosition(Vec2(origin.x + visibleSize.width * 0.22f, origin.y + visibleSize.height*0.2f));
	hammeringButton->setScale(1.0f);

	quenchingButton->setPosition(Vec2(origin.x + visibleSize.width * 0.32f, origin.y + visibleSize.height*0.4f));
	quenchingButton->setScale(1.0f);

	upgradeImage->setPosition(Vec2(origin.x + visibleSize.width * 0.11f, origin.y + visibleSize.height*0.9f));
	upgradeImage->setScale(1.0f);

	repairImage->setPosition(Vec2(origin.x + visibleSize.width * 0.325f, origin.y + visibleSize.height*0.9f));
	repairImage->setScale(1.0f);

	smeltingButton->setTag(ZOrder::SMELTING_IMAGE);
	hammeringButton->setTag(ZOrder::HAMMERING_IMAGE);
	quenchingButton->setTag(ZOrder::QUENCHING_IMAGE);
	upgradeImage->setTag(ZOrder::UPGRADE_IMAGE);
	repairImage->setTag(ZOrder::REPAIR_IMAGE);

	//smelting bar create
	Sprite *smeltingTimeBar = Sprite::create("timebar.png");
	smeltingBarGauge = ProgressTimer::create(smeltingTimeBar);
	smeltingBarGauge->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.95));
	smeltingBarGauge->setPercentage(0);
	smeltingBarGauge->setMidpoint(ccp(0, 0.5));
	smeltingBarGauge->setBarChangeRate(ccp(1, 0));
	smeltingBarGauge->setType(kCCProgressTimerTypeBar);
	smeltingTimeOutLine = Sprite::create("timeoutline.png");
	smeltingTimeOutLine->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.95));
	smeltingGaugeDownSpeed = 5;

	//hammering bar create
	Sprite *hammeringTimeBar = Sprite::create("timebar.png");
	hammeringBarGauge = ProgressTimer::create(hammeringTimeBar);
	hammeringBarGauge->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.9));
	hammeringBarGauge->setPercentage(0);
	hammeringBarGauge->setMidpoint(ccp(0, 0.5));
	hammeringBarGauge->setBarChangeRate(ccp(1, 0));
	hammeringBarGauge->setType(kCCProgressTimerTypeBar);
	hammeringTimeOutLine = Sprite::create("timeoutline.png");
	hammeringTimeOutLine->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.9));
	hammeringGaugeDownSpeed = 10;

	//quenching bar create
	Sprite *quenchingTimeBar = Sprite::create("timebar.png");
	quenchingBarGauge = ProgressTimer::create(quenchingTimeBar);
	quenchingBarGauge->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.85));
	quenchingBarGauge->setPercentage(0);
	quenchingBarGauge->setMidpoint(ccp(0, 0.5));
	quenchingBarGauge->setBarChangeRate(ccp(1, 0));
	quenchingBarGauge->setType(kCCProgressTimerTypeBar);
	quenchingTimeOutLine = Sprite::create("timeoutline.png");
	quenchingTimeOutLine->setPosition(Vec2(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height*0.85));
	quenchingGaugeDownSpeed = 15;


	// add the sprite as a child to this layer
	this->addChild(backgroundImage);
	this->addChild(background2Image);
	this->addChild(smithImage);

	upgradeGold = GameData::getInstance()->getNeededUpgradeGold();
	upgradeLabel = Label::createWithTTF("강화골드", "fonts/arial.ttf", 50);
	upgradeLabel->setString(StringUtils::format("%d%s", upgradeGold, "GOLD"));
	// position the label on the center of the screen
	upgradeLabel->setPosition(Vec2(Vec2(origin.x + visibleSize.width * 0.11f, origin.y + visibleSize.height*0.86f)));
	upgradeLabel->setColor(ccc3(250, 250, 250));
	this->addChild(upgradeLabel, 1);
	
	
	auto gateImage = Sprite::create(ImageResources::DIMENSION_GATE_BUTTON_PATH);
	gateImage->setPosition(Vec2(visibleSize.width * 0.35f, visibleSize.height * 0.6f));
	this->addChild(gateImage, ZOrder::DIMENSION_GATE_IMAGE);

	//업그레이드 레이어는 ItemMode의 반대 이미지를 보여줌
	if (GameData::getInstance()->getItemMode() == GameData::ItemMode::SWORD) {
		itemImage = Sprite::create("Images/shield.png");
		itemName = Label::createWithSystemFont("방패 이름", "Arial", 50);
	}
	else {
		itemImage = Sprite::create("Images/sword.png");
		itemName = Label::createWithSystemFont("칼 이름", "Arial", 50);
	}
	itemImage->setPosition(Vec2(visibleSize.width * 0.35f, visibleSize.height * 0.6f));
	itemImage->setName("itemImage");
	itemName->setPosition(Vec2(origin.x + visibleSize.width*0.35f, origin.x + visibleSize.height * 0.7f));
	itemName->setVisible(true);

	this->addChild(itemImage, ZOrder::ITEM_IMAGE);
	this->addChild(itemName, ZOrder::ITEM_NAME);

	repairGold = GameData::getInstance()->getNeededRepairGold();
	repairLabel = Label::createWithTTF("수리골드", "fonts/arial.ttf", 50);
	repairLabel->setString(StringUtils::format("%d%s", repairGold, "GOLD"));
	repairLabel->setPosition(Vec2(origin.x + visibleSize.width * 0.33f, origin.y + visibleSize.height*0.86f));
	repairLabel->setColor(ccc3(250, 250, 250));
	this->addChild(repairLabel, 2);

	completeUpgradeButton = Sprite::create("Images/upgrade_before_complete.png");
	completeUpgradeButton->setPosition(Vec2(visibleSize.width * 0.22f, visibleSize.height * 7 / 10));
	completeUpgradeButton->setTag(ZOrder::COMPLETE_UPGRADE_BUTTON);

	smeltingButton->addTouchEventListener(CC_CALLBACK_0(UpgradeLayer::increaseGauge, this, smeltingBarGauge));
	hammeringButton->addTouchEventListener(CC_CALLBACK_0(UpgradeLayer::increaseGauge, this, hammeringBarGauge));
	quenchingButton->addTouchEventListener(CC_CALLBACK_0(UpgradeLayer::increaseGauge, this, quenchingBarGauge));

	this->addChild(completeUpgradeButton);
	this->addChild(smeltingButton);
	this->addChild(hammeringButton);
	this->addChild(quenchingButton);
	this->addChild(upgradeImage);
	this->addChild(repairImage);
	this->addChild(smeltingBarGauge, 2);
	this->addChild(smeltingTimeOutLine);
	this->addChild(hammeringBarGauge, 2);
	this->addChild(hammeringTimeOutLine);
	this->addChild(quenchingBarGauge, 2);
	this->addChild(quenchingTimeOutLine);

	this->scheduleUpdate();

	hideBeforeUpgradeResources();
	//망치,담금질 비활성화 색상으로 변경
	setUpgradeButtonOpacity(currentUpgradePhase);

	return true;
}

void UpgradeLayer::makeUpgradeCompleteLayer(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto upgradeCompleteLayer = UpgradeCompleteLayer::create();
	upgradeCompleteLayer->setContentSize(Size(800, 600));
	upgradeCompleteLayer->setAnchorPoint(Vec2(0, 0));
	upgradeCompleteLayer->setPosition(Vec2(visibleSize.width * 0.01f, visibleSize.height * 0.17f));
	upgradeCompleteLayer->setVisible(false);
	upgradeCompleteLayer->setName("upgradeCompleteLayer");
	this->addChild(upgradeCompleteLayer, ZOrder::UPGRADE_COMPLETE_LAYER);
}

void UpgradeLayer::update(float delta) {
	showUiButton(currentUpgradePhase);	

	smeltingBarGauge->setPercentage(smeltingBarGauge->getPercentage() - delta * smeltingGaugeDownSpeed);
	hammeringBarGauge->setPercentage(hammeringBarGauge->getPercentage() - delta * hammeringGaugeDownSpeed);
	quenchingBarGauge->setPercentage(quenchingBarGauge->getPercentage() - delta * quenchingGaugeDownSpeed);

	checkComplete();
	if (currentUpgradePhase == UpgradePhase::UPGRADE) {
		checkGaugeLock();
	}
	

	if (GameData::getInstance()->getItemMode() == GameData::ItemMode::SWORD) {
		itemImage->setTexture("Images/shield.png");
		itemName->setString(GameData::getInstance()->getShield().getName());
	}
	else {
		itemImage->setTexture("Images/sword.png");
		itemName->setString(StringUtils::format("%s", GameData::getInstance()->getSword().getName().c_str()));
	}
}

void UpgradeLayer::checkGaugeLock() {
	if (GaugeLockChecker::isGaugeLocked(smeltingBarGauge->getPercentage(), 70))
	{
		lockBeforeHammering = true;
		hammeringButton->setOpacity(255);
	}
	if (GaugeLockChecker::isGaugeLocked(hammeringBarGauge->getPercentage(), 70))
	{
		lockBeforeQuenching = true;
		quenchingButton->setOpacity(255);
	}
	if (GaugeLockChecker::isGaugeLocked(hammeringBarGauge->getPercentage(), 70) && !isUpgrade)
	{
		showCompleteButton();
	}
}

void UpgradeLayer::checkComplete() {
	switch (currentUpgradePhase) {
	case UpgradePhase::UPGRADE:
		if (quenchingBarGauge->getPercentage() >= 70)
		{
			showCompleteButton();
			completeButtonPhase = CompleteButtonPhase::CAN_CLICK;
		}
		break;
	case UpgradePhase::REPAIR:
		if (hammeringBarGauge->getPercentage() >= 70)
		{
			showCompleteButton();
			completeButtonPhase = CompleteButtonPhase::CAN_CLICK;
		}
		break;
	case UpgradePhase::NONE:
		//Nothing To Do
		break;
	}
}

void UpgradeLayer::checkLock() {
	// 나중에 강화마다 값을 다르게 할거면, 매개변수에 값을 받아오는 식으로 수정하시면 됩니다.
	if (smeltingBarGauge->getPercentage() >= 70) {
		lockBeforeHammering = true;
		hammeringButton->setOpacity(255);
	}

	if (hammeringBarGauge->getPercentage() >= 70) {
		lockBeforeQuenching = true;
		quenchingButton->setOpacity(255);
	}
}

void UpgradeLayer::increaseGauge(CCProgressTimer* gauge)
{
	float currentPercent = gauge->getPercentage();
	gauge->setPercentage(currentPercent + (float)8);
}

void UpgradeLayer::showUiButton(UpgradePhase upgradePhase) {
	if (upgradePhase == UpgradePhase::NONE) {
		completeUpgradeButton->setVisible(false);
		upgradeImage->setVisible(true);
		repairImage->setVisible(true);
		upgradeLabel->setVisible(true);
		repairLabel->setVisible(true);
		smeltingBarGauge->setVisible(false);
		smeltingTimeOutLine->setVisible(false);
		hammeringBarGauge->setVisible(false);
		hammeringTimeOutLine->setVisible(false);
		quenchingBarGauge->setVisible(false);
		quenchingTimeOutLine->setVisible(false);
	}
	else if(upgradePhase == UpgradePhase::UPGRADE){
		completeUpgradeButton->setVisible(true);
		upgradeImage->setVisible(false);
		repairImage->setVisible(false);
		upgradeLabel->setVisible(false);
		repairLabel->setVisible(false);
		smeltingBarGauge->setVisible(true);
		smeltingTimeOutLine->setVisible(true);
		hammeringBarGauge->setVisible(true);
		hammeringTimeOutLine->setVisible(true);
		quenchingBarGauge->setVisible(true);
		quenchingTimeOutLine->setVisible(true);
	}
	else if (upgradePhase == UpgradePhase::REPAIR) {
		completeUpgradeButton->setVisible(true);
		upgradeImage->setVisible(false);
		repairImage->setVisible(false);
		upgradeLabel->setVisible(false);
		repairLabel->setVisible(false);
		hammeringBarGauge->setVisible(true);
		hammeringTimeOutLine->setVisible(true);

	}
}


void UpgradeLayer::upgradeClicked()
{
	currentUpgradePhase = UpgradePhase::UPGRADE;
	log("Upgrade Phase");
	if (GameData::getInstance()->getItemMode() == GameData::ItemMode::SWORD) {
		//소드는 딸이 사용중이므로 방패강화
		if (UpgradeController::payUpgradeCosts(upgradeGold, Item::SHIELD) == true) {
			showUiButton(currentUpgradePhase);
			setUpgradeButtonOpacity(currentUpgradePhase);
		}
		else {
			//돈이 없어 강화를 할 수 없는 경우
		}
	}
	else {
		if (UpgradeController::payUpgradeCosts(upgradeGold, Item::SWORD) == true) {
			showUiButton(currentUpgradePhase);
			setUpgradeButtonOpacity(currentUpgradePhase);
		}
		else {
			//돈이 없어 강화를 할 수 없는 경우
		}
	}
}

void UpgradeLayer::setUpgradeButtonOpacity(UpgradePhase currentUpgradePhase) 
{
	switch (currentUpgradePhase) {
	case UpgradePhase::UPGRADE:
		hammeringButton->setOpacity(120);
		quenchingButton->setOpacity(120);
		smeltingButton->setOpacity(255);
		break;
	case UpgradePhase::REPAIR:
		hammeringButton->setOpacity(255);
		break;
	case UpgradePhase::NONE:
		hammeringButton->setOpacity(0);
		quenchingButton->setOpacity(0);
		smeltingButton->setOpacity(0);
		break;
	}
}

void UpgradeLayer::repairClicked()
{
	hammeringButton->setOpacity(255);
	upgradeImage->setVisible(false);
	repairImage->setVisible(false);
	hammeringBarGauge->setVisible(true);
	hammeringTimeOutLine->setVisible(true);

	currentUpgradePhase = UpgradePhase::REPAIR; // 강화인지 수리인지 체크하는 변수
	log("Repair Phase");
	lockBeforeHammering = true; // 수리의 경우 망치만 사용하므로 제한을 걸어둘 필요가 없다.
	getSword = GameData::getInstance()->getSword();
	log("current durability is %d", getSword.getDurability());
	showUiButton(currentUpgradePhase);
}


void UpgradeLayer::showCompleteButton()
{
	if (currentUpgradePhase == REPAIR) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		completeUpgradeButton->setTexture("Images/upgrade_after_complete.png"); //TODO 바꿔야됨
	}
	else if (currentUpgradePhase == UPGRADE) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		completeUpgradeButton->setTexture("Images/upgrade_after_complete.png");
	}
}


void UpgradeLayer::hideBeforeUpgradeResources()
{
	completeUpgradeButton->setVisible(false);
	smeltingBarGauge->setVisible(false);
	smeltingTimeOutLine->setVisible(false);
	hammeringBarGauge->setVisible(false);
	hammeringTimeOutLine->setVisible(false);
	quenchingBarGauge->setVisible(false);
	quenchingTimeOutLine->setVisible(false);
}

bool UpgradeLayer::onTouchBegan(Touch* touch_, Event* event_)
{
	Point p = touch_->getLocation();

	// 강화, 수리 이미지
	auto upgradeButton = (Sprite*) this->getChildByTag(ZOrder::UPGRADE_IMAGE);
	Rect upgradeTouchRect = upgradeButton->getBoundingBox();
	if (upgradeTouchRect.containsPoint(p)) {
		upgradeClicked();
	}

	auto repairButton = (Sprite*) this->getChildByTag(ZOrder::REPAIR_IMAGE);
	Rect repairTouchRect = repairButton->getBoundingBox();
	if (repairTouchRect.containsPoint(p)) {
		repairClicked();
	}

	if (completeButtonPhase == CAN_CLICK) {
		auto completeUpgradeButton = (Sprite*) this->getChildByTag(ZOrder::COMPLETE_UPGRADE_BUTTON);
		Rect completeUpgradeTouchRect = completeUpgradeButton->getBoundingBox();
		if (completeUpgradeTouchRect.containsPoint(p)) {
			completeClicked();
		}
	}
	return true;
}

void UpgradeLayer::completeClicked() {
	lockBeforeHammering = false; // 초기화
	lockBeforeQuenching = false;
	log("complete!!");
	switch (currentUpgradePhase) {
	case UpgradePhase::UPGRADE:
		UpgradeController::upgradeItem();
		break;
	case UpgradePhase::REPAIR:
		getSword.setDurability(getSword.getMaxDurability());
		log("%d", getSword.getDurability());
		break;
	}

	currentUpgradePhase = UpgradePhase::NONE;
	completeButtonPhase = CompleteButtonPhase::CANNOT_CLICK;
	clearGauge();
	showUiButton(currentUpgradePhase);
	setUpgradeButtonOpacity(currentUpgradePhase);
	hideBeforeUpgradeResources();
	

	auto upgradeCompleteLayer = (Layer*)getChildByName("upgradeCompleteLayer");
	upgradeCompleteLayer->setVisible(true);
}

void UpgradeLayer::clearGauge()
{
	smeltingBarGauge->setPercentage(0);
	hammeringBarGauge->setPercentage(0);
	quenchingBarGauge->setPercentage(0);
}

void UpgradeLayer::setTouchListener()
{
	// make touch listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(UpgradeLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(UpgradeLayer::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(UpgradeLayer::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(UpgradeLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}


void UpgradeLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void UpgradeLayer::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void UpgradeLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void UpgradeLayer::keyPressed(cocos2d::EventKeyboard::KeyCode key_code_, cocos2d::Event *event_)
{
	if (key_code_ == EventKeyboard::KeyCode::KEY_A)
	{
		increaseGauge(smeltingBarGauge);
	}

	if (key_code_ == EventKeyboard::KeyCode::KEY_S && lockBeforeHammering)
	{
		increaseGauge(hammeringBarGauge);
	}

	if (key_code_ == EventKeyboard::KeyCode::KEY_D && lockBeforeQuenching)
	{
		increaseGauge(quenchingBarGauge);
	}
}
void UpgradeLayer::keyReleased(cocos2d::EventKeyboard::KeyCode key_code_, cocos2d::Event *event_)
{

}