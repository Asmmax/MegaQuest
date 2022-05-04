#include "Paragraphs/ParagraphGroup.hpp"

using namespace QuestCore;

ParagraphGroup::ParagraphGroup(const TextString& gap):
	_gap(gap)
{
}

void ParagraphGroup::ClearParagraphs()
{
	_paragraphs.clear();
	_cases.Clear();
}

void ParagraphGroup::AddParagraph(const std::shared_ptr<IParagraph>& paragraph)
{
	_paragraphs.emplace_back(paragraph);
}

void ParagraphGroup::UpdateCases()
{
	_cases.Clear();
	for (auto& paragraph : _paragraphs) {
		_cases += paragraph->GetCaseContainer();
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

CaseContainer& ParagraphGroup::GetCaseContainer()
{
	UpdateCases();
	return _cases;
}
