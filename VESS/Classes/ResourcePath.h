#pragma once
#include <string>
using namespace std;
struct ImagePath {
public:
	const static string BACKGROUND_PATH;
	const static string MINI_POPUP_IMAGE;
	const static string UPGRADE_BEFORE_COMPLETE;
	const static string UPGRADE_BUTTON;
	const static string REPAIR_BUTTON;
	const static string REPAIR_BEFORE_COMPLETE;
	const static string UPGRADE_AFTER_COMPLETE;
	const static string REPAIR_AFTER_COMPLETE;
	const static string IMAGE_PATH;
	const static string DIMENSION_GATE_BUTTON_PATH;
	const static string DIMENSION_GATE_BUTTON_ACTIVE;
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
	const static string DUNGEON_DOOR_BEFORE;
	const static string DUNGEON_DOOR_AFTER;
	const static string POLE_IMAGE;
	const static string SKY_IMAGE;
	const static string TILE_BACKGROUND;
	const static string DUNGEON_DOOR_LOCK;
	const static string TUTORIAL_YES_BUTTON;
	const static string TUTORIAL_NO_BUTTON;
	const static string LEVIATHAN_IMAGE;
	const static string RESET_BUTTON;
	const static string RESET_BUTTON_ACTIVE;
	const static string PAUSE_BUTTON;
	const static string PAUSE_BUTTON_ACTIVE;
	const static string RESUME_BUTTON;
	const static string RESUME_BUTTON_ACTIVE;	
	const static string BAR_1;
	const static string BAR_2;
	const static string BAR_3;
	const static string BACKGROUND_CAVE_1_0;
	const static string BACKGROUND_CAVE_1_1;
	const static string BACKGROUND_CAVE_1_2;
	const static string BACKGROUND_CAVE_1_3;
	const static string BACKGROUND_CAVE_2_0;
	const static string BACKGROUND_CAVE_2_1;
	const static string BACKGROUND_CAVE_2_2;
	const static string BACKGROUND_CAVE_2_3;
	const static string BACKGROUND_CAVE_2_4;
};

struct ActionPath {
public:
	const static string HERO_PATH;
	const static int HERO_DEFENSE_START_FRAME;
	const static int HERO_DEFENSE_END_FRAME;
	const static int HERO_RUN_START_FRAME;
	const static int HERO_RUN_END_FRAME;
	const static string SWORD_PATH;
	const static string SHIELD_PATH;
};

struct AudioPath {
public:
	const static string AUDIO_PATH;
	const static string BGM;
	const static string SOUND;
	const static string SOUND_DIMENSION_GATE_PATH;
	const static string SOUND_JUMP_PATH;
	const static string SOUND_ATTACK_PATH;
	const static string SOUND_BLOCK;
	const static string SOUND_UPGRADE_COMPLETE;
	const static string SOUND_PUI;
	const static string SOUND_OPEN_DOOR;
	const static string BGM_NEO_ROCK;
	const static string BGM_DIALOG;
	const static string BGM_CLEAR;
	const static string BGM_ENTER;
	const static string SOUND_QUENCHING;
	const static string SOUND_HAMMER;
	const static string SOUND_SMELTING;
	const static string SOUND_SLIME_DEAD;
};

struct ElementName {
public:
	const static string UPGRADE_COMPLETE_LAYER;
	const static string DURABILITY_NAME;
	const static string LOCKED;
	const static string TOUCH_SCREEN;
	const static string START_MESSAGE;
	const static string NOT_ENOUGH_GOLD;
	const static string UPGRADE_FAILED;
	const static string UPGRADE_PERCENT;
	const static string REPAIR_PERCENT;
	const static string REPAIR_FAILED;
};

struct TutorialEventPath {
public:
	const static string DRAG_01;
	const static string EVADE_01;
	const static string EVADE_02;
};