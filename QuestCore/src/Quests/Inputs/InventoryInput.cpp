#include "Quests/Inputs/InventoryInput.hpp"
#include "Quests/Slots/InventorySlot.hpp"

using namespace QuestCore;

InventoryInput::InventoryInput(Inventory* inventory, 
	InventorySlot* slot,
	Quest* quest) :

	Base(inventory, slot, quest)
{
}
