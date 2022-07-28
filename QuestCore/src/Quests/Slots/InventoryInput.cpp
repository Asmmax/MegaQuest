#include "Quests/Slots/InventoryInput.hpp"
#include "Quests/Slots/InventorySlot.hpp"

using namespace QuestCore;

InventoryInput::InventoryInput(const InventoryPtr& inventory, 
	const InventorySlotPtr& slot,
	const QuestHeaderPtr& quest) :

	QuestInitable(quest),
	_inventory(inventory),
	_slot(slot)
{
}

void InventoryInput::Init()
{
	_slot->SetInput(this);
}

InventoryInput::InventoryPtr InventoryInput::GetInventory() const
{
	return _inventory;
}
