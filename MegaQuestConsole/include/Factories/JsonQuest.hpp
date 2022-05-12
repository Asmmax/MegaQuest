#pragma once
#include "QuestBase.hpp"

namespace QuestCore
{
	class Item;
	class IParagraph;
	class Inventory;
}

class JsonQuest : public QuestCore::QuestBase
{
public:
	JsonQuest(const TextViewFactoryPtr& viewFactory, 
		const ButtonsFactoryPtr& buttonsFactory, 
		const std::map<std::string, QuestCore::Node>& roots,
		const std::map<std::string, InventoryPtr>& inventories);

	virtual const std::map<std::string, InventoryPtr>& GetInventories() const override;

protected:
	virtual const std::map<std::string, QuestCore::Node>& GetRoots() const override;

private:
	std::map<std::string, QuestCore::Node> _roots;
	std::map<std::string, InventoryPtr> _inventories;
};