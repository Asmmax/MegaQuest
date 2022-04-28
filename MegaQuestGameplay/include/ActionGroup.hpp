#pragma once
#include "ActionContainer.hpp"
#include "IAction.hpp"

namespace QuestCore
{
	class ActionGroup: public ActionContainer, public IAction
	{
	public:
		ActionGroup(const TextString& prefix, const TextString& gap);
		virtual TextString GetName() const override;
		virtual void Do() override;
	private:
		TextString _prefix;
		TextString _gap;
	};
}
