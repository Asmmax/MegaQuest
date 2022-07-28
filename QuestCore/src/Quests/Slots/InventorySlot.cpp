#include "Quests/Slots/InventorySlot.hpp"
#include "Quests/Slots/InventoryInput.hpp"

using namespace QuestCore;

void InventorySlot::Update()
{
	_input = nullptr;
}

void InventorySlot::SetInput(InventoryInput* input)
{
	_input = input;
}

InventorySlot::InventoryPtr InventorySlot::GetInventory() const
{
	if (!_input) {
		return nullptr;
	}
	return _input->GetInventory();
}
