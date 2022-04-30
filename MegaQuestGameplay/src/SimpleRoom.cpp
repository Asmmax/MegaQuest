#include "SimpleRoom.hpp"

using namespace QuestCore;

SimpleRoom::SimpleRoom(const InputList& inputs, 
	const std::vector<std::string>& hotKeys, 
	const std::map<std::string, ItemPtr>& items,
	const std::map<std::string, InventoryPtr>& inventories):
	_hotKeys(hotKeys),
	_items(items),
	_inventories(inventories),
	_paragraphs(inputs)
{
}

const std::shared_ptr<IParagraph>& SimpleRoom::GetParagraph(const std::string& key) const
{
	return _paragraphs[key];
}

const std::vector<std::string>& SimpleRoom::GetHotKeys() const
{
	return _hotKeys;
}

const std::map<std::string, IRoom::ItemPtr>& SimpleRoom::GetItems() const
{
	return _items;
}

const std::map<std::string, IRoom::InventoryPtr>& SimpleRoom::GetInventories() const
{
	return _inventories;
}
