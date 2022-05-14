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

	virtual ParagraphPtr GetRootParagraph(const std::string& rootKey) = 0;
	virtual CaseContainerPtr GetRootCaseContainer(const std::string& rootKey) = 0;
	virtual InventoryPtr GetInventory(const std::string& inventoryKey) = 0;
};