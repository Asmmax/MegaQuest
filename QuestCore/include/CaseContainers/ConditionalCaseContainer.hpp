#pragma once
#include "ICaseContainer.hpp"
#include <memory>

namespace QuestCore
{
	class ICondition;

	class ConditionalCaseContainer : public ICaseContainer
	{
		using ConditionPtr = std::shared_ptr<ICondition>;

	public:
		virtual void Print(IButtonPanel& buttonPanel) override;

		void SetThenContainer(const ICaseContainer::Ptr& thenContainer);
		void SetElseContainer(const ICaseContainer::Ptr& elseContainer);
		void ClearConditions();
		void AddCondition(const ConditionPtr& condition);
		bool IsAllowed() const;

	private:
		ICaseContainer::Ptr _thenContainer;
		ICaseContainer::Ptr _elseContainer;
		std::vector<ConditionPtr> _conditions;
	};
}
