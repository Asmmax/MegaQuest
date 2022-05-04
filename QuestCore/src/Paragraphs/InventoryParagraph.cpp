#include "Paragraphs/InventoryParagraph.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#include <algorithm>

using namespace QuestCore;

InventoryParagraph::InventoryParagraph(const FormatedString& prefix, 
	const TextString& gap, 
	const FormatedString& postfix,
	const std::shared_ptr<Inventory>& inventory):

	_prefix(prefix),
	_gap(gap),
	_postfix(postfix),
	_inventory(inventory)
{
}

TextString InventoryParagraph::GetQuest() const
{
	int countItems = 0;
	auto items = GetOrderedItems();
	for (auto& item : items)
	{
		countItems += item.second;
	}

	auto prefix = _prefix.GetContainsFor(countItems);
	auto postfix = _postfix.GetContainsFor(countItems);

	TextString contains;
	for (auto itemIt = items.begin(); itemIt != items.end(); itemIt++) {
		if (itemIt != items.begin()) {
			contains += _gap;
		}
		contains += itemIt->first->GetContains(itemIt->second);
	}

	return prefix + contains + postfix;
}

CaseContainer& InventoryParagraph::GetCaseContainer()
{
	return _cases;
}

void QuestCore::InventoryParagraph::SetItemOrder(const ItemPtr& item, int order)
{
	auto res = _itemOrders.emplace(item, order);
	if (!res.second) {
		res.first->second = order;
	}
}

std::vector<std::pair<InventoryParagraph::ItemPtr, int>> InventoryParagraph::GetOrderedItems() const
{
	std::map<ItemPtr, int> shiftItemOrders(_itemOrders);
	for (auto& shiftOrder : shiftItemOrders) {
		if (shiftOrder.second >= 0) {
			shiftOrder.second++;
		}
	}

	std::vector<std::pair<ItemPtr, int>> orderedItems;
	auto items = _inventory->GetItems();
	for (auto& item : items) {
		orderedItems.emplace_back(item);
	}

	std::sort(orderedItems.begin(), orderedItems.end(), [shiftItemOrders](const auto& left, const auto& right) {
		int leftOrder = 0;
		auto foundIt = shiftItemOrders.find(left.first);
		if (foundIt != shiftItemOrders.end()) {
			leftOrder = foundIt->second;
		}

		int rightOrder = 0;
		foundIt = shiftItemOrders.find(right.first);
		if (foundIt != shiftItemOrders.end()) {
			rightOrder = foundIt->second;
		}

		return leftOrder < rightOrder;
		});

	return orderedItems;
}
