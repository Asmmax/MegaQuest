#pragma once
#include "IAction.hpp"
#include <memory>

namespace QuestCore
{
	class Inventory;

	class Clearing : public IAction
	{
	public:
		Clearing(Inventory* inventory);
		virtual void Do() override;
	private:
		Inventory* _inventory;
	};
}
