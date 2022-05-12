#include "Factories/JsonQuest.hpp"
#include "IParagraph.hpp"
#include "Item.hpp"
#include "Inventory.hpp"

using namespace QuestCore;

JsonQuest::JsonQuest(const TextViewFactoryPtr& viewFactory,
	const ButtonsFactoryPtr& buttonsFactory,
	const std::map<std::string, QuestCore::Node>& roots,
	const std::map<std::string, InventoryPtr>& inventories) :
	QuestBase(viewFactory, buttonsFactory),
	_roots(roots),
	_inventories(inventories)
{
}

const std::map<std::string, Node>& JsonQuest::GetRoots() const
{
	return _roots;
}

const std::map<std::string, Inventory::Ptr>& JsonQuest::GetInventories() const
{
	return _inventories;
}
