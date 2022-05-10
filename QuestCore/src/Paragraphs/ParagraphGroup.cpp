#include "Paragraphs/ParagraphGroup.hpp"

using namespace QuestCore;

ParagraphGroup::ParagraphGroup(const TextString& gap):
	_gap(gap)
{
}

void ParagraphGroup::Clear()
{
	_paragraphs.clear();
}

void ParagraphGroup::AddParagraph(const IParagraph::Ptr& paragraph)
{
	_paragraphs.emplace_back(paragraph);
}

TextString ParagraphGroup::GetText() const
{
	TextString result;
	for (auto it = _paragraphs.begin(); it != _paragraphs.end(); it++) {
		if (it != _paragraphs.begin()) {
			result += _gap;
		}
		auto& paragraphPtr = *it;
		result += paragraphPtr->GetText();
	}
	return result;
}
