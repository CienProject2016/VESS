
#include "FightLayer.h"
#include "Hero.h"
#include "StageClearLayer.h"
#include "DimensionGateController.h"
#include "StageLevelController.h"
#include "SimpleAudioEngine.h"
#include "ResourcePath.h"
#include "DurabilityController.h"
#include "GameoverPopupLayer.h"
#include "ui/CocosGUI.h"

#define gold "GOLD"
#define durabilityTag 300

bool FightLayer::init()
{
	if (!Layer::init())		return false;
	
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	initBackground();
	initDaughter();
	initOperator();
	initButton();
	initGoldLabel();
	initWeaponLabel();
	initHeart();
	initDurabilityLabel();
	initGameoverPopup("Gameover");

	this->scheduleUpdate();

	setTouchListener();

	//효과음 준비
	
	return true;
}

void FightLayer::initOperator() {
	operator_ = new BattleOperator();
	this->addChild(operator_, 1000000);
}

void FightLayer::initDaughter() {
	daughter = Hero::create();
	daughter->setParentLayer(this);
	this->addChild(daughter, 0);
}

void FightLayer::initDurabilityLabel() {
	auto durabilityNameLabel = Label::createWithSystemFont("", "Arial", 50);
	durabilityNameLabel->setPosition(Vec2(origin.x + visibleSize.width*0.510f, origin.y + visibleSize.height*0.15f));
	durabilityNameLabel->setColor(Color3B(0, 0, 0));
	durabilityNameLabel->setString(StringUtils::format("%s", ElementName::DURABILITY_NAME.c_str()));
	auto durabilityLabel = Label::createWithTTF("0", "fonts/arial.ttf", 50);
	durabilityLabel->setPosition(Vec2(origin.x + visibleSize.width*0.510f, origin.y + visibleSize.height*0.1f));
	durabilityLabel->setColor(Color3B(0, 0, 0)); //black
	durabilityLabel->setString(StringUtils::format("%d / %d", GameData::getInstance()->getSword()->getDurability(), GameData::getInstance()->getSword()->getMaxDurability()));
	this->addChild(durabilityNameLabel);
	this->addChild(durabilityLabel, 1);
	durabilityLabel->setName("durabilityLabel");
}

void FightLayer::initWeaponLabel() {

	if (GameData::getInstance()->getItemMode() == GameData::ItemMode::SWORD) {
		itemName = Label::createWithSystemFont("칼 이름", "Arial", 50);
	}
	else {
		itemName = Label::createWithSystemFont("방패 이름", "Arial", 50);
	}
	itemName->setPosition(Vec2(visibleSize.width*0.51f, visibleSize.height * 0.23f));
	itemName->setColor(Color3B(0, 0, 0));
	this->addChild(itemName);
}

void FightLayer::initGoldLabel() {
	int currentGold = GameData::getInstance()->getGold();
	currentGoldLabel = Label::createWithTTF("", "fonts/arial.ttf", 50);
	currentGoldLabel->setString(StringUtils::format("%d", currentGold));
	currentGoldLabel->setPosition(Vec2(origin.x + visibleSize.width * 0.540f, origin.y + visibleSize.height*0.935f));
	currentGoldLabel->setColor(Color3B(0, 0, 0)); //black	
	currentGoldLabel->setName("goldLabel");
	this->addChild(currentGoldLabel, 9999);

	auto goldIcon = Sprite::create(ImagePath::GOLD_ICON_PATH);
	goldIcon->setPosition(Vec2(origin.x + visibleSize.width*0.49f, origin.y + visibleSize.height * 0.935f));
	this->addChild(goldIcon);
}

