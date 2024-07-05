#pragma once
#include "ICaseContainer.hpp"
#include <memory>

namespace QuestCore
{
	class ICondition;

	class ConditionalCaseContainer : public ICaseContainer
	{
	public:
		ConditionalCaseContainer(ICaseContainer* thenContainer,
			ICaseContainer* elseContainer,
			const std::vector<ICondition*>& conditions = std::vector<ICondition*>());

		virtual void Print(IButtonGroup& buttons) override;
		void ClearConditions();
		void AddCondition(ICondition* condition);
		bool IsAllowed() const;

	private:
		ICaseContainer* _thenContainer;
		ICaseContainer* _elseContainer;
		std::vector<ICondition*> _conditions;
	};
}
