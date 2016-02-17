
#include "FightLayer.h"
#include "Hero.h"
#include "StageClearLayer.h"
#include "DimensionGateController.h"
#include "SimpleAudioEngine.h"
#include "Resources.h"

#define gold "GOLD"
#define durabilityTag 300
#define kFinalDistance 4001

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

	this->scheduleUpdate();

	setTouchListener();

	//효과음 준비
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AudioResources::SOUND_JUMP_PATH.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AudioResources::SOUND_DIMENSION_GATE_PATH.c_str());

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

void FightLayer::initWeaponLabel() {
	auto label = Label::createWithTTF("0", "fonts/arial.ttf", 50);

	int durabilitysword = GameData::getInstance()->getSword().getDurability();
	label->setPosition(Vec2(origin.x + visibleSize.width*0.550f, origin.y + visibleSize.height*0.15f));
	label->setColor(ccc3(0, 0, 0)); //black
	label->setString(StringUtils::format("%d", durabilitysword));
	this->addChild(label, 1);
	label->setTag(durabilityTag);

	if (GameData::getInstance()->getItemMode() == GameData::ItemMode::SWORD) {
		itemImage = Sprite::create("Images/sword.png");
		itemName = Label::createWithSystemFont("칼 이름", "Arial", 50);
	}
	else {
		itemImage = Sprite::create("Images/shield.png");
		itemName = Label::createWithSystemFont("방패 이름", "Arial", 50);
	}
	itemImage->setPosition(Vec2(visibleSize.width *0.3f, visibleSize.height * 3 / 5));
	this->addChild(itemImage);
	itemName->setPosition(Vec2(visibleSize.width*0.35f, visibleSize.height * 0.7f));
	itemName->setColor(ccc3(0, 0, 0));
	this->addChild(itemName);


	//dimensionMessage->setTag(dimensionTag);
}

void FightLayer::initGoldLabel() {
	int currentGold = GameData::getInstance()->getGold();
	currentGoldLabel = Label::createWithTTF("", "fonts/arial.ttf", 50);
	currentGoldLabel->setString(StringUtils::format("%d", currentGold));
	currentGoldLabel->setPosition(Vec2(origin.x + visibleSize.width * 0.540f, origin.y + visibleSize.height*0.935f));
	currentGoldLabel->setColor(ccc3(0, 0, 0)); //black	
	currentGoldLabel->setName("goldLabel");
	this->addChild(currentGoldLabel, 9999);

	auto goldIcon = Sprite::create(ImageResources::GOLD_ICON_PATH);
	goldIcon->setPosition(Vec2(origin.x + visibleSize.width*0.49f, origin.y + visibleSize.height * 0.935f));
	this->addChild(goldIcon);
}

void FightLayer::initButton() {

	auto dimensionButton = MenuItemImage::create(ImageResources::DIMENSION_GATE_BUTTON_PATH, ImageResources::DIMENSION_GATE_BUTTON_PATH, ImageResources::DISABLE_BUTTON_PATH, CC_CALLBACK_1(FightLayer::dimensionCallback, this));
	auto attackButton = MenuItemImage::create("Images/AttackButton.png", "Images/AttackButton.png", ImageResources::DISABLE_BUTTON_PATH, CC_CALLBACK_1(FightLayer::attackCallback, this));
	auto jumpButton = MenuItemImage::create(ImageResources::JUMP_BUTTON_PATH, ImageResources::JUMP_BUTTON_PATH, ImageResources::DISABLE_BUTTON_PATH, CC_CALLBACK_1(FightLayer::jumpCallback, this));

	dimensionButton->setScale(1.0f);
	attackButton->setScale(2.0f);
	jumpButton->setScale(1.5f);

	auto battleMenu = Menu::create(dimensionButton, attackButton, jumpButton, NULL);//sit_Button
	battleMenu->setPosition(Vec2(origin.x + visibleSize.width*0.325f, origin.y + visibleSize.height*0.15f));
	battleMenu->alignItemsHorizontally();
	battleMenu->alignItemsHorizontallyWithPadding(visibleSize.width*0.05f);



	// add the sprite as a child to this layer
	this->addChild(battleMenu, 2);
}

