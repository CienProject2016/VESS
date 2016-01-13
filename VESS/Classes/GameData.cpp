#include "GameData.h"

GameData* GameData::instance_ = nullptr;

GameData::GameData() : stage_(1)
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