void FightLayer::initButton() {

	auto dimensionGateButton = cocos2d::ui::Button::create(ImagePath::DIMENSION_GATE_BUTTON_PATH, ImagePath::DIMENSION_GATE_BUTTON_PATH, ImagePath::DISABLE_BUTTON_PATH);
	dimensionGateButton->addTouchEventListener(CC_CALLBACK_2(FightLayer::dimensionCallback, this));
	dimensionGateButton->setName("dimensionGateButton");
	dimensionGateButton->setScale(1.0f);
	dimensionGateButton->setPosition(Vec2(origin.x + visibleSize.width*0.18f, origin.y + visibleSize.height*0.17f));
	


	auto durabilityIcon = Sprite::create(ImagePath::SWORD_DURABILITY_ICON);
	durabilityIcon->setPosition(Vec2(origin.x + visibleSize.width * 0.49f, origin.y + visibleSize.height * 0.16f));
	durabilityIcon->setName("durabilityIcon");
	this->addChild(durabilityIcon);

	// add the sprite as a child to this layer
	this->addChild(dimensionGateButton, 2);
}

void FightLayer::initHeart() {
	heart = (Sprite**)malloc(sizeof(Sprite*) * daughter->getFullHp());

	for (int i=0; i<daughter->getFullHp(); i++) {
		heart[i] = Sprite::create("Images/heart.png");
		heart[i]->setTag(100000 + i);
		heart[i]->setPosition(Vec2(fightLayerSize.width*(0.13f + 0.08f * i), fightLayerSize.height*0.93f));
		heart[i]->setScale(0.55f);
		this->addChild(heart[i]);
	}
}
void FightLayer::initGameoverPopup(string)
{
	
	auto gameOverPopup = GameoverPopupLayer::create("Gameover");
	gameOverPopup->setVisible(false);
	gameOverPopup->setName("gameover");
	gameOverPopup->setPosition(Vec2(visibleSize.width *0.3f, visibleSize.height * 0.4f));
	this->addChild(gameOverPopup, ZOrder::MINI_POPUP_LAYER);

}

void FightLayer::initBackground() {
	
	auto sky = Sprite::create(ImagePath::SKY_IMAGE);
	int sky_width = sky->getTexture()->getPixelsWide();
	float sky_height = sky->getTexture()->getPixelsHigh();
	float sky_rate = fightLayerSize.width / sky_width;
	sky_height = sky_height * sky_rate;
	sky->setScale(sky_rate);
	sky->setPosition(Vec2(fightLayerSize.width / 2, fightLayerSize.height - (sky_height / 2)));
	this->addChild(sky, -200);

	backgroundSpawnScheduler = BackgroundSpawnScheduler(this);
	backgroundSpeed = new float(-100);
}

void FightLayer::redrawGold() {
	int currentGold = GameData::getInstance()->getGold();
	currentGoldLabel->setString(StringUtils::format("%d", currentGold));

}

void FightLayer::redrawTexture() {
	if (GameData::getInstance()->getItemMode() == GameData::ItemMode::SWORD) {
		itemName->setString(GameData::getInstance()->getSword()->getName());
	}
	else {
		itemName->setString(GameData::getInstance()->getShield()->getName());
	}
}
void FightLayer::showGameover()
{
	if (daughter->getHp()==0)
	{
		auto gameoverPopup = (GameoverPopupLayer*)getChildByName("gameover");
		gameoverPopup->setVisible(true);
		gameoverPopup->setGameEnd(true);
	}

}
void FightLayer::monsterSpawnUpdate(float delta) {
	int moving_distance = GameData::getInstance()->getMovingDistance();
	int stageLevel = GameData::getInstance()->getStageLevel();
	Stage stageData = GameData::getInstance()->getStageList()->at(stageLevel);
	vector<int> distance_data = stageData.getMonsterLengthInfo();
	int monsterHealth = stageData.getHealth();
	if (MonsterSpawnScheduler::isMonsterSpawnTime(moving_distance, distance_data) && this->monster == NULL) {
		monster = Monster::create(this, Monster::Slime, monsterHealth);
		this->addChild(monster, 1);
		GameData::getInstance()->setMovingDistance(moving_distance + 1);
		*backgroundSpeed = 0;

	}


	int finalDistance = GameData::getInstance()->getCurrentStageInfo().getFinalDistance();
	if (monster == NULL) {
		movingDistanceReal += delta * movingVelocity;
		if (moving_distance > finalDistance) {
			*backgroundSpeed = 0;
			chest = Chest::create();
			chest->setParentLayer(this);
			this->addChild(chest);
		}
		if (GameData::getInstance()->getCurrentStageInfo().getKey()) {
			this->stageClear();
		}
	}
	if (1 <= movingDistanceReal) {
		GameData::getInstance()->setMovingDistance(moving_distance + (int)movingDistanceReal);
		movingDistanceReal -= (int)movingDistanceReal;
	}
}

