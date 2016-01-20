#include "Monster.h"
#include "GameData.h"
using namespace std;

Monster::Monster() {
}

Monster::~Monster() {

}

bool Monster::init() {
	auto sprite = Sprite::create("Images/slime.png");
	return true;
}

bool Monster::init(const std::string& filename)
{
	CCLOG("monsterName : %s", filename.c_str());
	if (filename.empty())
	{
		CCLOG("Call Sprite::initWithFile with blank resource filename.");
		return false;
	}

	if (Unit::init())
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto sprite = Sprite::create("Images/" + filename + ".png");
		sprite->setPosition(Vec2(origin.x + visibleSize.width*0.5f, origin.y + visibleSize.height*0.5f));
		sprite->setScale(4.0f);	
		sprite->setVisible(true);
		this->addChild(sprite);
		auto enemy_move = MoveTo::create(4, ccp(origin.x, origin.y + visibleSize.height*0.5f));
		auto enemy_fade = CCFadeOut::create(2);

		auto seq = CCSequence::create(enemy_move, CCDelayTime::create(1), enemy_fade, CCCallFunc::create(this, callfunc_selector(Monster::dropItem)), NULL);
		sprite->runAction(seq);
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

Monster* Monster::create(const std::string& file_name)
{
	Monster *monster = new Monster();
	if(monster && monster->init(file_name))
	{
		monster->autorelease();

		return monster;
	}
	CC_SAFE_DELETE(monster);
	return nullptr;
}

void Monster::dropItem()
{
	log("dropItem");
	

	int ingredientType = cocos2d::RandomHelper::random_int(0, 2);
	
	Ingredient ingredient(ingredientType);

	vector<Ingredient>& ingredientList = GameData::getInstance()->getIngredientList();
	ingredientList.push_back(ingredient);
	//1. 랜덤함수 (0,1,2) *

	//2. 재료 Material material = new Material(random);  *

	//3. GameData에 등록 vector<Material> materialList& = GameData::getInstance()->getMaterials();
	//materialList.push_back(material)
}