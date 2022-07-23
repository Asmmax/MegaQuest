#include "Paragraphs/ParagraphGroup.hpp"
#include "ITextView.hpp"

using namespace QuestCore;

ParagraphGroup::ParagraphGroup(
	const std::vector<std::shared_ptr<IParagraph>>& children,
	const TextString& gap):

	_paragraphs(children),
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

void ParagraphGroup::Print(ITextView& view)
{
	for (auto it = _paragraphs.begin(); it != _paragraphs.end(); it++) {
		if (it != _paragraphs.begin()) {
			view.AppendText(_gap);
		}
		auto& paragraphPtr = *it;
		paragraphPtr->Print(view);
	}
}
