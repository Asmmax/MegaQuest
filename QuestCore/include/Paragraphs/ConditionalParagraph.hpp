#pragma once
#include "IParagraph.hpp"
#include <memory>
#include <vector>

namespace QuestCore
{
	class ICondition;

	class ConditionalParagraph : public IParagraph
	{
		using ConditionPtr = std::shared_ptr<ICondition>;

	public:
		virtual TextString GetText() const override;
		void SetThenParagraph(const IParagraph::Ptr& thenParagraph);
		void SetElseParagraph(const IParagraph::Ptr& elseParagraph);
		void ClearConditions();
		void AddCondition(const ConditionPtr& condition);
		bool IsAllowed() const;

	private:
		IParagraph::Ptr _thenParagraph;
		IParagraph::Ptr _elseParagraph;
		std::vector<ConditionPtr> _conditions;
	};
}