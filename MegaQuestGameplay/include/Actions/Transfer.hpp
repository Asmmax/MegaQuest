#pragma once
#include "IAction.hpp"
#include <vector>
#include <memory>

namespace QuestCore
{
	class Inventory;
	class Item;

	class Transfer: public IAction
	{
		using ItemPtr = std::shared_ptr<Item>;
		using ItemQuery = std::pair<ItemPtr, int>;
	public:
		Transfer(const std::shared_ptr<Inventory>& source, const std::shared_ptr<Inventory>& target);
		virtual void Do() override;

		void AddThings(const ItemPtr& thing, int count);
		std::vector<ItemQuery> BoudThingsBy(const std::shared_ptr<Inventory>& inventory);

	private:
		std::vector<ItemQuery> _things;
		std::shared_ptr<Inventory> _source;
		std::shared_ptr<Inventory> _target;
	};
}
