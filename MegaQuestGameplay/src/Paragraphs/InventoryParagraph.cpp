#include "Paragraphs/InventoryParagraph.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

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
	auto& items = _inventory->GetItems();
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