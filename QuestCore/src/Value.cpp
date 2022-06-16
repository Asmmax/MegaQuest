#include "Value.hpp"
#include "Inventory.hpp"

using namespace QuestCore;

SimpleValue::SimpleValue(int value):
	_value(value)
{
}

int SimpleValue::Get() const
{
	return _value;
}



InventoryValue::InventoryValue(const std::weak_ptr<Item>& item, const std::weak_ptr<Inventory>& inventory):
	_item(item),
	_inventory(inventory)
{
}

int InventoryValue::Get() const
{
	auto inventoryPtr = _inventory.lock();
	if (!inventoryPtr) {
		return 0;
	}

	auto& items = inventoryPtr->GetItems();
	auto foundIt = items.find(_item.lock());
	if (foundIt == items.end()) {
		return 0;
	}
	return foundIt->second;
}
