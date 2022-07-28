#include "Quests/InventoryInput.hpp"
#include "Quests/InventorySlot.hpp"

using namespace QuestCore;

InventoryInput::InventoryInput(const InventoryPtr& inventory, const InventorySlotPtr& slot) :
	_inventory(inventory),
	_slot(slot)
{
}

void InventoryInput::Update()
{
	_slot->SetInput(this);
}

InventoryInput::InventoryPtr InventoryInput::GetInventory() const
{
	return _inventory;
}
