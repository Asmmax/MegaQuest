#include "Actions/CopyInventory.hpp"
#include "Inventory.hpp"

using namespace QuestCore;

CopyInventory::CopyInventory(const std::shared_ptr<Inventory>& source, const std::shared_ptr<Inventory>& target):
	_source(source),
	_target(target)
{
}

void CopyInventory::Do()
{
	auto& items = _source->GetItems();
	for (auto& item : items) {
		_target->PutItem(item.first, item.second);
	}
}
