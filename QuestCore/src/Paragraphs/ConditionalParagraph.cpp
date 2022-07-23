#include "Paragraphs/ConditionalParagraph.hpp"
#include "ICondition.hpp"
#include "TextString.hpp"

using namespace QuestCore;

ConditionalParagraph::ConditionalParagraph(
	const std::shared_ptr<IParagraph>& thenParagraph,
	const std::shared_ptr<IParagraph>& elseParagraph, 
	const std::vector<std::shared_ptr<ICondition>>& conditions):

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

void ConditionalParagraph::AddCondition(const ICondition::Ptr& condition)
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
