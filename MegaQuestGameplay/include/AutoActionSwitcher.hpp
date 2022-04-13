#pragma once
#include "ActionSwitcher.hpp"

namespace QuestCore
{
	class AutoActionSwitcher : public ActionSwitcher
	{
	public:
		AutoActionSwitcher();
		virtual void Do() override;

		void SetFinalAction(const std::shared_ptr<IAction>& action);

	private:
		std::shared_ptr<IAction> _finalActionId;
	};
}
