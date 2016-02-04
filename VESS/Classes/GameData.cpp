#include "GameData.h"

GameData* GameData::instance_ = nullptr;

GameData::GameData() : moving_distance_(0), stage_(), hero_hp_(100), gold_(150), costume_(0),durability_sword_(20),durabilty_shield_(20)
{
	dialogList_ = new vector<Dialog>();

	Dialog dialog1;
	dialog1.setName("레비아탄");
	dialog1.setPosition(Dialog::Position::RIGHT);
	dialog1.setDialogue("하하하하\n인간계 최고의 대장장이 마크여.\n나를 위해 인간의 피를 머금은 검을 만들어라.");
	dialogList_->push_back(dialog1);

	Dialog dialog2;
	dialog2.setName("대장장이");
	dialog2.setPosition(Dialog::Position::LEFT);
	dialog2.setDialogue("인간을 해칠 무기를 만들수는 없소.\n돌아가시오.");
	dialogList_->push_back(dialog2);
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