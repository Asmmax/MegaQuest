#include "Paragraphs/ConditionalParagraph.hpp"
#include "ICondition.hpp"
#include "TextString.hpp"

using namespace QuestCore;

TextString ConditionalParagraph::GetText() const
{
	if (IsAllowed()) {
		if (!_thenParagraph) {
			return TextString();
		}
		return _thenParagraph->GetText();
	}

	if (!_elseParagraph) {
		return TextString();
	}
	return _elseParagraph->GetText();
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
