#pragma once
#include "IAction.hpp"
#include <memory>

namespace QuestCore
{
	class Inventory;

	class Copying : public IAction
	{
	public:
		Copying(Inventory* source, Inventory* target);
		virtual void Do() override;
	private:
		Inventory* _source;
		Inventory* _target;
	};
}
