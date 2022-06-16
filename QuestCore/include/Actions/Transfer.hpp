#pragma once
#include "IAction.hpp"
#include "Inventory.hpp"
#include <vector>
#include <memory>

namespace QuestCore
{
	class Transfer: public IAction
	{
		using ItemPtr = std::shared_ptr<Item>;
	public:
		Transfer(const std::shared_ptr<Inventory>& source, 
			const std::shared_ptr<Inventory>& target,
			const std::vector<ItemRecord>& items = std::vector<ItemRecord>());

		virtual void Do() override;

		void AddThings(const ItemPtr& thing, int count);
		std::vector<ItemRecord> BoundThingsBy(const std::shared_ptr<Inventory>& inventory);

	private:
		std::vector<ItemRecord> _things;
		std::shared_ptr<Inventory> _source;
		std::shared_ptr<Inventory> _target;
	};
}
