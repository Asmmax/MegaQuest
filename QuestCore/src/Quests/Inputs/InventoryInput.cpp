#include "Quests/Inputs/InventoryInput.hpp"
#include "Quests/Slots/InventorySlot.hpp"

using namespace QuestCore;

InventoryInput::InventoryInput(const InventoryPtr& inventory, 
	const InventorySlotPtr& slot,
	const QuestHeaderPtr& quest) :

	Base(inventory, slot, quest)
{
}
