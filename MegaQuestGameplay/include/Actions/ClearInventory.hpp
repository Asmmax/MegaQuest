#pragma once
#include "IAction.hpp"
#include <memory>

namespace QuestCore
{
	class Inventory;

	class ClearInventory : public IAction
	{
	public:
		ClearInventory(const std::shared_ptr<Inventory>& inventory);
		virtual void Do() override;
	private:
		std::shared_ptr<Inventory> _inventory;
	};
}