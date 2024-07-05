#pragma once
#include "IParagraph.hpp"
#include <memory>
#include <vector>

namespace QuestCore
{
	class ICondition;

	class ConditionalParagraph : public IParagraph
	{
	public:
		ConditionalParagraph(IParagraph* thenParagraph,
			IParagraph* elseParagraph,
			const std::vector<ICondition*>& conditions = std::vector<ICondition*>());

		virtual void Print(ITextView& view) override;
		void ClearConditions();
		void AddCondition(ICondition* condition);
		bool IsAllowed() const;

	private:
		IParagraph* _thenParagraph;
		IParagraph* _elseParagraph;
		std::vector<ICondition*> _conditions;
	};
}
