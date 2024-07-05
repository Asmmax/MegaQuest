#pragma once
#include "IAction.hpp"
#include "Inventory.hpp"
#include <vector>
#include <memory>

namespace QuestCore
{
	class Transfer: public IAction
	{
	public:
		Transfer(Inventory* source, Inventory* target,
			const std::vector<ItemRecord>& items = std::vector<ItemRecord>());

		virtual void Do() override;

		void AddThings(Item* thing, int count);
		std::vector<ItemRecord> BoundThingsBy(Inventory* inventory);

	private:
		std::vector<ItemRecord> _things;
		Inventory* _source;
		Inventory* _target;
	};
}
