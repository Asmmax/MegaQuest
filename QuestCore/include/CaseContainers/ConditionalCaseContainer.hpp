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
		virtual const std::vector<Case>& GetCases(const std::string& key = std::string()) const override;
		virtual size_t GetCaseCount() const override;

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