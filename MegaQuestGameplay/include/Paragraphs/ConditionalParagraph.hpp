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
		virtual TextString GetQuest() const override;
		virtual CaseContainer& GetCaseContainer() override;
		void SetThenParagraph(const std::shared_ptr<IParagraph>& thenParagraph);
		void SetElseParagraph(const std::shared_ptr<IParagraph>& elseParagraph);
		void ClearConditions();
		void AddCondition(const std::shared_ptr<ICondition>& condition);
		bool IsAllowed() const;

	private:
		std::shared_ptr<IParagraph> _thenParagraph;
		std::shared_ptr<IParagraph> _elseParagraph;
		std::vector<std::shared_ptr<ICondition>> _conditions;
	};
}