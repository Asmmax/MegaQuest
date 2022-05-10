#include "Paragraphs/TextParagraph.hpp"

using namespace QuestCore;

TextParagraph::TextParagraph(const TextString& text):
	_text(text)
{
}

TextString TextParagraph::GetText() const
{
	return _text;
}
