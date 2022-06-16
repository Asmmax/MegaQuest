#include "Paragraphs/ConditionalParagraph.hpp"
#include "ICondition.hpp"
#include "TextString.hpp"

using namespace QuestCore;

ConditionalParagraph::ConditionalParagraph(const std::vector<std::shared_ptr<ICondition>>& conditions):
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

void ConditionalParagraph::SetThenParagraph(const IParagraph::Ptr& thenParagraph)
{
	_thenParagraph = thenParagraph;
}

void ConditionalParagraph::SetElseParagraph(const IParagraph::Ptr& elseParagraph)
{
	_elseParagraph = elseParagraph;
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
