#include "DurabilityController.h"
#include "GameData.h"
#include "Sword.h"
#include "Shield.h"

void DurabilityController::reduceDurability(Item::Type itemType, int value) {
	switch (itemType) {
	case Item::Type::SWORD:{
		int durability = GameData::getInstance()->getSword()->getDurability();
		Sword* sword = GameData::getInstance()->getSword();
		sword->setDurability(durability - value);
		break;
		}
	case Item::Type::SHIELD:{
		int durability = GameData::getInstance()->getShield()->getDurability();
		GameData::getInstance()->getShield()->setDurability(durability - value);
		break;
		}
	}
}