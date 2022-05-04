#include "Paragraphs/ConditionalParagraph.hpp"
#include "CaseContainer.hpp"
#include "ICondition.hpp"

using namespace QuestCore;

TextString ConditionalParagraph::GetQuest() const
{
	static TextString defaultQuest;

	if (IsAllowed()) {
		if (!_thenParagraph) {
			return defaultQuest;
		}
		return _thenParagraph->GetQuest();
	}

	if (!_elseParagraph) {
		return defaultQuest;
	}
	return _elseParagraph->GetQuest();
}

CaseContainer& ConditionalParagraph::GetCaseContainer()
{
	static CaseContainer defaultContainer;

	if (IsAllowed()) {
		if (!_thenParagraph) {
			return defaultContainer;
		}
		return _thenParagraph->GetCaseContainer();
	}

	if (!_elseParagraph) {
		return defaultContainer;
	}
	return _elseParagraph->GetCaseContainer();
}

void ConditionalParagraph::SetThenParagraph(const std::shared_ptr<IParagraph>& thenParagraph)
{
	_thenParagraph = thenParagraph;
}

void ConditionalParagraph::SetElseParagraph(const std::shared_ptr<IParagraph>& elseParagraph)
{
	_elseParagraph = elseParagraph;
}

void ConditionalParagraph::ClearConditions()
{
	_conditions.clear();
}

void ConditionalParagraph::AddCondition(const std::shared_ptr<ICondition>& condition)
{
	_conditions.push_back(condition);
}

bool ConditionalParagraph::IsAllowed() const
{
	for (auto& condition : _conditions) {
		if (!condition->IsAllowed()) {
			return false;
		}
	}
	return true;
}
