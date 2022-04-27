#include "ParagraphGroup.hpp"

using namespace QuestCore;

ParagraphGroup::ParagraphGroup(const TextString& gap):
	_gap(gap)
{
}

void ParagraphGroup::ClearParagraphs()
{
	_paragraphs.clear();
	_actions.Clear();
}

void ParagraphGroup::AddParagraph(const std::shared_ptr<IParagraph>& paragraph)
{
	_paragraphs.emplace_back(paragraph);
}

void ParagraphGroup::UpdateActions()
{
	_actions.Clear();
	for (auto& paragraph : _paragraphs) {
		_actions += paragraph->GetActionContainer();
	}
}

TextString ParagraphGroup::GetQuest() const
{
	TextString result;
	for (auto it = _paragraphs.begin(); it != _paragraphs.end(); it++) {
		if (it != _paragraphs.begin()) {
			result += _gap;
		}
		auto& paragraphPtr = *it;
		result += paragraphPtr->GetQuest();
	}
	return result;
}

ActionMap& ParagraphGroup::GetActionContainer()
{
	UpdateActions();
	return _actions;
}
