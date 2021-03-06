#include "EnterScene.h"
#include "SimpleAudioEngine.h"
#include "StageLevelController.h"

USING_NS_CC;

Scene* EnterScene::createScene()
{
	auto scene = Scene::create(); //Scene생성
	auto layer = EnterScene::create();//Layer생성
	scene->addChild(layer);//Layer을 Scene의 자식으로 함
	return scene;
}

bool EnterScene::init()
{
	
	if (!Layer::init())
	{
		return false;
	}
	StageLevelController::initiateProperty();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AudioPath::BGM_ENTER.c_str());
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto leviathanImage = Sprite::create(ImagePath::LEVIATHAN_IMAGE);
	leviathanImage->setPosition(Vec2(visibleSize.width * 0.15f, visibleSize.height * 0.44f));
	this->addChild(leviathanImage);

	auto restartButton = ui::Button::create(ImagePath::RESET_BUTTON, ImagePath::RESET_BUTTON_ACTIVE, ImagePath::DISABLE_BUTTON_PATH);
	restartButton->setPosition(Vec2(visibleSize.width * 0.4f, visibleSize.height * 0.15f));
	restartButton->addTouchEventListener(CC_CALLBACK_2(EnterScene::restartCallback, this));
	this->addChild(restartButton);

	for (int i = 0; i < 10; i++){
		auto enterStageButton = ui::Button::create(ImagePath::DUNGEON_DOOR_BEFORE, ImagePath::DUNGEON_DOOR_AFTER, ImagePath::DISABLE_BUTTON_PATH);
		auto stageLabel = Label::createWithSystemFont(StringUtils::format("Stage %d", i + 1), "Arial", 40);
		stageLabel->setAnchorPoint(Vec2(0, 0));
		stageLabel->setTag(STAGE_LABEL + i);
		enterStageButton->setTag(STAGE_DOOR + i);
		enterStageButton->addTouchEventListener(CC_CALLBACK_2(EnterScene::enterCallback, this, i));
		if (GameData::getInstance()->getTopStage() < i) {
			enterStageButton->loadTextures(ImagePath::DUNGEON_DOOR_LOCK, ImagePath::DUNGEON_DOOR_LOCK, ImagePath::DISABLE_BUTTON_PATH);
			stageLabel->setString(StringUtils::format("%s %d\n%s", "Stage", i + 1, ElementName::LOCKED.c_str()));
			enterStageButton->setTouchEnabled(false);
		}
		else {
			enterStageButton->setTouchEnabled(true);
		}
		
		if (i < 5){
			enterStageButton->setPosition(Vec2(visibleSize.width * 0.45f+ (i - 1)*0.7*visibleSize.width/5 , visibleSize.height*0.38f));
			stageLabel->setPosition(Vec2(visibleSize.width * 0.42f+ (i - 1)*0.7*visibleSize.width/5 , visibleSize.height*0.26f));
		}
		else {
			enterStageButton->setPosition(Vec2(visibleSize.width * 0.45f + (i - 6)*0.7*(visibleSize.width / 5), visibleSize.height *0.73f));
			stageLabel->setPosition(Vec2(visibleSize.width * 0.42f + (i - 6)*0.7*(visibleSize.width / 5), visibleSize.height *0.63f));
		}
		
		this->addChild(enterStageButton);
		this->addChild(stageLabel);
	}
	auto backButton = ui::Button::create("Images/back.png","Images/back.png","Images/back.png");
	backButton->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height* 0.9f));
	backButton->addTouchEventListener(CC_CALLBACK_2(EnterScene::backCallback, this));
	backButton->setScale(0.2f);
	this->addChild(backButton,0);
	this->scheduleUpdate();
	
	return true;
}

void EnterScene::restartCallback(Ref* sender, ui::Widget::TouchEventType type) {
	switch (type) {
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED:
		GameData::getInstance()->resetInfo();
		break;		
	case ui::Widget::TouchEventType::CANCELED:
		break;
	}
}

void EnterScene::backCallback(Ref* sender, ui::Widget::TouchEventType type) {
	switch (type) {
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED:
		{
		Scene* startScene = StartScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, startScene, Color3B(255, 255, 255)));
		}
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	}
}

void EnterScene::update(float delta) {
	for (int i = 0; i < 10; i++) {
		auto enterStageButton = (ui::Button*)this->getChildByTag(STAGE_DOOR + i);
		auto stageLabel = (Label*)this->getChildByTag(STAGE_LABEL + i);
		if (GameData::getInstance()->getTopStage() < i) {
			enterStageButton->loadTextures(ImagePath::DUNGEON_DOOR_LOCK, ImagePath::DUNGEON_DOOR_LOCK, ImagePath::DISABLE_BUTTON_PATH);
			stageLabel->setString(StringUtils::format("%s %d\n%s", "Stage", i + 1, ElementName::LOCKED.c_str()));
			enterStageButton->setTouchEnabled(false);
		}
		else {
			enterStageButton->loadTextures(ImagePath::DUNGEON_DOOR_BEFORE, ImagePath::DUNGEON_DOOR_AFTER, ImagePath::DISABLE_BUTTON_PATH);
			enterStageButton->setTouchEnabled(true);
		}
	}
}

void EnterScene::enterCallback(Ref* sender, ui::Widget::TouchEventType type, int stageLevel) {
	switch (type) {
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED:
		log("Enter");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioPath::SOUND_OPEN_DOOR.c_str());
		StageLevelController::setStageLevel(stageLevel);
		if (stageLevel == 0) {
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			Scene *dialogScene = DialogScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, dialogScene, Color3B(255, 255, 255)));
			GameData::getInstance()->setIsTutorial(true);

			
		}
		else {
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			Scene *gameScene = GameScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameScene, Color3B(255, 255, 255)));
			
		}
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	}
	
}



