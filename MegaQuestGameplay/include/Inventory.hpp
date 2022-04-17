#pragma once
#include <memory>
#include <map>

namespace QuestCore
{
	class ItemInfo;

	class Inventory
	{
		using ItemInfoPtr = std::shared_ptr<ItemInfo>;
	public:
		void PutItem(const ItemInfoPtr& item, int count);
		void ThrowItem(const ItemInfoPtr& item, int count);
		std::map<ItemInfoPtr, int> GetNullableItems() const;
		std::map<ItemInfoPtr, int> GetItems() const;

	private:
		std::map<ItemInfoPtr, int> _items;
	};
}
