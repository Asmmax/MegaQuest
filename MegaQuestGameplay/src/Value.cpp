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



InventoryValue::InventoryValue(const std::shared_ptr<Item>& item, const std::shared_ptr<Inventory>& inventory):
	_item(item),
	_inventory(inventory)
{
}

int InventoryValue::Get() const
{
	if (!_inventory) {
		return 0;
	}

	auto items = _inventory->GetItems();
	auto foundIt = items.find(_item);
	if (foundIt == items.end()) {
		return 0;
	}
	return foundIt->second;
}
