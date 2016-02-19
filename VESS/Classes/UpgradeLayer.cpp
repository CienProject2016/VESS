#include "UpgradeLayer.h"
#include "MiniPopupLayer.h"

bool UpgradeLayer::init() {
	if (!Layer::init()) {
		return false;
	}	
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	initPhase();
	initMiniPopup("골드가 부족합니다.");
	initSmithAndBackground();
	initGaugeBar();
	initButtonUi();
	initUpgradeCompleteLayer();
	initLabelInfo();
	initItemImage();
	hideBeforeUpgradeResources();
	setUpgradeButtonOpacity(currentUpgradePhase);
	setListener();
	
	this->scheduleUpdate();
	return true;
}

void UpgradeLayer::initMiniPopup(string) {
	auto miniPopup = MiniPopupLayer::create("골드가 부족합니다");
	miniPopup->setTouchEnabled(false);
	miniPopup->setVisible(false);
	miniPopup->setName("miniPopup");
	this->addChild(miniPopup, ZOrder::MINI_POPUP_LAYER);
}

void UpgradeLayer::initItemImage() {
	auto gateImage = Sprite::create(ImagePath::DIMENSION_GATE_BUTTON_PATH);
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
}

void UpgradeLayer::initLabelInfo() {
	upgradeGold = GameData::getInstance()->getNeededUpgradeGold();
	upgradeLabel = Label::createWithTTF("강화골드", "fonts/arial.ttf", 50);
	upgradeLabel->setString(StringUtils::format("%d%s", upgradeGold, "GOLD"));
	// position the label on the center of the screen
	upgradeLabel->setPosition(Vec2(Vec2(origin.x + visibleSize.width * 0.11f, origin.y + visibleSize.height*0.86f)));
	upgradeLabel->setColor(ccc3(250, 250, 250));
	this->addChild(upgradeLabel, 1);

	repairGold = GameData::getInstance()->getNeededRepairGold();
	repairLabel = Label::createWithTTF("수리골드", "fonts/arial.ttf", 50);
	repairLabel->setString(StringUtils::format("%d%s", repairGold, "GOLD"));
	repairLabel->setPosition(Vec2(origin.x + visibleSize.width * 0.33f, origin.y + visibleSize.height*0.86f));
	repairLabel->setColor(ccc3(250, 250, 250));
	this->addChild(repairLabel, 2);

}

void UpgradeLayer::initPhase() {
	currentUpgradePhase = NONE;
}

