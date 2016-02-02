
#include "Monster.h"
#include "GameData.h"
#include "FightLayer.h"
using namespace std;

Monster::Monster() {
}

Monster::~Monster() {

}

bool Monster::init()
{
	if (Unit::init())
	{
		hp_ = 100;
		window_size = fightLayerSize;
		origin = fightLayerOrigin;
		Node* node = CSLoader::createNode("animation/Tauren.csb");
		this->addChild(node); //get animation data 
		timeline::ActionTimeline* action = CSLoader::createTimeline("animation/Tauren.csb");
		node->setPosition(0, 0);
		node->runAction(action);
		action->gotoFrameAndPlay(26, 32, true);
		this->setPosition(Vec2(window_size.width * 0.7f, window_size.height * 0.4f));
		return true;
	}	
	return false;
}

bool Monster::isDead()
{
	if (this->hp_ <= 0)
	{
		return true;
	}
	return false;
}

Monster* Monster::create()
{
	Monster *monster = new Monster();
	if(monster && monster->init())
	{
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return nullptr;
}

void Monster::dropItem()
{
/*
	log("dropItem");
	

	int ingredientType = cocos2d::RandomHelper::random_int(0, 2);
	
	Ingredient ingredient(ingredientType);

	vector<Ingredient>& ingredientList = GameData::getInstance()->getIngredientList();
	ingredientList.push_back(ingredient);
	//1. 랜덤함수 (0,1,2) *

	//2. 재료 Material material = new Material(random);  *

	//3. GameData에 등록 vector<Material> materialList& = GameData::getInstance()->getMaterials();
	//materialList.push_back(material)
*/
}

void Monster::setParentLayer(FightLayer* layer) {
	field = layer;
}

void Monster::damage(int dam) {
	hp_ -= dam;
	log("monster HP is : %d", hp_);
	if (hp_ <= 0) {
		field->monsterDead();
	}
}
