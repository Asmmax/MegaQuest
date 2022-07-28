#include "Quests/ParagraphInput.hpp"
#include "Quests/ParagraphSlot.hpp"

using namespace QuestCore;

ParagraphInput::ParagraphInput(const ParagraphPtr& paragraph, const ParagraphSlotPtr& slot):
	_paragraph(paragraph),
	_slot(slot)
{
}

void ParagraphInput::Update()
{
	_slot->SetInput(this);
}

ParagraphInput::ParagraphPtr ParagraphInput::GetParagraph() const
{
	return _paragraph;
}
