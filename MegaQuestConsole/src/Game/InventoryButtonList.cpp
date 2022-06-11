#include "Game/InventoryButtonList.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#include <algorithm>

using namespace Game;

InventoryButtonList::InventoryButtonList(const DialogWeakPtr& parent,
	const OutputPtr& output,
	const QuestCore::TextString& error,
	const InventoryPtr& inventory,
	const std::vector<int>& counts,
	const QuestCore::TextString& putMessage,
	const QuestCore::TextString& throwMessage) :

	ButtonListBase(parent, output, error),
	_inventory(inventory),
	_counts(counts),
	_putMessage(putMessage),
	_throwMessage(throwMessage)
{
}

void InventoryButtonList::Update()
{
	Clear();

	auto& items = GetOrderedItems();
	for (auto& item : items) {
		for (int count : _counts) {
			AddPutButton(item.first, count);

			if (item.second >= count) {
				AddThrowButton(item.first, count);
			}
		}
	}

	Print();
}

void InventoryButtonList::AddPutButton(const ItemPtr& item, int count)
{
	if (_putMessage.IsEmpty()) {
		return;
	}

	QuestCore::TextString text = _putMessage + item->GetContains(count);
	AddButton(text, [inventory = _inventory, item, count]() {
		inventory->PutItem(item, count);
		});
}

void InventoryButtonList::AddThrowButton(const ItemPtr& item, int count)
{
	if (_throwMessage.IsEmpty()) {
		return;
	}

	QuestCore::TextString text = _throwMessage + item->GetContains(count);
	AddButton(text, [inventory = _inventory, item, count]() {
		inventory->ThrowItem(item, count);
		});
}

std::vector<std::pair<QuestCore::Item::Ptr, int>> InventoryButtonList::GetOrderedItems()
{
	std::vector<std::pair<QuestCore::Item::Ptr, int>> result;

	auto& items = _inventory->GetItems();

	for (auto& item : items) {
		result.emplace_back(item.first, item.second);
	}

	std::sort(result.begin(), result.end(), [](auto& left, auto& right) -> bool {
		return left.first->GetName() < right.first->GetName();
		});

	return result;
}
