#include "TextParagraph.hpp"

using namespace QuestCore;

TextParagraph::TextParagraph(const std::string& text):
	_text(text)
{
}

std::string TextParagraph::GetQuest() const
{
	return _text + "\n";
}