void UpgradeLayer::setListener() {

	//키보드 입력
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(UpgradeLayer::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(UpgradeLayer::keyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

}

void UpgradeLayer::initSmithAndBackground() {
	auto backgroundImage = Sprite::create("Images/background_image.png");
	auto background2Image = Sprite::create("Images/background2_image.png");
	auto smithImage = Sprite::create("Images/smith_image.png");


	// position the sprite on the center of the screen
	backgroundImage->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	backgroundImage->setScale(2.4f);

	background2Image->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	background2Image->setScale(2.0f);

	smithImage->setPosition(Vec2(origin.x + visibleSize.width * 0.2f, origin.y + visibleSize.height*0.4f));
	smithImage->setScale(2.0f);


	// add the sprite as a child to this layer
	this->addChild(backgroundImage);
	this->addChild(background2Image);
	this->addChild(smithImage);
}

void UpgradeLayer::initGaugeBar() {
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

	this->addChild(smeltingBarGauge, 2);
	this->addChild(smeltingTimeOutLine);
	this->addChild(hammeringBarGauge, 2);
	this->addChild(hammeringTimeOutLine);
	this->addChild(quenchingBarGauge, 2);
	this->addChild(quenchingTimeOutLine);
}

void UpgradeLayer::initButtonUi() {
	upgradeButton = cocos2d::ui::Button::create(ImagePath::UPGRADE_BUTTON, ImagePath::UPGRADE_BUTTON, ImagePath::DISABLE_BUTTON_PATH);
	upgradeButton->setPosition(Vec2(origin.x + visibleSize.width * 0.11f, origin.y + visibleSize.height*0.9f));
	upgradeButton->setScale(1.0f);
	upgradeButton->setTag(ZOrder::UPGRADE_IMAGE);
	upgradeButton->addTouchEventListener(CC_CALLBACK_0(UpgradeLayer::upgradeClicked, this));

	repairButton = cocos2d::ui::Button::create(ImagePath::REPAIR_BUTTON, ImagePath::REPAIR_BUTTON, ImagePath::DISABLE_BUTTON_PATH);
	repairButton->setPosition(Vec2(origin.x + visibleSize.width * 0.325f, origin.y + visibleSize.height*0.9f));
	repairButton->setScale(1.0f);	
	repairButton->setTag(ZOrder::REPAIR_IMAGE);
	repairButton->addTouchEventListener(CC_CALLBACK_0(UpgradeLayer::repairClicked, this));

	smeltingButton = cocos2d::ui::Button::create(ImagePath::SMELTING_BUTTON, ImagePath::SMELTING_BUTTON_ACTIVE, ImagePath::DISABLE_BUTTON_PATH);
	smeltingButton->setPosition(Vec2(origin.x + visibleSize.width * 0.12f, origin.y + visibleSize.height*0.4f));
	smeltingButton->setScale(1.0f);

	hammeringButton = cocos2d::ui::Button::create(ImagePath::HAMMERING_BUTTON, ImagePath::HAMMERING_BUTTON_ACTIVE, ImagePath::DISABLE_BUTTON_PATH);
	hammeringButton->setPosition(Vec2(origin.x + visibleSize.width * 0.22f, origin.y + visibleSize.height*0.2f));
	hammeringButton->setScale(1.0f);

	
	quenchingButton = cocos2d::ui::Button::create(ImagePath::QUENCHING_BUTTON, ImagePath::QUENCHING_BUTTON_ACTIVE, ImagePath::DISABLE_BUTTON_PATH);
	quenchingButton->setPosition(Vec2(origin.x + visibleSize.width * 0.32f, origin.y + visibleSize.height*0.4f));
	quenchingButton->setScale(1.0f);

	smeltingButton->addTouchEventListener(CC_CALLBACK_0(UpgradeLayer::increaseGauge, this, smeltingBarGauge));
	hammeringButton->addTouchEventListener(CC_CALLBACK_0(UpgradeLayer::increaseGauge, this, hammeringBarGauge));
	quenchingButton->addTouchEventListener(CC_CALLBACK_0(UpgradeLayer::increaseGauge, this, quenchingBarGauge));
	
	smeltingButton->setTag(ZOrder::SMELTING_IMAGE);
	hammeringButton->setTag(ZOrder::HAMMERING_IMAGE);
	quenchingButton->setTag(ZOrder::QUENCHING_IMAGE);

	completeUpgradeButton = cocos2d::ui::Button::create(ImagePath::UPGRADE_BEFORE_COMPLETE, ImagePath::UPGRADE_BEFORE_COMPLETE, ImagePath::DISABLE_BUTTON_PATH);
	completeUpgradeButton->setPosition(Vec2(visibleSize.width * 0.22f, visibleSize.height * 7 / 10));
	completeUpgradeButton->setTag(ZOrder::COMPLETE_UPGRADE_BUTTON);
	completeUpgradeButton->addTouchEventListener(CC_CALLBACK_0(UpgradeLayer::completeClicked, this));
	completeUpgradeButton->setTouchEnabled(false);

	completeRepairButton = cocos2d::ui::Button::create(ImagePath::REPAIR_BEFORE_COMPLETE, ImagePath::REPAIR_BEFORE_COMPLETE, ImagePath::DISABLE_BUTTON_PATH);
	completeRepairButton->setPosition(Vec2(visibleSize.width * 0.22f, visibleSize.height * 7 / 10));
	completeRepairButton->setTag(ZOrder::COMPLETE_REPAIR_BUTTON);
	completeRepairButton->addTouchEventListener(CC_CALLBACK_0(UpgradeLayer::completeClicked, this));
	completeRepairButton->setTouchEnabled(false);

	this->addChild(smeltingButton);
	this->addChild(hammeringButton);
	this->addChild(quenchingButton);
	this->addChild(completeUpgradeButton);
	this->addChild(completeRepairButton);
	this->addChild(upgradeButton);
	this->addChild(repairButton);
}


void UpgradeLayer::initUpgradeCompleteLayer(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto upgradeCompleteLayer = UpgradeCompleteLayer::create();
	upgradeCompleteLayer->setContentSize(Size(800, 600));
	upgradeCompleteLayer->setAnchorPoint(Vec2(0, 0));
	upgradeCompleteLayer->setPosition(Vec2(visibleSize.width * 0.01f, visibleSize.height * 0.17f));
	upgradeCompleteLayer->setVisible(false);
	upgradeCompleteLayer->setTouchEnabled(false);
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
	else if (currentUpgradePhase == UpgradePhase::REPAIR) {
	}else{

	}
	

	if (GameData::getInstance()->getItemMode() == GameData::ItemMode::SWORD) {
		itemImage->setTexture("Images/shield.png");
		itemName->setString(GameData::getInstance()->getShield()->getName());
	}
	else {
		itemImage->setTexture("Images/sword.png");
		itemName->setString(StringUtils::format("%s", GameData::getInstance()->getSword()->getName().c_str()));
	}
}

void UpgradeLayer::checkGaugeLock() {
	if (GaugeLockChecker::isGaugeLocked(smeltingBarGauge->getPercentage(), 70))
	{
		lockBeforeHammering = true;
		hammeringButton->setOpacity(255);
		hammeringButton->setTouchEnabled(true);
	}
	if (GaugeLockChecker::isGaugeLocked(hammeringBarGauge->getPercentage(), 70))
	{
		lockBeforeQuenching = true;
		quenchingButton->setOpacity(255);
		quenchingButton->setTouchEnabled(true);
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
			completeUpgradeButton->setTouchEnabled(true);
		}
		break;
	case UpgradePhase::REPAIR:
		if (hammeringBarGauge->getPercentage() >= 70)
		{
			showCompleteButton();
			completeRepairButton->setTouchEnabled(true);
		}
		break;
	case UpgradePhase::NONE:
		//Nothing To Do
		break;
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
		completeRepairButton->setVisible(false);
		upgradeButton->setVisible(true);
		upgradeButton->setTouchEnabled(true);
		repairButton->setVisible(true);
		repairButton->setTouchEnabled(true);
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
		upgradeButton->setVisible(false);
		upgradeButton->setTouchEnabled(false);
		repairButton->setVisible(false);
		repairButton->setTouchEnabled(false);
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
		completeRepairButton->setVisible(true);
		upgradeButton->setVisible(false);
		upgradeButton->setTouchEnabled(false);
		repairButton->setVisible(false);
		repairButton->setTouchEnabled(false);
		upgradeLabel->setVisible(false);
		repairLabel->setVisible(false);
		hammeringBarGauge->setVisible(true);
		hammeringTimeOutLine->setVisible(true);
	}
}


void UpgradeLayer::upgradeClicked()
{
	
	log("Upgrade Phase");
	if (GameData::getInstance()->getItemMode() == GameData::ItemMode::SWORD) {
		//소드는 딸이 사용중이므로 방패강화
		if (UpgradeController::payUpgradeCosts(upgradeGold, Item::SHIELD) == true) {
			currentUpgradePhase = UpgradePhase::UPGRADE;
			showUiButton(currentUpgradePhase);
			setUpgradeButtonOpacity(currentUpgradePhase);
		}
		else {
			auto miniPopup = (Layer*)getChildByName("miniPopup");
			miniPopup->setVisible(true);
		}
	}
	else {
		if (UpgradeController::payUpgradeCosts(upgradeGold, Item::SWORD) == true) {
			currentUpgradePhase = UpgradePhase::UPGRADE;
			showUiButton(currentUpgradePhase);
			setUpgradeButtonOpacity(currentUpgradePhase);
		}
		else {
			auto miniPopup = (Layer*)getChildByName("miniPopup");
			miniPopup->setVisible(true);
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
		smeltingButton->setTouchEnabled(true);
		break;
	case UpgradePhase::REPAIR:
		hammeringButton->setOpacity(255);
		hammeringButton->setTouchEnabled(true);
		break;
	case UpgradePhase::NONE:
		hammeringButton->setOpacity(0);
		hammeringButton->setTouchEnabled(false);
		quenchingButton->setOpacity(0);
		quenchingButton->setTouchEnabled(false);
		smeltingButton->setOpacity(0);
		smeltingButton->setTouchEnabled(false);
		break;
	}
}

void UpgradeLayer::repairClicked()
{
	upgradeButton->setVisible(false);
	repairButton->setVisible(false);
	
	hammeringBarGauge->setVisible(true);
	hammeringTimeOutLine->setVisible(true);
	
	lockBeforeHammering = true; // 수리의 경우 망치만 사용하므로 제한을 걸어둘 필요가 없다.

	if (GameData::getInstance()->getItemMode() == GameData::ItemMode::SWORD) {
		//소드는 딸이 사용중이므로 방패강화
		if (UpgradeController::payRepairCosts(repairGold, Item::SHIELD) == true) {
			currentUpgradePhase = UpgradePhase::REPAIR;
			showUiButton(currentUpgradePhase);
			setUpgradeButtonOpacity(currentUpgradePhase);
		}
		else {
			auto miniPopup = (Layer*)getChildByName("miniPopup");
			miniPopup->setVisible(true);
		}
	}
	else {
		if (UpgradeController::payRepairCosts(repairGold, Item::SWORD) == true) {
			currentUpgradePhase = UpgradePhase::REPAIR;
			showUiButton(currentUpgradePhase);
			setUpgradeButtonOpacity(currentUpgradePhase);
		}
		else {
			auto miniPopup = (Layer*)getChildByName("miniPopup");
			miniPopup->setVisible(true);
		}
	}


}


void UpgradeLayer::showCompleteButton()
{
	if (currentUpgradePhase == UPGRADE) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		completeUpgradeButton->loadTextures(ImagePath::UPGRADE_AFTER_COMPLETE, ImagePath::UPGRADE_AFTER_COMPLETE, ImagePath::DISABLE_BUTTON_PATH);
	}
	else if (currentUpgradePhase == REPAIR) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		completeRepairButton->loadTextures(ImagePath::REPAIR_AFTER_COMPLETE, ImagePath::REPAIR_AFTER_COMPLETE, ImagePath::DISABLE_BUTTON_PATH);
	}
}


