#pragma once
#include "IAction.hpp"
#include <memory>

namespace QuestCore
{
	class Inventory;

	class CopyInventory : public IAction
	{
	public:
		CopyInventory(const std::shared_ptr<Inventory>& source, const std::shared_ptr<Inventory>& target);
		virtual void Do() override;
	private:
		std::shared_ptr<Inventory> _source;
		std::shared_ptr<Inventory> _target;
	};
}