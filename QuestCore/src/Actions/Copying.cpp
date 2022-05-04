#include "Actions/Copying.hpp"
#include "Inventory.hpp"

using namespace QuestCore;

Copying::Copying(const std::shared_ptr<Inventory>& source, const std::shared_ptr<Inventory>& target):
	_source(source),
	_target(target)
{
}

void Copying::Do()
{
	auto& items = _source->GetItems();
	for (auto& item : items) {
		_target->PutItem(item.first, item.second);
	}
}
