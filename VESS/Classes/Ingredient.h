#pragma once
#include "cocos2d.h"

class Ingredient
{
private:
	enum IngredientType{  IRON_ORE,
						GOLD_INGOT,
						SILVER_INGOT};
	CC_SYNTHESIZE(IngredientType, type_, Type);
public:
	Ingredient();
	Ingredient(int);
	~Ingredient();
};
