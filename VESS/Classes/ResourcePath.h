#pragma once
#include <string>
using namespace std;
struct ImagePath {
public:
	const static string MINI_POPUP_IMAGE;
	const static string UPGRADE_BEFORE_COMPLETE;
	const static string REPAIR_BEFORE_COMPLETE;
	const static string UPGRADE_AFTER_COMPLETE;
	const static string REPAIR_AFTER_COMPLETE;
	const static string IMAGE_PATH;
	const static string DIMENSION_GATE_BUTTON_PATH;
	const static string JUMP_BUTTON_PATH;
	const static string DISABLE_BUTTON_PATH;
	const static string GOLD_ICON_PATH;
	const static string UPGRADE_COMPLETE_POPUP_FRAME_PATH;
	const static string REPAIR_COMPLETE_POPUP_FRAME_PATH;
	const static string CONFIRM_BUTTON_PATH;
	const static string SMELTING_BUTTON;
	const static string SMELTING_BUTTON_ACTIVE;
	const static string QUENCHING_BUTTON;
	const static string QUENCHING_BUTTON_ACTIVE;
	const static string HAMMERING_BUTTON;
	const static string HAMMERING_BUTTON_ACTIVE;
	const static string SWORD_DURABILITY_ICON;
	const static string SHIELD_DURABILITY_ICON;
};

struct AudioPath {
public:
	const static string AUDIO_PATH;
	const static string BGM;
	const static string SOUND;
	const static string SOUND_DIMENSION_GATE_PATH;
	const static string SOUND_JUMP_PATH;
	const static string SOUND_ATTACK_PATH;
};

struct ElementPath {
public:
	const static string UPGRADE_COMPLETE_LAYER;
};