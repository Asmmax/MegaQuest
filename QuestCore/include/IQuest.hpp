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

	class IQuest
	{
	protected:
		using ParagraphPtr = std::shared_ptr<IParagraph>;
		using ItemPtr = std::shared_ptr<Item>;
		using InventoryPtr = std::shared_ptr<Inventory>;

	public:
		virtual ~IQuest() = default;

		virtual const std::map<std::string, ParagraphPtr>& GetRoots() const = 0;
		virtual const std::vector<std::string>& GetHotKeys() const = 0;
		virtual const std::map<std::string, ItemPtr>& GetItems() const = 0;
		virtual const std::map<std::string, InventoryPtr>& GetInventories() const = 0;
	};
};
