#include "Game/ButtonLists/InventoryButtonList.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#include "Quests/Slots/InventorySlot.hpp"
#include <algorithm>

using namespace Game;

InventoryButtonList::InventoryButtonList(const QuestCore::TextString& error,
	const InventoryFactoryPtr& inventoryFactory,
	const std::vector<int>& counts,
	const QuestCore::TextString& putMessage,
	const QuestCore::TextString& throwMessage) :

	ButtonListBase(error),
	_inventoryFactory(inventoryFactory),
	_counts(counts),
	_putMessage(putMessage),
	_throwMessage(throwMessage)
{
}

void InventoryButtonList::UpdateImpl()
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
}

void InventoryButtonList::AddPutButton(const ItemPtr& item, int count)
{
	if (_putMessage.IsEmpty()) {
		return;
	}

	Button button;
	button.name = _putMessage + item->GetContains(count);
	button.callback = [inventoryFactory = _inventoryFactory, item, count]() {
		if (auto inventory = inventoryFactory->GetInventory()) {
			inventory->PutItem(item, count);
		}
	};

	AddButton(button);
}

void InventoryButtonList::AddThrowButton(const ItemPtr& item, int count)
{
	if (_throwMessage.IsEmpty()) {
		return;
	}

	Button button;
	button.name = _throwMessage + item->GetContains(count);
	button.callback = [inventoryFactory = _inventoryFactory, item, count]() {
		if (auto inventory = inventoryFactory->GetInventory()) {
			inventory->ThrowItem(item, count);
		}
	};

	AddButton(button);
}

std::vector<std::pair<QuestCore::Item::Ptr, int>> InventoryButtonList::GetOrderedItems()
{
	std::vector<std::pair<QuestCore::Item::Ptr, int>> result;

	auto inventory = _inventoryFactory->GetInventory();
	if (!inventory) {
		return result;
	}

	auto& items = inventory->GetItems();

	for (auto& item : items) {
		result.emplace_back(item.first, item.second);
	}

	std::sort(result.begin(), result.end(), [](auto& left, auto& right) -> bool {
		return left.first->GetName() < right.first->GetName();
		});

	return result;
}
