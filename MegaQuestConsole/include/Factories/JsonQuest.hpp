#pragma once
#include "IQuest.hpp"

namespace QuestCore
{
	class Item;
	class IParagraph;
	class Inventory;
}

class JsonQuest : public QuestCore::IQuest
{
public:
	JsonQuest(const std::map<std::string, QuestCore::Node>& roots,
		const std::vector<std::string>& hotKeys,
		const std::map<std::string, InventoryPtr>& inventories);

	virtual const std::map<std::string, QuestCore::Node>& GetRoots() const override;
	virtual const std::vector<std::string>& GetHotKeys() const override;
	virtual const std::map<std::string, InventoryPtr>& GetInventories() const override;

private:
	std::vector<std::string> _hotKeys;
	std::map<std::string, QuestCore::Node> _roots;
	std::map<std::string, InventoryPtr> _inventories;
};