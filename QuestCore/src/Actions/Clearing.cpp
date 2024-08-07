#include "Actions/Clearing.hpp"
#include "Inventory.hpp"

using namespace  QuestCore;

Clearing::Clearing(Inventory* inventory):
	_inventory(inventory)
{
}

void Clearing::Do()
{
	auto& items = _inventory->GetItems();
	for (auto& item : items) {
		_inventory->ThrowItem(item.first, item.second);
	}
}
