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
	int i;
	if (!Layer::init())
	{
		return false;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(AudioPath::SOUND_OPEN_DOOR.c_str());
	

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	

	auto myScene = Scene::create();

	for (i = 0; i < 10; i++){
		auto enterStage = ui::Button::create(ImagePath::DUNGEON_DOOR_BEFORE, ImagePath::DUNGEON_DOOR_AFTER, ImagePath::DISABLE_BUTTON_PATH	);
		auto stageLabel = Label::createWithSystemFont(StringUtils::format("Stage %d", i+1), "Arial", 40);
		if (i < 5){
			enterStage->setPosition(Vec2(visibleSize.width * 0.3f+ (i - 1)*0.7*visibleSize.width/5 , visibleSize.height*0.35f));
			stageLabel->setPosition(Vec2(visibleSize.width * 0.3f+ (i - 1)*0.7*visibleSize.width/5 , visibleSize.height*0.35f));
		}
		else {
			enterStage->setPosition(Vec2(visibleSize.width * 0.3f + (i - 6)*0.7*(visibleSize.width / 5), visibleSize.height *0.7f));
			stageLabel->setPosition(Vec2(visibleSize.width * 0.3f + (i - 6)*0.7*(visibleSize.width / 5), visibleSize.height *0.7f));
		}
		enterStage->setTag(stageDoor + i);
		enterStage->addTouchEventListener(CC_CALLBACK_0(EnterScene::enterCallback, this, i));
		this->addChild(enterStage);
		this->addChild(stageLabel);
	}

	auto backButton = Sprite::create("Images/back.png");
	backButton->setPosition(Vec2(visibleSize.width / 5, (visibleSize.height / 5) * 4 + origin.y));
	backButton->setScale(0.3f);
	this->addChild(backButton,0);
	this->scheduleUpdate();
	
	return true;
}

void EnterScene::enterCallback(int stageLevel) {
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AudioPath::SOUND_OPEN_DOOR.c_str());
	StageLevelController::setStageLevel(stageLevel);
	if (stageLevel == 0) {
		Scene *dialogScene = DialogScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, dialogScene, Color3B(255, 255, 255)));
		log("Touched");
	}
	else {
		Scene *gameScene = GameScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameScene, Color3B(255, 255, 255)));
	}
}



