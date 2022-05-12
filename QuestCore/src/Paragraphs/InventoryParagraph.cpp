#include "Paragraphs/InventoryParagraph.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#include "ITextView.hpp"
#include <algorithm>

using namespace QuestCore;

void InventoryParagraph::ItemOrganizer::AddItemOrder(const Item::Ptr& item, int order)
{
	auto res = _itemOrders.emplace(item, order);
	if (!res.second) {
		res.first->second = order;
	}
}

int InventoryParagraph::ItemOrganizer::GetOrder(const Item::Ptr& item) const
{
	int order = 0;
	auto foundIt = _itemOrders.find(item);
	if (foundIt != _itemOrders.end()) {
		order = foundIt->second;
	}
	return order;
}

InventoryParagraph::InventoryParagraph(const FormatedString& prefix, 
	const TextString& gap, 
	const FormatedString& postfix,
	const Inventory::Ptr& inventory):

	_prefix(prefix),
	_gap(gap),
	_postfix(postfix),
	_inventory(inventory)
{
}

void InventoryParagraph::Print(ITextView& view)
{
	int countItems = GetSumItemCount();
	view.AppendText(_prefix.GetContainsFor(countItems));

	auto items = GetOrderedItems();
	for (auto itemIt = items.begin(); itemIt != items.end(); itemIt++) {
		if (itemIt != items.begin()) {
			view.AppendText(_gap);
		}
		view.AppendText(itemIt->first->GetContains(itemIt->second));
	}

	view.AppendText(_postfix.GetContainsFor(countItems));
}

void InventoryParagraph::SetItemOrder(const Item::Ptr& item, int order)
{
	_itemOrganizer.AddItemOrder(item, order >= 0 ? order + 1 : order);
}
int InventoryParagraph::GetSumItemCount() const
{
	int countItems = 0;
	auto& items = _inventory->GetItems();
	for (auto& item : items) {
		countItems += item.second;
	}
	return countItems;
}

std::vector<std::pair<InventoryParagraph::ItemPtr, int>> InventoryParagraph::GetOrderedItems() const
{
	std::vector<std::pair<ItemPtr, int>> orderedItems;
	auto items = _inventory->GetItems();
	for (auto& item : items) {
		orderedItems.emplace_back(item);
	}

	std::sort(orderedItems.begin(), orderedItems.end(), [this](const auto& left, const auto& right) {
		return _itemOrganizer.GetOrder(left.first) < _itemOrganizer.GetOrder(right.first);
		});

	return orderedItems;
}