void FightLayer::initHeart() {
	heart = (Sprite**)malloc(sizeof(Sprite*) * 3);
	for (int i = 0; i < 3; i++) {
		heart[i] = Sprite::create("Images/heart.png");
		heart[i]->setTag(100000 + i);
		heart[i]->setPosition(Vec2(fightLayerSize.width*(0.13f + 0.08f * i), fightLayerSize.height*0.93f));
		heart[i]->setScale(0.55f);
		this->addChild(heart[i]);
	}
}

void FightLayer::initBackground() {
	auto ground = Sprite::create("Images/ground_basic.png");
	ground->setScale((fightLayerSize.width) / (ground->getTexture()->getPixelsWide()));
	ground->setPosition(Vec2(fightLayerSize.width / 2, fightLayerSize.height * 0.22f));
	this->addChild(ground, -100);
	
	auto sky = Sprite::create("Images/sky_basic.png");
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
		itemImage->setTexture("Images/sword.png");
		itemName->setString(GameData::getInstance()->getSword().getName());
	}
	else {
		itemImage->setTexture("Images/shield.png");
		itemName->setString(GameData::getInstance()->getShield().getName());
	}
}

void FightLayer::monsterSpawnUpdate(float delta) {
	int moving_distance = GameData::getInstance()->getMovingDistance();
	Stage stage_data = GameData::getInstance()->getStage();
	vector<int> distance_data = stage_data.getMonsterLengthInfo();
	if (MonsterSpawnScheduler::isMonsterSpawnTime(moving_distance, distance_data) && this->monster == NULL) {
		monster = Monster::create();
		monster->setParentLayer(this);
		this->addChild(monster, 1);
		GameData::getInstance()->setMovingDistance(moving_distance + 1);
		*backgroundSpeed = 0;

	}

	if (monster == NULL) {
		movingDistanceReal += delta * movingVelocity;
		if (moving_distance == kFinalDistance) {
			this->stageClear();
			CCLOG("stageClear");
		}
	}
	if (1 <= movingDistanceReal) {
		GameData::getInstance()->setMovingDistance(moving_distance + (int)movingDistanceReal);
		movingDistanceReal -= (int)movingDistanceReal;
	}
}

void FightLayer::update(float delta) {

	redrawTexture();
	monsterSpawnUpdate(delta);
	backgroundSpawnScheduler.update(delta);

}

void FightLayer::stageClear() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto stageClearLayer = StageClearLayer::create();
	stageClearLayer->setContentSize(Size(100, 100));
	stageClearLayer->setPosition(Vec2(origin.x + visibleSize.width *0.325f, origin.y + visibleSize.height*0.5f));

	this->addChild(stageClearLayer, 10000);

}

void FightLayer::dimensionCallback(cocos2d::Ref* pSender)
{
	DimensionGateController::changeItemPosition();
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioResources::SOUND_DIMENSION_GATE_PATH.c_str());
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
	auto label = (Label*)this->getChildByTag(durabilityTag);
	int durability = GameData::getInstance()->getSword().getDurability();
	GameData::getInstance()->getSword().setDurability(durability - 1);
	label->setString(StringUtils::format("%d", durability));
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

Monster* FightLayer::getMonster() {
	return monster;
}
Hero* FightLayer::getDaughter() {
	return daughter;
}

void FightLayer::monsterDead() {
	this->removeChild(monster);
	monster = NULL;
	*backgroundSpeed = -100;
}

void FightLayer::createBackgound(EnumBackground::OBJECT object) {
	if (object == EnumBackground::MOUNTAIN) {
		BackgroundObject* mountain = BackgroundObject::create();
		mountain->setImage("Images/mountain.png", Vec2(1, 0.8f), 2.0f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::BOTTOM);
		mountain->setSpeed(backgroundSpeed, 100, 1);
		this->addChild(mountain, -105);
	}
	if (object == EnumBackground::TREE) {
		BackgroundObject* tree = BackgroundObject::create();
		tree->setImage("Images/tree.png", Vec2(1, 0.6f), 0.8f, BackgroundObject::CUSTOMIZED_SIZE, BackgroundObject::TOP);
		tree->setSpeed(backgroundSpeed, 190, 2);
		this->addChild(tree, -104);
	}
}