void UpgradeLayer::hideBeforeUpgradeResources()
{
	completeUpgradeButton->loadTextures(ImagePath::UPGRADE_BEFORE_COMPLETE, ImagePath::UPGRADE_BEFORE_COMPLETE, ImagePath::DISABLE_BUTTON_PATH);
	completeUpgradeButton->setVisible(false);
	completeUpgradeButton->setTouchEnabled(false);
	completeRepairButton->loadTextures(ImagePath::REPAIR_BEFORE_COMPLETE, ImagePath::REPAIR_BEFORE_COMPLETE, ImagePath::DISABLE_BUTTON_PATH);
	completeRepairButton->setVisible(false);
	completeRepairButton->setTouchEnabled(false);
	smeltingBarGauge->setVisible(false);
	smeltingTimeOutLine->setVisible(false);
	hammeringBarGauge->setVisible(false);
	hammeringTimeOutLine->setVisible(false);
	quenchingBarGauge->setVisible(false);
	quenchingTimeOutLine->setVisible(false);
}


void UpgradeLayer::completeClicked() {
	lockBeforeHammering = false; // 초기화
	lockBeforeQuenching = false;
	log("complete!!");
	switch (currentUpgradePhase) {
	case UpgradePhase::UPGRADE:
		UpgradeController::upgradeItem(GameData::getInstance()->getUpgradeItemMode());
		break;
	case UpgradePhase::REPAIR:
		UpgradeController::repairItem(GameData::getInstance()->getUpgradeItemMode());
		log("%d", getSword.getDurability());
		break;
	}

	currentUpgradePhase = UpgradePhase::NONE;
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