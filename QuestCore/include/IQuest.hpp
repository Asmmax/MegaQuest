#pragma once
#include <memory>
#include <vector>
#include <map>
#include <string>

namespace QuestCore
{
	class IParagraph;
	class Item;
	class Inventory;
	class ICaseContainer;

	struct Node
	{
	private:
		using ParagraphPtr = std::shared_ptr<IParagraph>;
		using CaseContainerPtr = std::shared_ptr<ICaseContainer>;

	public:
		ParagraphPtr paragraph;
		CaseContainerPtr caseContainer;
	};

	class IQuest
	{
	protected:
		using ItemPtr = std::shared_ptr<Item>;
		using InventoryPtr = std::shared_ptr<Inventory>;

	public:
		virtual ~IQuest() = default;

		virtual const std::map<std::string, Node>& GetRoots() const = 0;
		virtual const std::vector<std::string>& GetHotKeys() const = 0;
		virtual const std::map<std::string, InventoryPtr>& GetInventories() const = 0;
	};
};
