#include "Factories/JsonQuest.hpp"
#include "IParagraph.hpp"
#include "Item.hpp"
#include "Inventory.hpp"

using namespace QuestCore;

JsonQuest::JsonQuest(const std::map<std::string, IParagraph::Ptr>& roots,
	const std::vector<std::string>& hotKeys,
	const std::map<std::string, Item::Ptr>& items,
	const std::map<std::string, Inventory::Ptr>& inventories) :
	_roots(roots),
	_hotKeys(hotKeys),
	_items(items),
	_inventories(inventories)
{
}

const std::map<std::string, IParagraph::Ptr>& JsonQuest::GetRoots() const
{
	return _roots;
}

const std::vector<std::string>& JsonQuest::GetHotKeys() const
{
	return _hotKeys;
}

const std::map<std::string, Item::Ptr>& JsonQuest::GetItems() const
{
	return _items;
}

const std::map<std::string, Inventory::Ptr>& JsonQuest::GetInventories() const
{
	return _inventories;
}
