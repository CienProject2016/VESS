#include "GameData.h"

GameData* GameData::instance_ = nullptr;

GameData::GameData() : moving_distance_(0), stage_(), hero_hp_(100), gold_(150), costume_(0), ingredientList_(0)
{
	
}
GameData::~GameData()
{

}

GameData* GameData::getInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new GameData();
	}
	return instance_;
}