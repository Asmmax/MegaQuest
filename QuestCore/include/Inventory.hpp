#pragma once
#include "Item.hpp"
#include <memory>
#include <map>

namespace QuestCore
{
	class Inventory
	{
		using ItemPtr = std::shared_ptr<Item>;
	public:
		using Ptr = std::shared_ptr<Inventory>;

		void PutItem(const ItemPtr& item, int count);
		void ThrowItem(const ItemPtr& item, int count);
		inline const std::map<ItemPtr, int>& GetItems() const { return _items; }

	private:
		std::map<ItemPtr, int> _items;
	};
}