void FightLayer::update(float delta) {
	redrawDurabilityButton();
	redrawTexture();
	monsterSpawnUpdate(delta);
	backgroundSpawnScheduler.update(delta);
	redrawGold();
	redrawHeart();
	showGameover();
	redrawDimensionGate();
}

void FightLayer::redrawHeart() {
	for (int i = 0; i<daughter->getFullHp(); i++) {
		heart[i] = (Sprite*)getChildByTag(100000 + i);
		if (i > daughter->getHp()-1) {
			heart[i]->setVisible(false);
		}
		else {
			heart[i]->setVisible(true);
		}
	}
}

void FightLayer::redrawDurabilityButton() {
	auto durabilityIcon = (Sprite*)this->getChildByName("durabilityIcon");
	auto durabilityLabel = (Label*)this->getChildByName("durabilityLabel");
	switch (GameData::getInstance()->getItemMode()) {
	case GameData::ItemMode::SWORD:
		durabilityIcon->setTexture(ImagePath::SWORD_DURABILITY_ICON);
		durabilityLabel->setString(StringUtils::format("%d / %d", GameData::getInstance()->getSword()->getDurability(), GameData::getInstance()->getSword()->getMaxDurability()));
		break;
	case GameData::ItemMode::SHIELD:
		durabilityIcon->setTexture(ImagePath::SHIELD_DURABILITY_ICON);
		durabilityLabel->setString(StringUtils::format("%d / %d", GameData::getInstance()->getShield()->getDurability(), GameData::getInstance()->getShield()->getMaxDurability()));
		break;
	}
}

void FightLayer::stageClear() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	auto stageClearLayer = StageClearLayer::create();
	stageClearLayer->setContentSize(Size(100, 100));
	stageClearLayer->setPosition(Vec2(origin.x + visibleSize.width *0.325f, origin.y + visibleSize.height*0.5f));
	StageLevelController::clearStage(GameData::getInstance()->getStageLevel());
	this->addChild(stageClearLayer, 10000);
	
}

void FightLayer::dimensionCallback(cocos2d::Ref* pSender, ui::Widget::TouchEventType type)
{
	
	switch (type) {
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioPath::SOUND_DIMENSION_GATE_PATH.c_str());
		DimensionGateController::changeItemPosition(daughter);
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	}
}


void FightLayer::attackCallback(cocos2d::Ref* pSender)
{
	daughter->startAttack();
	reduceDurability();//reduce durability of weapon
}


void FightLayer::jumpCallback(cocos2d::Ref* pSender)
{
	daughter->startJump();
}

void FightLayer::sitCallback(cocos2d::Ref* pSender)
{
	daughter->startSitDown();
}

void FightLayer::reduceDurability() {
	auto durabilityLabel = (Label*)this->getChildByName("durabilityLabel");
	switch (GameData::getInstance()->getItemMode()) {
	case GameData::ItemMode::SWORD:
		DurabilityController::reduceDurability(Item::Type::SWORD, 1);
		durabilityLabel->setString(StringUtils::format("%d", GameData::getInstance()->getSword()->getDurability()));
		break;
	case GameData::ItemMode::SHIELD:
		DurabilityController::reduceDurability(Item::Type::SHIELD, 1);
		durabilityLabel->setString(StringUtils::format("%d", GameData::getInstance()->getShield()->getDurability()));
		break;
	}
	
}


