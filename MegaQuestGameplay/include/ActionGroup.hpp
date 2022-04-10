#pragma once
#include "ActionContainer.hpp"
#include "IAction.hpp"

namespace QuestCore
{
	class ActionGroup: public ActionContainer, public IAction
	{
	public:
		virtual std::string GetName() const override;
		virtual void Do() override;
	};
}
