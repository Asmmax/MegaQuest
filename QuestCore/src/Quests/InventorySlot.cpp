#include "Quests/InventorySlot.hpp"
#include "Quests/InventoryInput.hpp"

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
