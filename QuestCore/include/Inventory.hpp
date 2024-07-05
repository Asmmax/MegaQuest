#pragma once
#include "Quests/QuestInitable.hpp"
#include <memory>
#include <map>
#include <vector>

namespace QuestCore
{
	class Item;

	struct ItemRecord
	{
		Item* item;
		int count;
	};

	class Inventory : public QuestInitable
	{
	public:

		Inventory(Quest* quest, const std::vector<ItemRecord>& items = std::vector<ItemRecord>());
		void PutItem(Item* item, int count);
		void ThrowItem(Item* item, int count);
		inline const std::map<Item*, int>& GetItems() const { return _items; }
		virtual void Init() override;

	private:
		std::map<Item*, int> _initItems;
		std::map<Item*, int> _items;
	};
}
