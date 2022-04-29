#include "Paragraphs/TextParagraph.hpp"

using namespace QuestCore;

TextParagraph::TextParagraph(const TextString& text):
	_text(text)
{
}

TextString TextParagraph::GetQuest() const
{
	return _text;
}

CaseContainer& TextParagraph::GetCaseContainer()
{
	return _cases;
}
