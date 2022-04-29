#pragma once
#include "IAction.hpp"
#include <vector>
#include <memory>

namespace QuestCore
{
	class Inventory;
	class Item;

	class GiftReceiving: public IAction
	{
		using ItemPtr = std::shared_ptr<Item>;
		using ItemQuery = std::pair<ItemPtr, int>;
	public:
		GiftReceiving(const std::shared_ptr<Inventory>& inventory);
		virtual void Do() override;

		void AddThings(const ItemPtr& thing, int count);

	private:
		std::vector<ItemQuery> _things;
		std::shared_ptr<Inventory> _inventory;
	};
}
