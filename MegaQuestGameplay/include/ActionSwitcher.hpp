#pragma once
#include "ActionContainer.hpp"
#include "IAction.hpp"

namespace QuestCore
{
	class ActionSwitcher : public ActionContainer, public IAction
	{
	public:
		virtual std::string GetName() const override;
		virtual void Do() override;

		void Switch(const std::shared_ptr<IAction>& action);

	private:
		std::shared_ptr<IAction> _target;
	};
}
