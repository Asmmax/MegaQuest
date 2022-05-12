#include "Paragraphs/TextParagraph.hpp"
#include "ITextView.hpp"

using namespace QuestCore;

TextParagraph::TextParagraph(const TextString& text):
	_text(text)
{
}
void TextParagraph::Print(ITextView& view)
{
	view.AppendText(_text);
}
