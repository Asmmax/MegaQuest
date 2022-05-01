#include "Actions/ClearInventory.hpp"
#include "Inventory.hpp"

using namespace  QuestCore;

ClearInventory::ClearInventory(const std::shared_ptr<Inventory>& inventory):
	_inventory(inventory)
{
}

void ClearInventory::Do()
{
	auto& items = _inventory->GetItems();
	for (auto& item : items) {
		_inventory->ThrowItem(item.first, item.second);
	}
}
