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
		ConditionalParagraph(const std::vector<std::shared_ptr<ICondition>>& conditions = std::vector<std::shared_ptr<ICondition>>());
		/// @inject
		void SetThenParagraph(const std::shared_ptr<IParagraph>& thenParagraph);
		/// @inject
		void SetElseParagraph(const std::shared_ptr<IParagraph>& elseParagraph);

		virtual void Print(ITextView& view) override;
		void ClearConditions();
		void AddCondition(const ConditionPtr& condition);
		bool IsAllowed() const;

	private:
		IParagraph::Ptr _thenParagraph;
		IParagraph::Ptr _elseParagraph;
		std::vector<ConditionPtr> _conditions;
	};
}
