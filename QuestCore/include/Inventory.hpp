#pragma once
#include "Quests/QuestInitable.hpp"
#include <memory>
#include <map>
#include <vector>

namespace QuestCore
{
	class Item;

	/// @serializable
	struct ItemRecord
	{
		std::shared_ptr<Item> item;
		int count;
	};

	/// @serializable @shared inventories
	class Inventory : public QuestInitable
	{
		using ItemPtr = std::shared_ptr<Item>;
	public:
		using Ptr = std::shared_ptr<Inventory>;

		Inventory(const QuestHeaderPtr& quest, const std::vector<ItemRecord>& items = std::vector<ItemRecord>());
		void PutItem(const ItemPtr& item, int count);
		void ThrowItem(const ItemPtr& item, int count);
		inline const std::map<ItemPtr, int>& GetItems() const { return _items; }
		virtual void Init() override;

	private:
		std::map<ItemPtr, int> _initItems;
		std::map<ItemPtr, int> _items;
	};
}
