#include "Paragraphs/ConditionalParagraph.hpp"
#include "ICondition.hpp"
#include "TextString.hpp"

using namespace QuestCore;

ConditionalParagraph::ConditionalParagraph(
	IParagraph* thenParagraph,
	IParagraph* elseParagraph, 
	const std::vector<ICondition*>& conditions):

	_thenParagraph(thenParagraph),
	_elseParagraph(elseParagraph),
	_conditions(conditions)
{
}

void ConditionalParagraph::Print(ITextView& view)
{
	if (IsAllowed()) {
		if (_thenParagraph) {
			_thenParagraph->Print(view);
		}
	}
	else {

		if (_elseParagraph) {
			_elseParagraph->Print(view);
		}
	}
}

void ConditionalParagraph::ClearConditions()
{
	_conditions.clear();
}

void ConditionalParagraph::AddCondition(ICondition* condition)
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
