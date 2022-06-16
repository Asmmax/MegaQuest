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
		ConditionalCaseContainer(const std::vector<std::shared_ptr<ICondition>>& conditions = std::vector<std::shared_ptr<ICondition>>());
		/// @inject
		void SetThenContainer(const std::shared_ptr<ICaseContainer>& thenContainer);
		/// @inject
		void SetElseContainer(const std::shared_ptr<ICaseContainer>& elseContainer);

		virtual void Print(IButtonGroup& buttons) override;
		void ClearConditions();
		void AddCondition(const ConditionPtr& condition);
		bool IsAllowed() const;

	private:
		ICaseContainer::Ptr _thenContainer;
		ICaseContainer::Ptr _elseContainer;
		std::vector<ConditionPtr> _conditions;
	};
}
