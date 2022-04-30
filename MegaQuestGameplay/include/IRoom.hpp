#pragma once
#include "TextString.hpp"
#include <memory>
#include <vector>
#include <map>

namespace QuestCore
{
	class IParagraph;
	class Item;
	class Inventory;

	class IRoom
	{
	public:
		using ItemPtr = std::shared_ptr<Item>;
		using InventoryPtr = std::shared_ptr<Inventory>;

		virtual ~IRoom() = default;

		virtual const std::shared_ptr<IParagraph>& GetParagraph(const std::string& key) const = 0;
		virtual const std::vector<std::string>& GetHotKeys() const = 0;
		virtual const std::map<std::string, ItemPtr>& GetItems() const = 0;
		virtual const std::map<std::string, InventoryPtr>& GetInventories() const = 0;
	};
}
