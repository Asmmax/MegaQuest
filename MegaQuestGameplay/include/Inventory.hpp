#pragma once
#include "Item.hpp"
#include <memory>
#include <map>

namespace QuestCore
{
	class Inventory
	{
		using ItemPtr = std::shared_ptr<Item>;
		using ItemContainer = std::map<ItemPtr, int, ItemComparator>;
	public:
		void PutItem(const ItemPtr& item, int count);
		void ThrowItem(const ItemPtr& item, int count);
		inline const ItemContainer& GetItems() const { return _items; }

	private:
		ItemContainer _items;
	};
}
