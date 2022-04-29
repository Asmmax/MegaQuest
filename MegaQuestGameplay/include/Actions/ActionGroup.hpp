#pragma once
#include "IAction.hpp"
#include <memory>
#include <vector>

namespace QuestCore
{
	class ActionGroup: public IAction
	{
	public:
		void Clear();
		void AddAction(const std::shared_ptr<IAction>& action);
		virtual void Do() override;
	private:
		std::vector<std::shared_ptr<IAction>> _actions;
	};
}
