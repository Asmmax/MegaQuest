#include "Factories/JsonQuest.hpp"
#include "IParagraph.hpp"
#include "Item.hpp"
#include "Inventory.hpp"

using namespace QuestCore;

JsonQuest::JsonQuest(const std::map<std::string, Node>& roots,
	const std::vector<std::string>& hotKeys,
	const std::map<std::string, Inventory::Ptr>& inventories) :
	_roots(roots),
	_hotKeys(hotKeys),
	_inventories(inventories)
{
}

const std::map<std::string, Node>& JsonQuest::GetRoots() const
{
	return _roots;
}

const std::vector<std::string>& JsonQuest::GetHotKeys() const
{
	return _hotKeys;
}

const std::map<std::string, Inventory::Ptr>& JsonQuest::GetInventories() const
{
	return _inventories;
}
