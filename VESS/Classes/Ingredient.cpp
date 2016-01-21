#pragma once
#include "cocos2d.h"
#include "Ingredient.h"
#include<stdlib.h>
#include<iostream>

Ingredient::Ingredient()
{
	this->type_ = IRON_ORE;
}

Ingredient::~Ingredient()
{

}

Ingredient::Ingredient(int typeNumber)
{
	switch (typeNumber)
	{
	case 0:
		type_ = IRON_ORE;
	case 1:
		type_ = GOLD_INGOT;
	case 2:
		type_ = SILVER_INGOT;
	}
}

