#include "GameData.h"

GameData* GameData::instance_ = nullptr;

GameData::GameData() : moving_distance_(0), stage_(), hero_hp_(100), gold_(150), costume_(0),durability_sword_(20),durabilty_shield_(20)
{
	auto dialogFileData = FileUtils::getInstance()->getStringFromFile("json/dialog.json");

	dialogList_ = new vector<Dialog>();
	rapidjson::Document doc;
	doc.Parse(dialogFileData.c_str());

	auto& data = doc["opening"];

	for (auto iter = data.Begin(); iter != data.End(); iter++) {
		Dialog dialog;
		dialog.setName((*iter)["name"].GetString());
		if ((*iter)["position"] == "left") {
			dialog.setPosition(Dialog::Position::LEFT);
		} else {
			dialog.setPosition(Dialog::Position::RIGHT);
		}
		dialog.setDialogue((*iter)["lines"].GetString());
		dialogList_->push_back(dialog);
	}

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