void FightLayer::setTouchListener()
{
	// make touch listener

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(FightLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(FightLayer::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(FightLayer::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(FightLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

bool FightLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	if (this->getBoundingBox().containsPoint(touch->getLocation())) {
		int min_x = this->boundingBox().getMinX();
		Vec2 pos = touch->getLocation();
		pos.x -= min_x;
		operator_->startController(pos);
		return true;
	}
	return false;
}

void FightLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	if (this->getBoundingBox().containsPoint(touch->getLocation())) {
		int min_x = this->boundingBox().getMinX();
		Vec2 pos = touch->getLocation();
		pos.x -= min_x;
		operator_->setTouchPos(pos);
	}
}

void FightLayer::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void FightLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	switch (operator_->getState()) {
	case 0:		//CANCEL
		break;
	case 1:		//ATTACK
		daughter->startAttack();
		reduceDurability();//reduce durability of weapon
		break;
	case 2:		//JUMP
		daughter->startJump();
		break;
	case 3:		//AVOID
		daughter->startAvoid();
		break;
	case 4:		//SIT
		daughter->startSitDown();
		break;
	}
	operator_->endController();
}

void FightLayer::redrawDimensionGate() {
	auto dimensionGateButton = (cocos2d::ui::Button*)getChildByName("dimensionGateButton");
	switch (GameData::getInstance()->getItemMode()) {
	case GameData::ItemMode::SWORD:
		if (GameData::getInstance()->getSword()->getDurability() <= 0) {
			dimensionGateButton->loadTextures(ImagePath::DIMENSION_GATE_BUTTON_ACTIVE, ImagePath::DIMENSION_GATE_BUTTON_ACTIVE, ImagePath::DISABLE_BUTTON_PATH);
		}
		else {
			dimensionGateButton->loadTextures(ImagePath::DIMENSION_GATE_BUTTON_PATH, ImagePath::DIMENSION_GATE_BUTTON_PATH, ImagePath::DISABLE_BUTTON_PATH);
		}
		break;
	case GameData::ItemMode::SHIELD:
		if (GameData::getInstance()->getShield()->getDurability() <= 0) {
			dimensionGateButton->loadTextures(ImagePath::DIMENSION_GATE_BUTTON_ACTIVE, ImagePath::DIMENSION_GATE_BUTTON_ACTIVE, ImagePath::DISABLE_BUTTON_PATH);
		}
		else {
			dimensionGateButton->loadTextures(ImagePath::DIMENSION_GATE_BUTTON_PATH, ImagePath::DIMENSION_GATE_BUTTON_PATH, ImagePath::DISABLE_BUTTON_PATH);
		}
		break;
	}
	
	
}

Monster* FightLayer::getMonster() {
	return monster;
}
Hero* FightLayer::getDaughter() {
	return daughter;
}
Chest* FightLayer::getChest() {
	return chest;
}


void FightLayer::monsterDead() {
	this->removeChild(monster);
	monster = NULL;
	*backgroundSpeed = -200;
}

void FightLayer::chestDead() {
	this->removeChild(chest);
	chest = NULL;
	*backgroundSpeed = -100;

	this->stageClear();
	CCLOG("stageClear");

}

void FightLayer::createBackgound(EnumBackground::OBJECT object) {
	if (object == EnumBackground::MOUNTAIN) {
		BackgroundObject* mountain = BackgroundObject::create();
		mountain->setImage("Images/mountain.png", Vec2(1, 0.8f), 2.0f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::BOTTOM);
		mountain->setSpeed(backgroundSpeed, 100, 1);
		this->addChild(mountain, -105);
	}
	if (object == EnumBackground::POLE) {
		BackgroundObject* pole= BackgroundObject::create();
		pole->setImage(ImagePath::POLE_IMAGE, Vec2(1, 0.7f), 0.6f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::TOP);
		pole->setSpeed(backgroundSpeed, 100, 1);
		this->addChild(pole, -99);
	}
	if (object == EnumBackground::TILE) {
		BackgroundObject *tile = BackgroundObject::create();
		tile->setImage(ImagePath::TILE_BACKGROUND, Vec2(0.5f, 0.38f), 1.0f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::BOTTOM);
		tile->setSpeed(backgroundSpeed, 100, 1);
		this->addChild(tile, -101);
	}
}


