#pragma once
#include <memory>
#include <string>

namespace QuestCore
{
	class IParagraph;
	class ICaseContainer;
	class Inventory;
}

class IRootFactory
{
protected:
	using ParagraphPtr = std::shared_ptr<QuestCore::IParagraph>;
	using CaseContainerPtr = std::shared_ptr<QuestCore::ICaseContainer>;
	using InventoryPtr = std::shared_ptr<QuestCore::Inventory>;

public:
	virtual ~IRootFactory() = default;

	virtual ParagraphPtr GetParagraph(const std::string& rootKey) = 0;
	virtual CaseContainerPtr GetCaseContainer(const std::string& rootKey) = 0;
	virtual InventoryPtr GetInventory(const std::string& inventoryKey) = 0;
};